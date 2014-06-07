<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connect to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","rousee-db","t8AVZ0LHCDilxZdU","rousee-db");
if($mysqli->connect_errno){
	echo "database connection error!!! It is: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
if(!($stmt = $mysqli->prepare("INSERT INTO route2 () VALUES (?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("s",$_POST['StopName']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " rows to route2.";
}
?>
<!-- HTML START !-->
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<html>
<body>
<p>
<a href="routes.php">go back</a>
</p>