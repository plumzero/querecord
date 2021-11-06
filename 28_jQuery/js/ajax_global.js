
// ---------------------------
// ----- .ajaxComplete() -----
// ---------------------------

// Type: Function( Event event, jqXHR jqXHR, PlainObject ajaxOptions )

$(document).ready(function() {
    $("#complete .trigger").click(function() {
        $("#complete .result").load("ajax/test.html");
    });
});

// When the user clicks the element with class trigger and the Ajax request completes, the log
// message is displayed.
$(document).ajaxComplete(function(){
    $("#complete .log").text("Triggered ajaxComplete handler.");
});

// All ajaxComplete handlers are invoked, regardless of what Ajax request was completed. If you must
// differentiate between the requests, use the parameters passed to the handler. 
// Each time an ajaxComplete handler is executed, it is passed the event object, the XMLHttpRequest
// object, and the settings object that was used in the creation of the request. 
// For example, you can restrict the callback to only handling events dealing with a particular URL:
$(document).ajaxComplete(function(event, xhr, settings) {
    if (settings.url === "ajax/test.html") {
        $("#complete .log").text("Triggered ajaxComplete handler. The result is " + xhr.responseText);
    }
});

// Show a message when an Ajax request completes.
$(document).ajaxComplete(function(event, xhr, settings) {
    $("#complete #msg").append("<li>Request Complete.  url = " + settings.url + "</li>");
});

// If $.ajax() or $.ajaxSetup() is called with the global option set to false, the .ajaxComplete() method
// will not fire. 

// ------------------------
// ----- .ajaxError() -----
// ------------------------

// Type: Function( Event event, jqXHR jqXHR, PlainObject ajaxSettings, String thrownError )

// Whenever an Ajax request completes with an error, jQuery triggers the ajaxError event. Any and all
// handlers that have been registered with the .ajaxError() method are executed at this time. 
// Note: This handler is not called for cross-domain script and cross-domain JSONP requests.

$(document).ajaxError(function() {
    $("#error .log").text("Triggered ajaxError handler.");
});

// Now, make an Ajax request using any jQuery method.
// When the user clicks the button and the Ajax request fails, because the requested file is missing, 
// the log message is displayed.
$(document).ready(function() {
    $("#error .trigger").click(function() {
        $("#error .result").load("ajax/missing.html");
    });
});

// All ajaxError handlers are invoked, regardless of what Ajax request was completed. To differentiate
// between the requests, use the parameters passed to the handler. Each time an ajaxError handler is 
// executed, it is passed the event object, the jqXHR object (prior to jQuery 1.5, the XHR object), and
// the settings object that was used in the creation of the request. When an HTTP error occurs, the fourth 
// argument (thrownError) receives the textual portion of the HTTP status, such as "Not Found" or "Internal 
// Server Error."
// For example, to restrict the error callback to only handling events dealing with a particular URL:
$(document).ajaxError(function(event, jaxhr, settings, thrownError) {
    if ( settings.url == "ajax/missing.html" ) {
        $( "#error .log" ).text( "Triggered ajaxError handler." + thrownError);
    }
});

// Show a message when an Ajax request fails.
$(document).ajaxError(function(event, request, settings) {
    $("#complete #msg").append("<li>Error requesting page " + settings.url + "</li>");
});

// If $.ajax() or $.ajaxSetup() is called with the global option set to false, the .ajaxError() method
// will not fire. 


// -----------------------
// ----- .ajaxSend() -----
// -----------------------

// Type: Function( Event event, jqXHR jqXHR, PlainObject ajaxOptions )

// Whenever an Ajax request is about to be sent, jQuery triggers the ajaxSend event. Any and all handlers
// that have been registered with the .ajaxSend() method are executed at this time.

// Attach the event handler to the document:
$(document).ajaxSend(function() {
    $("#send .log").text("Triggered ajaxSend handler.");
});

// Now, make an Ajax request using any jQuery method:
$(document).ready(function() {
    $("#send .trigger").click(function() {
        $("#send .result").load("ajax/test.html");
    });
});

// When the user clicks the element with class trigger and the Ajax request is about to begin, the log 
// message is displayed.

// All ajaxSend handlers are invoked, regardless of what Ajax request is to be sent. If you must differentiate 
// between the requests, use the parameters passed to the handler. Each time an ajaxSend handler is executed, 
// it is passed the event object, the jqXHR object (in version 1.4, XMLHttpRequestobject), and the settings 
// object that was used in the creation of the Ajax request. 
// For example, you can restrict the callback to only handling events dealing with a particular URL:
$(document).ajaxSend(function(event, jqxhr, settings) {
    if (settings.url == "ajax/test.html") {
        $("#send .log").text("Triggered ajaxSend handler.(another)");
    }
});

