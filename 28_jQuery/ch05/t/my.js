// 数据在 html 中
$(document).ready(function() {
    $('#letter-a div').click(function(event) {
        event.preventDefault();
        $('#dictionary').load('a.html');
    });
});

// 数据在 json 中
$(document).ready(function() {
    $('#letter-b div').click(function(event) {
        event.preventDefault();
        $.getJSON('b.json', function(data) {
            var html = '';
            $.each(data, function(entryIndex, entry) {
                html += '<div class="entry">';
                html += '<h3 class="term">' + entry.term + '</h3>';
                html += '<div class="part">' + entry.part + '</div>';
                html += '<div class="definition">';
                html += entry.definition;
                if (entry.quote) {
                    html += '<div class="quote">';
                    $.each(entry.quote, function(lineIndex, line) {
                        html += '<div class="quote-line">' + line + '</div>';
                    });
                    if (entry.author) {
                        html += '<div class="quote-author">' + entry.author + '</div>';
                    }
                    html += '</div>';
                }
                html += '</div>';
                html += '</div>';
            });
            $('#dictionary').html(html);
        });
    });
});

// 通过 jQuery 直接加载 .js 文件
$(document).ready(function() {
    $('#letter-c div').click(function(event) {
        event.preventDefault();
        $.getScript('c.js');
    });
});


// 数据在 xml 中
$(document).ready(function() {
    $('#letter-d div').click(function(event) {
        event.preventDefault();
        $.get('d.xml', function(data) {
            $('#dictionary').empty();
            $(data).find('entry').each(function() {
                var $entry = $(this);
                var html = '<div class="entry">';
                html += '<h3 class="term">' + $entry.attr('term');
                html += '</h3>';
                html += '<div class="part">' + $entry.attr('part');
                html += '</div>';
                html += '<div class="definition">';
                html += $entry.find('definition').text();
                var $quote = $entry.find('quote');
                if ($quote.length) {
                    html += '<div class="quote">';
                    $quote.find('line').each(function() {
                        html += '<div class="quote-line">';
                        html += $(this).text() + '</div>';
                    });
                    if ($quote.attr('author')) {
                        html += '<div class="quote-author">';
                        html += $quote.attr('author') + '</div>';
                    }
                    html += '</div>';
                }
                html += '</div>';
                html += '</div>';
                $('#dictionary').append($(html));
            });
        });
    });
});

// 通过 Ajax GET 数据
$(document).ready(function(){
    $('#letter-e div').click(function(event) {
        $.ajax({
            type: "GET",
            url: "/get",
            dataType: "json",
            success: function(data) {
                jdata = JSON.stringify(data);
                var html = '';
                $.each(JSON.parse(jdata), function(entryIndex, entry) {
                    html += '<div class="entry">';
                    html += '<h3 class="term">' + entry.term + '</h3>';
                    html += '<div class="part">' + entry.part + '</div>';
                    html += '<div class="definition">';
                    html += entry.definition;
                    if (entry.quote) {
                        html += '<div class="quote">';
                        $.each(entry.quote, function(lineIndex, line) {
                            html += '<div class="quote-line">' + line + '</div>';
                        });
                        if (entry.author) {
                            html += '<div class="quote-author">' + entry.author + '</div>';
                        }
                        html += '</div>';
                    }
                    html += '</div>';
                    html += '</div>';
                });
                $('#dictionary').append(html);

                return false;
            }
        });
    });
});

// 通过 Ajax POST 数据
$(document).ready(function(){
    $('#letter-f div').click(function(event) {
        $.ajax({
            type: "POST",
            url: "/post",
            dataType: "json",
            data: {
                appId: "101",
                userId: "xiaoming",
            },
            contentType: "application/x-www-form-urlencoded",
            success: function(data) {
                jdata = JSON.stringify(data);
                var html = '';
                $.each(JSON.parse(jdata), function(entryIndex, entry) {
                    html += '<div class="entry">';
                    html += '<h3 class="term">' + entry.term + '</h3>';
                    html += '<div class="part">' + entry.part + '</div>';
                    html += '<div class="definition">';
                    html += entry.definition;
                    if (entry.quote) {
                        html += '<div class="quote">';
                        $.each(entry.quote, function(lineIndex, line) {
                            html += '<div class="quote-line">' + line + '</div>';
                        });
                        if (entry.author) {
                            html += '<div class="quote-author">' + entry.author + '</div>';
                        }
                        html += '</div>';
                    }
                    html += '</div>';
                    html += '</div>';
                });
                $('#dictionary').append(html);

                return false;
            }
        });
    });
});