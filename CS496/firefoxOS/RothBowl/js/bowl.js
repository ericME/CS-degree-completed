$(document).ready(function(){
       $("#btnAddBowl").click(function(){
              //Change to the add-bowls
              $.mobile.changePage ($("#add-bowls"));
          });

          $("#btnViewBowls").click(function(){
              //Change to the add-bowls
              $.mobile.changePage ($("#view-bowls"));
              //Empty the list first
              $("#bowl-list").html("");
              //Read the bowls
                  var url = "https://rothbowl.herokuapp.com/api/bowl";

                  // If you don't set the mozSystem option, you'll get CORS errors (Cross Origin Resource Sharing)
                  // You can read more about CORS here: https://developer.mozilla.org/docs/HTTP/Access_control_CORS
                  request = new XMLHttpRequest({ mozSystem: true });

                  request.open('get', url, true);
                  request.responseType = 'text';

                  request.onreadystatechange = function() {//Call a function when the state changes.
                    if(request.readyState == 4 && request.status == 200) {
                      //alert(request.responseText);
                      alert("Bowls Loaded from Rothbowl API");
                      var bowlElement = $("<div data-role='collapsible' data-mini='true'/>");
                      var h3BowlTitle = $("<h3/>").text("API Bowl List");
                      var pBowlDetails = $("<p/>").text(request.responseText);
                      bowlElement.append(h3BowlTitle);
                      bowlElement.append(pBowlDetails);
                      $("#bowl-list").append(bowlElement);    
                      $('div[data-role=collapsible]').collapsible({refresh:true});
                    }
                  }

                  request.send();
                  
          });
          
          //Click Handlers for Add Bowls page
          $("#btnSaveBowl").click(function(){
                  //bowl-add=True&name=_&favorite=_&underdog=_
              	bowlName = $("#bowlName").val();
              	bowlT1Name = $("#bowlT1Name").val();
                bowlT2Name = $("#bowlT2Name").val();
              	var url = "https://rothbowl.herokuapp.com/api";
    	        var params = "bowl-add=True&name="+bowlName+"&favorite="+bowlT1Name+"&underdog="+bowlT2Name;

    	        // If you don't set the mozSystem option, you'll get CORS errors (Cross Origin Resource Sharing)
    	        // You can read more about CORS here: https://developer.mozilla.org/docs/HTTP/Access_control_CORS
    	        request = new XMLHttpRequest({ mozSystem: true });

    	        request.open('POST', url, true);
    	        request.responseType = 'text';
    	        
    	        request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    	        request.setRequestHeader("Content-length", params.length);
    	        request.setRequestHeader("Connection", "close");
    	        request.onreadystatechange = function() {//Call a function when the state changes.
                    if(request.readyState == 4 && request.status == 200) {
                      //alert(request.responseText);
                      alert("Your bowl has been saved to rothbowl via the API");
                      
                    }
                  }
    	        request.send(params);
          	

          });
          
          $("#btnUpdateBowl").click(function(){
              //patch=True&member-type=bowl&member-id=_)&key=name&val=_super
              bowlName = $("#bowlName").val();
              bowlT1Name = $("#bowlT1Name").val();
              bowlT2Name = $("#bowlT2Name").val();
              bowlID = $("#bowlID").val();
              var url = "https://rothbowl.herokuapp.com/api";
              var params = "patch=True&member-type=bowl&member-id="+bowlID+"&key=name&val="+bowlName;

              // If you don't set the mozSystem option, you'll get CORS errors (Cross Origin Resource Sharing)
              // You can read more about CORS here: https://developer.mozilla.org/docs/HTTP/Access_control_CORS
              request = new XMLHttpRequest({ mozSystem: true });

              request.open('POST', url, true);
              request.responseType = 'text';
              
              request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
              request.setRequestHeader("Content-length", params.length);
              request.setRequestHeader("Connection", "close");
              request.onreadystatechange = function() {//Call a function when the state changes.
                    if(request.readyState == 4 && request.status == 200) {
                      //alert(request.responseText);
                      alert("Your bowl has been updated on rothbowl via the API");
                      
                    }
                  }
              request.send(params);
            

          });

          $("#btnDeleteBowl").click(function(){
              //delete=True&member-type=bowl&member-id=_
              bowlID = $("#bowlID").val();
              var url = "https://rothbowl.herokuapp.com/api";
              var params = "delete=True&member-type=bowl&member-id="+bowlID;

              // If you don't set the mozSystem option, you'll get CORS errors (Cross Origin Resource Sharing)
              // You can read more about CORS here: https://developer.mozilla.org/docs/HTTP/Access_control_CORS
              request = new XMLHttpRequest({ mozSystem: true });

              request.open('POST', url, true);
              request.responseType = 'text';
              
              request.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
              request.setRequestHeader("Content-length", params.length);
              request.setRequestHeader("Connection", "close");
              request.onreadystatechange = function() {//Call a function when the state changes.
                    if(request.readyState == 4 && request.status == 200) {
                      //alert(request.responseText);
                      alert("Your bowl has been deleted from rothbowl via the API");
                      
                    }
                  }
              request.send(params);
            

          });

          $("#btnClearBowl").click(function(){
              $("#bowlName").val("");
              $("#bowlT1Name").val("");
              $("#bowlT2Name").val("");
              $("#bowlID").val("");
              $("#bowlTitle").focus();
          });
          


});