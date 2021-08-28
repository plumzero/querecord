
// 你要自己决定是否需要这么多的判断
function showPic(whichPic) {
    if (! document.getElementById("placeholder")) return false;
    var source = whichPic.getAttribute("href");
    var placeholder = document.getElementById("placeholder");
    placeholder.setAttribute("src", source);
    // 如果没有 description 就算了
    if (document.getElementById("description")) {
        var text = whichPic.getAttribute("title") ? whichPic.getAttribute("title") : "";
        var description = document.getElementById("description");
        if (description.firstChild.nodeType == 3) {
            description.firstChild.nodeValue = text;
        }
    }
    return true;
}

function countBodyChildren() {
    var body_element = document.getElementsByTagName("body")[0];
    alert(body_element.childNodes.length);
}

function prepareGallery() {
    // 对象检测
    if (! document.getElementsByTagName) return false;
    if (! document.getElementById) return false;
    if (! document.getElementById("imagegallery")) return false;

    var gallery = document.getElementById("imagegallery");
    var links = gallery.getElementsByTagName("a");
    for (var i = 0; i < links.length; i++) {
        links[i].onclick = function() {
            return ! showPic(this);     // 如果返回 false，则图片未更新，返回 true 允许默认行为发生。
        }
        links[i].onkeypress = links[i].onclick; // 允许键盘事件。不过，最好不要使用 onkeypress 事件处理函数
    }
}

// 利用 addLoadEvent 可以加载多个预处理函数执行，而仅使用 window.onload 的话只能执行最后一个
function addLoadEvent(func) {
    var oldonload = window.onload;
    if (typeof window.onload != 'function') {
        window.onload = func;
    } else {
        window.onload = function() {
            oldonload();
            func();
        }
    }
}

function appendElement() {
    var placeholder = document.createElement("img");
    placeholder.setAttribute("id", "placeholder");
    placeholder.setAttribute("src", "images/placeholder.gif");
    placeholder.setAttribute("alt", "my image gallery");
    var description = document.createElement("p");
    description.setAttribute("id", "description");
    var desctext = document.createTextNode("Choose an image");
    description.appendChild(desctext);
    document.body.appendChild(placeholder);
    var gallery = document.getElementById("imagegallery");
    gallery.parentNode.insertBefore(description, gallery);
}

// DOM 本身不提供类似于 insertBefore 的 insertAfter 函数，但我们可以实现一个，如下:
function insertAfter(newElement, targetElement) {
    var parent = targetElement.parentNode;
    if (parent.lastChild == targetElement) {
        parent.appendChild(newElement);
    } else {
        parent.insertBefore(newElement, targetElement.nextSibling);
    }
}

function preparePlaceholder() {
    if (! document.createElement) return false;
    if (! document.createTextNode) return false;
    if (! document.getElementById) return false;
    if (! document.getElementById("imagegallery")) return false;
    var placeholder = document.createElement("img");
    placeholder.setAttribute("id", "placeholder");
    placeholder.setAttribute("src", "images/placeholder.gif");
    placeholder.setAttribute("alt", "my image gallery");
    var description = document.createElement("p");
    description.setAttribute("id", "description");
    var desctext = document.createTextNode("Choose an image");
    description.appendChild(desctext);
    var gallery = document.getElementById("imagegallery");
    insertAfter(placeholder, gallery);
    insertAfter(description, placeholder);
}