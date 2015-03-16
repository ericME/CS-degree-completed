$(document).ready(function(){
    $("#login_message").html("");
    $("#btnLogOut").hide();
    $("#btnLoginNotes").hide();

    function create_request(username, password, type) {

        httpRequest = new XMLHttpRequest({ mozSystem: true });
        var type_par = "";
        if (type === 1){
            type_par = "&create=create_new"
        } else {
            type_par = "&login=login_user"
        }
        var parameters = "username=" + username + "&password=" + password + type_par;

        function alertContents() {
            if (httpRequest.readyState === 4) {
              if (httpRequest.status === 200) {
                var text = httpRequest.responseText;
                //alert("response: " + text);
                $("#login_message").html("server response:<br>"  + text);
                switch (text[0]){
                    case "0":
                        $("#btnLogOut").show();
                        $("#btnLoginNotes").show();
                        $("#username").hide();
                        $("#password").hide();
                        $("#btnLogIn").hide();
                        $("#btnNewUser").hide();
                        $("#login_message").html("Logged In!<br>Welcome, " + username + "!<br>");  
                        localStorage.setItem('username', username);
                        $.mobile.changePage ($("#note"));
                        break;
                    case "1":
                        $("#login_message").html("Someone is using that name already. Please try a different username; it must be unique.<br>");
                        break;
                    case "2":
                        $("#login_message").html("I can't find that username...did you type it right? It is case sensitive.<br>");
                        break;
                    case "3":
                        $("#login_message").html("The password you entered is incorrect.<br>");
                        break;
                    default:
                        console.log("ERROR");
                        alert("Fatal Login Error ... ");
                        break;
                }

            } else {
                alert('There was a problem with the server.');
                }
            }
        }

        function sendReq() {
            if(!httpRequest){
                throw 'Unable to create httpRequest';
            }
            
            httpRequest.open('POST', 'http://web.engr.oregonstate.edu/~rousee/CS496/ajaxlogin.php', true);
            httpRequest.responseType = 'text';
            httpRequest.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
            httpRequest.setRequestHeader("Content-length", parameters.length);
            httpRequest.setRequestHeader("Connection", "close");
            httpRequest.onreadystatechange = alertContents;
            httpRequest.send(parameters);
        }

        sendReq();
    }


    $("#btnLogIn").click(function(){
            u = $("#username").val();
            p = $("#password").val();
            if (u.length === 0){
                alert("You must enter a username.")
            } else if (p.length === 0){
                alert("You must enter a password.")
            } else {
                create_request(u, p, 0);
            }
        });

    $("#btnLogOut").click(function(){
            window.location = window.location;
        });

    $("#btnNewUser").click(function(){
            u = $("#username").val();
            p = $("#password").val();
            if (u.length === 0){
                alert("You must enter a username.")
            } else if (p.length === 0){
                alert("You must enter a password.")
            } else {
                create_request(u, p, 1);
            }
        });

    $("#btnLoginNotes").click(function(){
            $.mobile.changePage ($("#note"));
        });
});