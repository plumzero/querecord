
// Create a serialized representation of an array, a plain object, or a jQuery object suitable for 
// use in a URL query string or Ajax request. In case a jQuery object is passed, it should contain 
// input elements with name/value properties.

$(document).ready(function() {
    $("#param1 .trigger").click(function() {
        var params = { width: 1680, height: 1050 };
        var str = jQuery.param(params);
        $("#param1 #result").text(str);
    });

    $("#param2 .trigger").click(function() {
        var str = $.param({ a: [ 2, 3, 4 ] });
        str += "<br>";
        str += $.param({ a: { b: 1, c: 2 }, d: [ 3, 4, { e: 5 } ] });
        $("#param2 #result").append(str);
    });
});

// Note: Only "successful controls" are serialized to the string. No submit button value is 
// serialized since the form was not submitted using a button. 
// For a form element's value to be included in the serialized string, the element must have a 
// name attribute.
// Values from checkboxes and radio buttons (inputs of type "radio" or "checkbox") are included 
// only if they are checked. Data from file select elements is not serialized.

// Serialize a form to a query string that could be sent to a server in an Ajax request.
$(document).ready(function() {
    function showValues() {
        var str = $("#serialize form").serialize();
        console.log(str);
        $("#serialize #result").text(str);
    }

    $("#serialize input[type='checkbox'], input[type='radio']").on("click", showValues);
    $("#serialize select").on("change", showValues);
});

// The .serializeArray() method uses the standard W3C rules for successful controls to determine 
// which elements it should include; in particular the element cannot be disabled and must contain 
// a name attribute. 
// No submit button value is serialized since the form was not submitted using a button. Data from 
// file select elements is not serialized. Elements that do not contain a value attribute are 
// represented with the empty string value.
$(document).ready(function() {
    function showValues2() {
        var fields = $("#serializeArray :input").serializeArray();
        $("#serializeArray #result").empty();
        jQuery.each(fields, function(i, field) {
            $("#serializeArray #result").append(field.value + " ");
            console.log();
        });
    }

    $("#serializeArray :checkbox, #serializeArray :radio").click(showValues2);
    $("#serializeArray select").change(showValues2);
});
