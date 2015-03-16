$(document).ready(function(){

    function refresh(){
       $("#returned_data").html("Fetching...");
        url = "https://rothbowl.herokuapp.com/api";
        params = "user-data=True&request_type=get&username="+localStorage.getItem('username');
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
                //items = request.responseText.slice(1,-1);
                items = request.responseText.replace(/ /g, "");
                items = items.replace(/'/g, "\"");
                //console.log(items);
                items = JSON.parse(items);
                $("#returned_data").html("<strong>username: </strong>" + items.username + "<br>"
                    + "<strong>Stored Item 1: </strong>" + items.data1 + "<br>"
                    + "<strong>Stored Item 2: </strong>" + items.data2 + "<br>"
                    + "<strong>Stored Item 3: </strong>" + items.data3 + "<br>"
                    );
            }
        }
        request.send(params); 
    }
        
   $("#btnRemoteData").click(function(){
      //Change to the add-players
        $.mobile.changePage ($("#add-data"));
    });

   $("#btnGetData").click(function(){
        refresh();
    });
    
    
    $("#btnSaveData").click(function(){

        url = "https://rothbowl.herokuapp.com/api";
        params = "user-data=True&request_type=put&username="+localStorage.getItem('username')+
        "&data1="+$("#data1").val()+"&data2="+$("#data2").val()+"&data3="+$("#data3").val();
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
                //items = request.responseText.slice(1,-1);
                items = request.responseText.replace(/ /g, "");
                items = items.replace(/'/g, "\"");
                //console.log(items);
                items = JSON.parse(items);
                $("#returned_data").html("<strong>username: </strong>" + items.username + "<br>"
                    + "<strong>Stored Item 1: </strong>" + items.data1 + "<br>"
                    + "<strong>Stored Item 2: </strong>" + items.data2 + "<br>"
                    + "<strong>Stored Item 3: </strong>" + items.data3 + "<br>"
                    );
            }
        }
        request.send(params); 

    });

    $("#btnDeleteData").click(function(){
        url = "https://rothbowl.herokuapp.com/api";
        params = "user-data=True&request_type=put&username="+localStorage.getItem('username')+
        "&data1=&data2=&data3=";
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
                //items = request.responseText.slice(1,-1);
                items = request.responseText.replace(/ /g, "");
                items = items.replace(/'/g, "\"");
                //console.log(items);
                items = JSON.parse(items);
                $("#returned_data").html("<strong>username: </strong>" + items.username + "<br>"
                    + "<strong>Stored Item 1: </strong>" + items.data1 + "<br>"
                    + "<strong>Stored Item 2: </strong>" + items.data2 + "<br>"
                    + "<strong>Stored Item 3: </strong>" + items.data3 + "<br>"
                    );
            }
        }
        request.send(params); 
    });

    $("#btnClearData").click(function(){
      $("#data1").val("");
      $("#data2").val("");
      $("#data3").val("");
      $("#data1").focus();
    });
        


});