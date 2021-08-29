

function getHTTPObject() {
    if (typeof XMLHttpRequest == "undefined") {
        // alert("unsupport Ajax!");
        return false;
    }
    return new XMLHttpRequest();
}

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

function getNewContent() {
    var request = getHTTPObject();
    if (request) {
        request.open("GET", "example.txt", true);
        request.onreadystatechange = function() {
            if (request.readyState == 4) {
                var para = document.createElement("p");
                var txt = document.createTextNode(request.responseText);
                para.appendChild(txt);
                document.getElementById("new").appendChild(para);
            }
        };
        request.send(null);
    } else {
        alert("Sorry, your browser does not support XMLHttpRequest!");
    }
}

function getMethodTest() {
    var xhr = new XMLHttpRequest();
    if (xhr) {
        xhr.open("GET", "http://192.168.2.102:8080/api/v1/red", true);
        xhr.onreadystatechange = function() {
            if (xhr.readyState == 4) {
                var para = document.createElement("p");
                var txt = document.createTextNode(xhr.responseText);
                para.appendChild(txt);
                document.getElementById("new").appendChild(para);
            }
        };
        xhr.send(null);
    } else {
        alert("Sorry, your browser does not support XMLHttpRequest!");
    }
}

function postMethodTest() {
    var xhr = new XMLHttpRequest();
    if (xhr) {
        xhr.open("POST", "http://192.168.2.102:8080/api/v1/blue", true);
        xhr.onreadystatechange = function() {
            if (xhr.readyState == 4) {
                var para = document.createElement("p");
                var txt = document.createTextNode(xhr.responseText);
                para.appendChild(txt);
                document.getElementById("new").appendChild(para);
            }
        };
        xhr.send("Hello World");
    } else {
        alert("Sorry, your browser does not support XMLHttpRequest!");
    }
}