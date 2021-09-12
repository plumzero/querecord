
package main

import (
	"context"
	"net/http"
	"time"
)

// ContextMiddle 是 HTTP 服务中间件，统一读取通行 cookie 并使用 ctx 传递
func ContextMiddle(next http.Handler) http.Handler {
	return http.HandlerFunc(func(w http.ResponseWriter, r *http.Request) {
		cookie, _ := r.Cookie("Check")
		if cookie != nil {
			ctx := context.WithValue(r.Context(), "Check", cookie.Value)
			next.ServeHTTP(w, r.WithContext(ctx))
		} else {
			next.ServeHTTP(w, r)
		}
	})
}

func CheckHandler(w http.ResponseWriter, r *http.Request) {
	expiration := time.Now().Add(1 * time.Minute)
	cookie := http.Cookie{Name: "Check", Value: "42", Expires: expiration}
	http.SetCookie(w, &cookie)
}

func indexHandler(w http.ResponseWriter, r *http.Request) {
	// 通过取中间件传过来的 context 值来判断是否放行通过
	if chk := r.Context().Value("Check"); chk == "42" {
		w.WriteHeader(http.StatusOK)
		w.Write([]byte("Let's go!"))
	} else {
		w.WriteHeader(http.StatusNotFound)
		w.Write([]byte("No Pass!"))
	}
}

// 打开浏览器，依次访问如下 url
//  /
//  /chk
//  /
// 观察效果
func main() {
	mux := http.NewServeMux()
	
	mux.HandleFunc("/", indexHandler)

	mux.HandleFunc("/chk", CheckHandler)

	ctxMux := ContextMiddle(mux)
	http.ListenAndServe(":8080", ctxMux)
}