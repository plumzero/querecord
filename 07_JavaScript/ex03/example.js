
function insertByWrite(text) {
    var str = "<p>";
    str += text;
    str += "</p>";
    document.write(str);
}

function insertByInnerHTML() {
    var testdiv = document.getElementById("testdiv");
    testdiv.innerHTML = "<p>I inserted <em>this</em> content.</p>";
}

function insertByDOM() {
    var para = document.createElement("p");
    var txt = document.createTextNode("Hello world");
    para.appendChild(txt);
    var testdiv = document.getElementById("testdiv");
    testdiv.appendChild(para);
}