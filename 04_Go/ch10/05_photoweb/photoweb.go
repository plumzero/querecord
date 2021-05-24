
package main

import (
	"io"
	"log"
	"net/http"
	"os"
	"io/ioutil"
	"mime"
	"html/template"
	"strings"
	"path"
	"runtime/debug"
	"fmt"
)

const (
	UPLOAD_DIR = "./uploads"
	TEMPLATE_DIR = "./views"
	ListDir = 0x0001
)

var templates map[string]*template.Template = make(map[string]*template.Template)

// init() 函数会在 main 函数之前执行
// 预加载模板
func init() {
	files, err := ioutil.ReadDir(TEMPLATE_DIR)
	if err != nil {
		panic(err)
		return
	}
	var templateName, templatePath string
	for _, fi := range files {
		templateName = fi.Name()
		if ext := path.Ext(templateName); ext != ".html" {
			continue
		}
		templatePath = TEMPLATE_DIR + "/" + templateName
		tmpl := strings.Replace(templateName, ".html", "", 1)
		
		t := template.Must(template.ParseFiles(templatePath))
		templates[tmpl] = t
	}
}

func uploadHandler(w http.ResponseWriter, r *http.Request) {
	if r.Method == "GET" {
		if err := renderHtml(w, "upload", nil); err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
	}

	if r.Method == "POST" {
		// 接收到来自客户端的 POST 请求，从表单中寻找名为 image 的文本域
		f, h, err := r.FormFile("image")	// return multipart.File *multipart.FileHeader error
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		filename := h.Filename
		defer f.Close()
		// 创建文件
		t, err := os.Create(UPLOAD_DIR + "/" + filename)
		if err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		defer t.Close()
		// 创建副本
		if _, err := io.Copy(t, f); err != nil {
			http.Error(w, err.Error(), http.StatusInternalServerError)
			return
		}
		// 跳转到查看图片页面
		http.Redirect(w, r, "/view?id=" + filename, http.StatusFound)
	}
}

func viewHandler(w http.ResponseWriter, r *http.Request) {
	imageId := r.FormValue("id")
	imagePath := UPLOAD_DIR + "/" + imageId
	if exists := isExists(imagePath); !exists {
		http.NotFound(w, r)
		return
	}
	content, err := ioutil.ReadFile(imagePath)
	if err != nil {
		panic(err)
	}
	mime_type := http.DetectContentType(content)
	mediatype, _, err := mime.ParseMediaType(mime_type)
	if err != nil {
		panic(err)
	}
	w.Header().Set("Content-Type", mediatype)
	http.ServeFile(w, r, imagePath)
}

func listHandler(w http.ResponseWriter, r *http.Request) {
	files, err := ioutil.ReadDir(UPLOAD_DIR)
	if err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
		return
	}

	locals := make(map[string]interface{})
	images := []string{}
	for _, fi := range files {
		images = append(images, fi.Name())
	}
	locals["images"] = images

	if err = renderHtml(w, "list", locals); err != nil {
		http.Error(w, err.Error(), http.StatusInternalServerError)
	}
}

func isExists(path string) bool {
	_, err := os.Stat(path)
	if err == nil {
		return true
	}
	return os.IsExist(err)
}

func renderHtml(w http.ResponseWriter, tname string, locals map[string]interface{}) (err error) {
	err = templates[tname].Execute(w, locals)
	return err
}

func safeHandler(fn http.HandlerFunc) http.HandlerFunc {
	return func(w http.ResponseWriter, r *http.Request) {
		defer func() {
			if e, ok := recover().(error); ok {
				http.Error(w, e.Error(), http.StatusInternalServerError)
				fmt.Println("WARN: panic in %v. - %v", fn, e)
				fmt.Println(string(debug.Stack()))
			}
		}()
		fn(w, r)
	}
}

// 动态请求与静态资源分离
func staticDirHandler(mux *http.ServeMux, prefix string, staticDir string, flags int) {
	mux.HandleFunc(prefix, func(w http.ResponseWriter, r *http.Request) {
		file := staticDir + r.URL.Path[len(prefix) - 1:]
		if (flags & ListDir) == 0 {
			if exists := isExists(file); ! exists {
				http.NotFound(w, r)
				return
			}
		}
		http.ServeFile(w, r, file)
	})
}

func main() {
	mux := http.NewServeMux()
	staticDirHandler(mux, "/assets/", "./public", 0)
	http.HandleFunc("/upload", safeHandler(uploadHandler))
	http.HandleFunc("/view", safeHandler(viewHandler))
	http.HandleFunc("/", safeHandler(listHandler))
	err := http.ListenAndServe(":8080", nil)
	if err != nil {
		log.Fatal("ListenAndServe: ", err.Error())
	}
}
