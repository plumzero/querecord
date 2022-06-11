$(document).ready(function(){
    $('#submit').on("click", function() {
        $.ajax({
            type: "get",
            data: {},
            contentType: "application/json",
            url: "http://api.wpbom.com/api/ancien.php?msg=静夜思&b=1",
            beforeSend: function() {
                $('#submit').attr({disabled: "disabled"});
            },
            success: function(data) {
				console.log(data);
            },
            complete: function() {
                $('#submit').removeAttr("disabled");
            },
            error: function() {
                alert("error occured!");
            }
        });
    });
});