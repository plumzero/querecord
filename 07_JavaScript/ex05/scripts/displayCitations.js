
// 显式 "文献来源链接表"

function displayCitations() {
    var quotes = document.getElementsByTagName("blockquote");
    for (var i = 0; i < quotes.length; i++) {
        if (!quotes[i].getAttribute("cite")) continue;
        var url = quotes[i].getAttribute("cite");
        // 找出包含当前 blockquote 元素(即 quotes[i])所包含的全体元素节点
        var quoteChildren = quotes[i].getElementsByTagName("*");
        if (quoteChildren.length < 1) continue;
        var elem = quoteChildren[quoteChildren.length - 1];
        
        var link = document.createElement("a");
        var link_text = document.createTextNode("source");
        link.appendChild(link_text);
        link.setAttribute("href", url);

        var superscript = document.createElement("sup");
        superscript.appendChild(link);

        elem.appendChild(superscript);
    }
}

addLoadEvent(displayCitations);