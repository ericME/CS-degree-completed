<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

$hdr = '<!DOCTYPE html>
        <html lang = "en">
          <head>
            <meta charset="UTF-8">
            <title>content 1 PHP</title>
            <link rel='."stylesheet".' href='."./style.css".' type='."text/css".' media='."all".' />
            <script src='."login.js".'></script>
          </head>
          <body>
          <div id="content">';

$ftr = '
  </body>
</html>';

include 'pass.php';
$mysqli = new mysqli("mysql.eecs.oregonstate.edu", "cs419-g6", $db_pass, "cs419-g6");
if ($mysqli->connect_errno){
    echo "Database connection failed: (" . $mysqli->connect_errno . ")" . $mysqli->connect_error;
} 


//actual view generation...
echo $hdr;
echo 'pass';
echo $ftr;
?>
    
