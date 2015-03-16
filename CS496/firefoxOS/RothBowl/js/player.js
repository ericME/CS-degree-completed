$(document).ready(function(){
       $("#btnAddPlayer").click(function(){
          //Change to the add-players
          $.mobile.changePage ($("#add-players"));
        });

        $("#btnViewPlayers").click(function(){
          //Change to the add-players
          $.mobile.changePage ($("#view-players"));
          //Empty the list first
          $("#player-list").html("");
          //Read the players
            var url = "https://rothbowl.herokuapp.com/api/player";

            // If you don't set the mozSystem option, you'll get CORS errors (Cross Origin Resource Sharing)
            // You can read more about CORS here: https://developer.mozilla.org/docs/HTTP/Access_control_CORS
            request = new XMLHttpRequest({ mozSystem: true });

            request.open('get', url, true);
            request.responseType = 'text';

            request.onreadystatechange = function() {//Call a function when the state changes.
                if(request.readyState == 4 && request.status == 200) {
                    //alert(request.responseText);
                    alert("Players Loaded from Rothbowl API");
                    var playerElement = $("<div data-role='collapsible' data-mini='true'/>");
                    var h3PlayerTitle = $("<h3/>").text("API Player List");
                    var pPlayerDetails = $("<p/>").text(request.responseText);
                    playerElement.append(h3PlayerTitle);
                    playerElement.append(pPlayerDetails);
                    $("#player-list").append(playerElement);  
                    $('div[data-role=collapsible]').collapsible({refresh:true});
                }
            }

            request.send();
            
        });
        
        //Click Handlers for Add Players page
        $("#btnSavePlayer").click(function(){
            //player-add=True&fname=_&lname=_
          	playerFName = $("#playerFName").val();
          	playerLName = $("#playerLName").val();
          	var url = "https://rothbowl.herokuapp.com/api";
		    var params = "player-add=True&fname="+playerFName+"&lname="+playerLName;

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
                    alert("Your player has been saved to rothbowl via the API");
                    
                }
            }
		    request.send(params);
        	

        });
        
        $("#btnUpdatePlayer").click(function(){
            //player-add=True&fname=_&lname=_
          	playerFName = $("#playerFName").val();
          	playerLName = $("#playerLName").val();
          	playerID = $("#playerID").val();
          	var url = "https://rothbowl.herokuapp.com/api";
		    var params = "patch=True&member-type=player&member-id="+playerID+"&key=name&val="+playerFName+"%20"+playerLName;

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
                    alert("Your player has been updated on rothbowl via the API");
                    
                }
            }
		    request.send(params);
        	

        });

        $("#btnDeletePlayer").click(function(){
            //player-add=True&fname=_&lname=_
          	playerFName = $("#playerFName").val();
          	playerLName = $("#playerLName").val();
          	playerID = $("#playerID").val();
          	var url = "https://rothbowl.herokuapp.com/api";
            var params = "delete=True&member-type=player&member-id="+playerID;

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
                    alert("Your player has been updated on rothbowl via the API");
                    
                }
            }
		    request.send(params);
        	

        });

        $("#btnClearPlayer").click(function(){
          $("#playerFName").val("");
          $("#playerLName").val("");
          $("#playerID").val("");
          $("#playerFName").focus();
        });
        


});