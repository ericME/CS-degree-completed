<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connect to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","rousee-db","t8AVZ0LHCDilxZdU","rousee-db");
if($mysqli->connect_errno){
	echo "database connection error!!! It is: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
if(!($stmt = $mysqli->prepare("DELETE FROM positions WHERE busNo = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("i",$_POST['BusNum']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} 	
if(!($stmt = $mysqli->prepare("INSERT INTO positions(pID, busNo, lat, lng, tmstp, accuracy) VALUES (NULL,?,?,?,NULL,?)"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("iddi",$_POST['BusNum'],$_POST['Lat'],$_POST['Lng'],$_POST['Acc']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Added " . $stmt->affected_rows . " rows to positions.";
}
?>
<!-- HTML START !-->
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<html>
<body>
<p>
<a href="index.php#positions">go back</a>
</p>