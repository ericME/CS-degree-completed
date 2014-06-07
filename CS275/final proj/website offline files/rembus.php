<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connect to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","rousee-db","t8AVZ0LHCDilxZdU","rousee-db");
if($mysqli->connect_errno){
	echo "database connection error!!! It is: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
//bus positions relationship update
if(!($stmt = $mysqli->prepare("DELETE FROM positions WHERE busNo = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("i",$_POST['BusID']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Deleted " . $stmt->affected_rows . " rows from positions. ";
}

//bus routes relationship update
if(!($stmt = $mysqli->prepare("UPDATE routes SET bus = NULL WHERE bus = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("i",$_POST['BusID']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Updated " . $stmt->affected_rows . " rows from routes. ";
}


//bus and driver relationship update
if(!($stmt = $mysqli->prepare("DELETE FROM busanddriver WHERE bus = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("i",$_POST['BusID']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Deleted " . $stmt->affected_rows . " rows from busanddrivers. ";
}

//bus db update
if(!($stmt = $mysqli->prepare("DELETE FROM buses WHERE busNo = ?"))){
	echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!($stmt->bind_param("i",$_POST['BusID']))){
	echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
}
if(!$stmt->execute()){
	echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
} else {
	echo "Deleted " . $stmt->affected_rows . " rows from buses.";
}
?>

<!-- HTML START !-->
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
<html>
<body>
<p>
<a href="index.php#buses">go back</a>
</p>