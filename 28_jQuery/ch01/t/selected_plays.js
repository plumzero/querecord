
$(document).ready(function() {
    $('#selected-plays > li').addClass('horizontal');
    // 通过否定式伪类选择符来识别没有 horizontal 类的所有列表项
    $('#selected-plays li:not(.horizontal)').addClass('sub-level');
});

$(document).ready(function() {
    $('a[href^="mailto:"]').addClass('mailto');
    $('a[href$=".pdf"]').addClass('pdflink');
    $('a[href^="http"][href*="henry"]').addClass('henrylink');
});

$('a').filter(function() {
    return this.hostname && this.hostname != location.hostname;
}).addClass('external');
