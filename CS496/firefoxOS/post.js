// DOMContentLoaded is fired once the document has been loaded and parsed,
// but without waiting for other external resources to load (css/images/etc)
// That makes the app more responsive and perceived as faster.
// https://developer.mozilla.org/Web/Reference/Events/DOMContentLoaded
window.addEventListener('DOMContentLoaded', function() {

  // We'll ask the browser to use strict code to help us catch errors earlier.
  // https://developer.mozilla.org/Web/JavaScript/Reference/Functions_and_function_scope/Strict_mode
  'use strict';

  var apiURL = 'https://rothbowl.herokuapp.com/api';
  var errorMsg = document.getElementById('error');
  var searchInput = document.getElementById('term');
  var results = document.getElementById('results');
  var request = null;
  var form = document.querySelector('form');

  // Forms will take the values in the input fields they contain
  // and send them to a server for further processing,
  // but since we want to stay in this page AND make a request to another server,
  // we will listen to the 'submit' event, and prevent the form from doing what
  // it would usually do, using preventDefault.
  // Read more about it here:
  // https://developer.mozilla.org/Web/API/event.preventDefault
  //
  // Then we search without leaving this page, just as we wanted.
  form.addEventListener('submit', function(e) {
      e.preventDefault();
      search();
  }, false);

  // ---

  function search() {

    // Are we searching already? Then stop that search
    if(request && request.abort) {
      request.abort();
    }


    results.textContent = 'working';

    // We will be using the 'hidden' attribute throughout the app rather than a
    // 'hidden' CSS class because it enhances accessibility.
    // See: http://www.whatwg.org/specs/web-apps/current-work/multipage/editing.html#the-hidden-attribute
    results.hidden = false;
    errorMsg.hidden = true;


    var term = searchInput.value;
    if(term.length === 0) {
      term = searchInput.placeholder;
    }

    var url = apiURL;
    var params = term;

    // If you don't set the mozSystem option, you'll get CORS errors (Cross Origin Resource Sharing)
    // You can read more about CORS here: https://developer.mozilla.org/docs/HTTP/Access_control_CORS
    request = new XMLHttpRequest({ mozSystem: true });

    request.open('POST', url, true);
    request.responseType = 'text';

    // We're setting some handlers here for dealing with both error and
    // data received. We could just declare the functions here, but they are in
    // separate functions so that search() is shorter, and more readable.
    request.addEventListener('error', onRequestError);
    request.addEventListener('load', onRequestLoad);

    
    request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    request.setRequestHeader("Content-length", params.length);
    request.setRequestHeader("Connection", "close");
    request.send(params);

  }


  function onRequestError() {

    var errorMessage = request.error;
      if(!errorMessage) {
        errorMessage = 'searching_error';
      }
      showError(errorMessage);

  }


  function onRequestLoad() {

    var response = request.response;
    if (this.readystate === 5){
      console.log("here");
    }

    if(response === null) {
      showError(translate('searching_error'));
      return;
    }

    results.textContent = response;

    // And once we have all the content in place, we can show it.
    results.hidden = false;

  }


  function showError(text) {
    errorMsg.textContent = text;
    errorMsg.hidden = false;
    results.hidden = true;
  }

});
