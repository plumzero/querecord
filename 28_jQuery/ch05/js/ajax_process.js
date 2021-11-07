
$(document).ready(function() {
    // Save some data to the server and notify the user once it's complete.
    $("#post_nofify .trigger").click(function() {
        $.ajax({
            method: "POST",
            url: "post_nofify",
            data: { name: "John", location: "Boston" }
        })
        .done(function(msg) {
            alert("Data Saved: " + msg);
        });
    });
});