// Show a message before an Ajax request is sent.
$(document).ajaxSend(function(event, request, settings) {
    $("#send #msg").append("<li>Starting request at " + settings.url + "</li>");
});

// If $.ajax() or $.ajaxSetup() is called with the global option set to false, the .ajaxSend() method
// will not fire. 

// ------------------------
// ----- .ajaxStart() -----
// ------------------------

// Type: Function()

// Whenever an Ajax request is about to be sent, jQuery checks whether there are any other outstanding Ajax 
// requests. If none are in progress, jQuery triggers the ajaxStart event. Any and all handlers that have been 
// registered with the .ajaxStart() method are executed at this time.

// Attach the event handler to any element:
$(document).ajaxStart(function() {
    $("#start .log").text("Triggered ajaxStart handler");
});

// Now, make an Ajax request using any jQuery method:
$(document).ready(function() {
    $("#start .trigger").click(function() {
        $("#start .result").load("ajax/test.html");
    });
});
// When the user clicks the element with class trigger and the Ajax request is sent, the log message is 
// displayed.

// Show a loading message whenever an Ajax request starts (and none is already active).
$(document).ajaxStart(function() {
    $("#loading").show();
});

// If $.ajax() or $.ajaxSetup() is called with the global option set to false, the .ajaxStart() method 
// will not fire. 

// ------------------------
// ----- .ajaxStop() -----
// ------------------------

// Type: Function()

// Whenever an Ajax request completes, jQuery checks whether there are any other outstanding Ajax requests. 
// If none remain, jQuery triggers the ajaxStop event. Any and all handlers that have been registered with 
// the .ajaxStop() method are executed at this time. 
// The ajaxStop event is also triggered if the last outstanding Ajax request is cancelled by returning false 
// within the beforeSend callback function. 

// Attach the event handler to the document:
$(document).ajaxStop(function() {
    $("#stop .log").text("Triggered ajaxStop handler.");
});

// Now, make an Ajax request using any jQuery method:
$(document).ready(function() {
    $("#stop .trigger").click(function() {
        $("#stop .result").load("ajax/test.html");
    });
});
// When the user clicks the element with class trigger and the Ajax request completes, the log message is 
// displayed.

// Hide a loading message after all the Ajax requests have stopped.
$(document).ajaxStop(function() {
    $("loading").hide();
});

// If $.ajax() or $.ajaxSetup() is called with the global option set to false, the .ajaxStop() method will
// not fire.

// ------------------------
// ----- .ajaxSuccess() -----
// ------------------------

// Type: Function( Event event, jqXHR jqXHR, PlainObject ajaxOptions, PlainObject data )

// Whenever an Ajax request completes successfully, jQuery triggers the ajaxSuccess event. Any and all handlers that have been registered with the .ajaxSuccess() method are executed at this time.

// Attach the event handler to any element:
$(document).ajaxSuccess(function() {
    $("#success .log").text("Triggered ajaxSuccess handler.");
});

// Now, make an Ajax request using any jQuery method:
$(document).ready(function() {
    $("#success .trigger").on("click", function() {
        $("#success .result").load("ajax/test.html");
    });
});
// When the user clicks the element with class trigger and the Ajax request completes successfully, the log 
// message is displayed.

// All ajaxSuccess handlers are invoked, regardless of what Ajax request was completed. If you must 
// differentiate between the requests, you can use the parameters passed to the handler. Each time an 
// ajaxSuccess handler is executed, it is passed the event object, the XMLHttpRequest object, and the settings 
// object that was used in the creation of the request.
// For example, you can restrict the callback to only handling events dealing with a particular URL:
$(document).ajaxSuccess(function(event, xhr, settings) {
    if (settings.url == "ajax/test.html") {
      $("#success .log").text("Triggered ajaxSuccess handler. The Ajax response was: " +
        xhr.responseText);
    }
});
// Note: You can get the returned Ajax contents by looking at xhr.responseXML or xhr.responseText for xml and 
// html respectively.

// Show a message when an Ajax request completes successfully.
$(document).ajaxSuccess(function(event, request, settings) {
    $("#success #msg").append("<li>Successful Request!</li>");
});

// If $.ajax() or $.ajaxSetup() is called with the global option set to false, the .ajaxSuccess() method will 
// not fire. 
