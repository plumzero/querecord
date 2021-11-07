
// $.get(): 从服务器文件(.xml)中获取数据，于 B 端解析并嵌入到页面中
$(document).ready(function() {
    $('#get-xml .trigger').click(function(event) {
        event.preventDefault();
        $.get('ajax/get.xml', function(data) {
            $('#get-xml #dictionary').empty();
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
                $('#get-xml #dictionary').append($(html));
            });
        });
    });
});

// $.getJSON(): 从服务器文件(.json)中获取数据，于 B 端解析并嵌入到页面中
$(document).ready(function() {
    $('#get-json .trigger').click(function(event) {
        event.preventDefault();
        $.getJSON('ajax/getJSON.json', function(data) {
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
            $('#get-json #dictionary').html(html);
        });
    });
});

// $.getScript(): 从服务器文件(.js)中获取数据，于 B 端解析并嵌入到页面中
$(document).ready(function() {
    $('#get-script .trigger').click(function(event) {
        event.preventDefault();
        $.getScript('/ajax/getScript.js');
    });
});

// $.load(): 从服务器文件(.html)中获取数据，并嵌入到页面中
$(document).ready(function() {
    $('#load .trigger').click(function(event) {
        event.preventDefault();
        $('#load #dictionary').load('/ajax/load.html');
    });
});

// $.get(): 获取数据
$(document).ready(function(){
    $('#get .trigger').click(function(event) {
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
                $('#get #dictionary').append(html);

                return false;
            }
        });
    });
});

// $.post(): 发送并获取数据
$(document).ready(function(){
    $('#post .trigger').click(function(event) {
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
                $('#post #dictionary').append(html);

                return false;
            }
        });
    });
});