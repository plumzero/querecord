$(document).ready(function() {
    $('#submit').click(function() {
        var d = {};
        var t = $('form').serializeArray();
        $.each(t, function() {
            d[this.name] = this.value;
            console.log(this.name, this.value);
        });
        alert(JSON.stringify(d));
    });
});