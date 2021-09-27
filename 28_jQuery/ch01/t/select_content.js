$(document).ready(function() {
    $('tr:nth-child(odd)').addClass('alt');
    $('td:contains(Henry)').parent().children().addClass('highlight');
});
