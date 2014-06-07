<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connect to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","rousee-db","t8AVZ0LHCDilxZdU","rousee-db");
if($mysqli->connect_errno){
	echo "database connection error!!! It is: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	
if(!($stmt = $mysqli->prepare("UPDATE busanddriver SET driver = ? WHERE bus = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("ii",$_POST['DrvID'],$_POST['BusID']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Changed " . $stmt->affected_rows . " rows.";
}
?>

<!-- HTML START !-->
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<html>
<body>
<p>
<a href="index.php#buses">go back</a>
</p>