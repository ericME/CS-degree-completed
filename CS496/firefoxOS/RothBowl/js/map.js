$(document).ready(function(){
    $("#btnShowMap").click(function(){
            $.mobile.changePage ($("#view-position"));
            if ("geolocation" in navigator) {
                function geo_success(position) {
                  $("#position").html("");
                    var element = $("<div data-role='collapsible' data-mini='true'/>");
                    var h3Title = $("<h3/>").text("latitude");
                    var pDetails = $("<p/>").text(position.coords.latitude);
                    element.append(h3Title);
                    element.append(pDetails);
                    $("#position").append(element);
                    $('div[data-role=collapsible]').collapsible({refresh:true});
                    element = $("<div data-role='collapsible' data-mini='true'/>");
                    h3Title = $("<h3/>").text("longitude");
                    pDetails = $("<p/>").text(position.coords.longitude);
                    element.append(h3Title);
                    element.append(pDetails);
                    $("#position").append(element);
                    $('div[data-role=collapsible]').collapsible({refresh:true});
                    element = $("<div data-role='collapsible' data-mini='true'/>");
                    h3Title = $("<h3/>").text("accuracy");
                    pDetails = $("<p/>").text(position.coords.accuracy);
                    element.append(h3Title);
                    element.append(pDetails);
                    $("#position").append(element);
                    $('div[data-role=collapsible]').collapsible({refresh:true});
                    element = $("<div data-role='collapsible' data-mini='true'/>");
                    h3Title = $("<h3/>").text("altitude");
                    pDetails = $("<p/>").text(position.coords.altitude);
                    element.append(h3Title);
                    element.append(pDetails);
                    $("#position").append(element);
                    $('div[data-role=collapsible]').collapsible({refresh:true});
                    element = $("<div data-role='collapsible' data-mini='true'/>");
                    h3Title = $("<h3/>").text("all");
                    pDetails = $("<p/>").text("latitude: " + position.coords.latitude);
                    element.append(h3Title);
                    element.append(pDetails);
                    pDetails = $("<p/>").text("longitude: " + position.coords.longitude)
                    element.append(pDetails);
                    pDetails = $("<p/>").text("accuracy: " + position.coords.accuracy)
                    element.append(pDetails);
                    pDetails = $("<p/>").text("altitude: " + position.coords.altitude)
                    element.append(pDetails);
                    $("#position").append(element);
                    $('div[data-role=collapsible]').collapsible({refresh:true});
                }

                function geo_error() {
                  alert("Sorry, no position available.");
                }

                var geo_options = {
                  enableHighAccuracy: true, 
                  maximumAge        : 300000, 
                  timeout           : 270000
                };

                var wpid = navigator.geolocation.watchPosition(geo_success, geo_error, geo_options);
            } else {
              /* geolocation IS NOT available */
              alert("geolocation is not available on this device");
            }
        });
});


$("#note-list").html("");
          //Read the notes
          for (i=0; i<=localStorage.length-1; i++)  
            {  
                key = localStorage.key(i);  
                val = localStorage.getItem(key);
                var noteElement = $("<div data-role='collapsible' data-mini='true'/>");
                var h3NoteTitle = $("<h3/>").text(key);
                var pNoteDetails = $("<p/>").text(val);
                noteElement.append(h3NoteTitle);
                noteElement.append(pNoteDetails);
                $("#note-list").append(noteElement);
            }  
            $('div[data-role=collapsible]').collapsible({refresh:true});