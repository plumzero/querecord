
function styleHeaderSiblings() {
    if (!document.getElementsByTagName) return false;
    var headers = document.getElementsByTagName("h1");
    var elem;
    for (var i = 0; i < headers.length; i++) {
        elem = getNextElement(headers[i].nextSibling);
        elem.style.fontWeight = "bold";
        elem.style.fontSize = "1.2em";
        elem.style.color = "red";
    }
}

function styleHeaderSiblingsSetByClass() {
    if (!document.getElementsByTagName) return false;
    var headers = document.getElementsByTagName("h1");
    var elem;
    for (var i = 0; i < headers.length; i++) {
        elem = getNextElement(headers[i].nextSibling);
        addClass(elem, "intro");
    }
}


// 寻找指定节点的下一个元素节点
function getNextElement(node) {
    if (node.nodeType == 1) {
        return node
    }
    if (node.nextSibling) {
        return getNextElement(node.nextSibling);
    }
    return null;
}

function addClass(element, value) {
    if (!element.className) {
        element.className = value;
    } else {
        newClassName = element.className;
        netClassName += " ";
        newClassName += value;
        element.className = newClassName;
    }
}

addLoadEvent(styleHeaderSiblingsSetByClass);
