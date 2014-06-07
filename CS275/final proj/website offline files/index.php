<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connect to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","rousee-db","t8AVZ0LHCDilxZdU","rousee-db");
if($mysqli->connect_errno){
	echo "database connection error!!! It is: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
?>
<!-- HTML START !-->
<!DOCTYPE html>
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="en">
	
	<head>
		<title>CS275 PHP Project</title>
		<style type="text/css" media="all">
			html {
				font-family: sans-serif;
				-webkit-text-size-adjust: 100%;
				-ms-text-size-adjust: 100%;
			}
			body {
				font-size: 1em;
				color: #FFFFB0;
				background-color: #000005;
			}
			h1 {
				margin: .2em 0;
				font-size: 2em;
				color: #AA5000;
			}
			h3 {
				color: #AA5000;
			}
			fieldset {
				padding: 0.35em 0.625em 0.75em;
				margin: 0 3px;
				border: 2px solid #AA5000;
			}
			legend {
				padding: 0;
				border: 0;
			}
			button, input, select, textarea {
				margin: 0;
				font-family: inherit;
				font-size: 150%;
			}
			table {
				margin-bottom: 2em;
			}
			td, th {
				border: 1px solid #999;
				padding: 0.1em 1em;
			}
	
		</style>
		
	</head>
	<body>
	<div>
		<!-- basic data !-->
		<h1>CS275 Final Project</h1>
		<h4>by Eric Rouse</h4>
		<h3>Where's My Bus Database</h3>
		<p>This is the interface to the <strong>Where's my Bus database</strong>, it can be used to add and remove buses, stops, drivers, etc.</p>
		
		
		<!-- bus database view !-->
		<a name="buses"></a>
		<div><table>
			
			<tr>
				<td colspan="7"><h3>Current Bus Drivers and Positions</h3></td>
			</tr>
			<tr>
				<th>Bus Number</th>
				<th colspan="2">Driver's Name</th>
				<th>Route</th>
				<th colspan="2">Bus GPS Latitude/Longitude Position</th>
				<th>Time of Position</th>
				
			</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT b.busNo, d.fname, d.lname, p.lat, p.lng, p.tmstp, r.route
					FROM buses AS b
					INNER JOIN busanddriver AS bd ON b.busNo = bd.bus
					INNER JOIN drivers AS d ON d.dID = bd.driver
					INNER JOIN positions AS p ON b.busNo = p.busNo
					INNER JOIN routes AS r ON b.busNo = r.bus
					GROUP BY r.route"))){
				echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: " .$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->bind_result($busNumber, $fname, $lname, $lat, $lng, $time,$route)){
				echo "Bind failed: " .$stmt->errno." ".$stmt->error;
			}
			while($stmt->fetch()){
				echo "<tr>\n<td>\n".$busNumber."</td>\n<td>".$fname."</td>\n<td>".$lname."</td>\n<td>".$route."</td>\n<td>".$lat."</td>\n<td>".$lng."</td>\n<td>".$time."</td></tr>";
			}
			$stmt->close();
		?>
		</table></div>
		<p>Please note that <strong>ONLY</strong> buses with a driver and a position and a route will show up in this list. So, if the bus you are interested in isn't on the list, it might not have one of these critical attributes.</p>
		<!-- bus forms !-->
		<!-- match a bus and driver !-->
		
		<div>
			<h3>Pair a Bus With a Driver</h3>
			<form method="post" action="adddrivertobus.php"> 

				<fieldset>
					<legend>Mix and Match as Desired</legend>
					<select name="BusID" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT busNo FROM buses"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' . $id . '</option>\n';
						}
						$stmt->close();
					?>
					</select>
					<select name="DrvID" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT dID, fname, lname FROM drivers"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id, $fname, $lname)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' . $fname ." ". $lname. '</option>\n';
						}
						$stmt->close();
					?>
					</select>
				</fieldset>

				<p><input type="submit" /></p>
			</form>
		</div>
		<div>
			<h3>Pair a Bus With a Route</h3>
			<form method="post" action="addbustoroute.php"> 

				<fieldset>
					<legend>Put a bus on a route</legend>
					<select name="BusID" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT busNo FROM buses"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' . $id . '</option>\n';
						}
						$stmt->close();
					?>
					</select>
					<select name="RouteID" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT route FROM routes"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' . "Route" ." ". $id.'</option>\n';
						}
						$stmt->close();
					?>
					</select>
				</fieldset>

				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- add to form !-->
		<div>
			<h3>Add a Bus</h3>
			<form method="post" action="addbus.php"> 

				<fieldset>
					<legend>Easy Breazy add Method</legend>
					<p>Just click the submit button, it will generate a new bus as if by magic!</p>

				</fieldset>


				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- remove from form !-->
		<div>
			<h3>Remove a Bus</h3>
			<form method="post" action="rembus.php"> 

				<fieldset>
					<legend>Bus ID# (required)</legend>
					<select name="BusID" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT busNo FROM buses"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' . $id . '</option>\n';
						}
						$stmt->close();
					?>
					</select>
				</fieldset>

				<p><input type="submit" value="Remove"/></p>
			</form>
		</div>

		
		<!-- drivers database view !-->
		<a name="drivers"></a>
		<div><table>
			
			<tr>
				<td colspan="4"><h3>Current Drivers</h3></td>
			</tr>
			<tr>
				<th>ID#</th>
				<th>First Name</th>
				<th>Last Name</th>
				<th>Rating</th>
			</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT * FROM drivers"))){
				echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: " .$mysqli->connect_errno." ".$mysqli->connect_error;
			}
			if(!$stmt->bind_result($id, $fname, $lname, $rating)){
				echo "Bind failed: "  . $mysqli->connect_errno . " " . $mysqli->connect_error;
			}
			while($stmt->fetch()){
				echo "<tr>\n<td>\n".$id."</td>\n<td>".$fname."</td>\n<td>".$lname."</td>\n<td>".$rating."</td></tr>";
			}
			$stmt->close();
		?>
		</table></div>
		
		<!--drivers forms !-->
		<!-- add to form !-->
		<div>
			<h3>Add a Driver</h3>
			<form method="post" action="adddriver.php"> 

				<fieldset>
					<legend>New Driver Name (required)</legend>
					<p>First Name: <input type="text" name="FirstName" /></p>
					<p>Last Name: <input type="text" name="LastName" /></p>
				</fieldset>

				<fieldset>
					<legend>New Driver Rating (optional)</legend>
					<p>Rating (1-5): <input type="text" name="Rating" /></p>
				</fieldset>

				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- remove from form !-->
		<div>
			<h3>Remove a Driver</h3>
			<form method="post" action="remdriver.php"> 

				<fieldset>
					<legend>Driver to Remove</legend>
					<select name="DrvID" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT dID, fname, lname FROM drivers"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id, $fname, $lname)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' . $fname ." ". $lname. '</option>\n';
						}
						$stmt->close();
					?>
					</select>
				</fieldset>

				<p><input type="submit" value="Remove" /></p>
			</form>
		</div>
		
		<!-- positions database view !-->
		<a name="positions"></a>
		<div><table>
			
			<tr>
				<td colspan="6"><h3>Current Positions</h3></td>
			</tr>
			<tr>
				<th>ID#</th>
				<th>Bus #</th>
				<th>Latitude</th>
				<th>Longitude</th>
				<th>Timestamp</th>
				<th>Accuracy</th>
			</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT * FROM positions"))){
				echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: " .$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->bind_result($id, $bus, $lat, $lng, $tm, $acc)){
				echo "Bind failed: "  .$stmt->errno." ".$stmt->error;
			}
			while($stmt->fetch()){
				echo "<tr>\n<td>\n".$id."</td>\n<td>".$bus."</td>\n<td>".$lat."</td>\n<td>".$lng."</td>\n<td>".$tm."</td>\n<td>".$acc."</td></tr>";
			}
			$stmt->close();
		?>
		</table></div>
		<!--positions forms !-->
		<!-- add to form !-->
		<div>
			<h3>Post a New Bus Position</h3>
			<form method="post" action="addposition.php"> 

				<fieldset>
					 <legend>New Position (required)</legend>
					<p> Bus#:
					<select name="BusNum" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT busNo FROM buses"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' . $id . '</option>\n';
						}
						$stmt->close();
					?>
					</p>
					</select>
					<p>Latitude: <input type="text" name="Lat" /></p>
					<p>Longitude: <input type="text" name="Lng" /></p>
				</fieldset>
				

				<fieldset>
					<legend>Position Accuracy (optional)</legend>
					<p>Accuracy (1-10): <input type="text" name="Acc" /></p>
				</fieldset>

				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- remove from form !-->
		<div>
			<h3>Remove a Position</h3>
			<form method="post" action="remposition.php"> 

				<fieldset>
					<legend>Position to Remove</legend>
					<select name="PosID" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT pID, lat, lng FROM positions"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id, $lat, $lng)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' ."Pos#: ". $id . " @ position: ". $lat .", ".$lng. '</option>\n';
						}
						$stmt->close();
					?>
					</select>
				</fieldset>

				<p><input type="submit" value="Remove" /></p>
			</form>
		</div>
		
		<!-- stops database view !-->
		<a name="stops"></a>
		<div><table>
			
			<tr>
				<td colspan="3"><h3>Current Stops</h3></td>
			</tr>
			<tr>
				<th>Stop Name</th>
				<th>Latitude</th>
				<th>Longitude</th>
			</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT name, lat, lng FROM stops"))){
				echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: " .$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->bind_result($name, $lat, $lng)){
				echo "Bind failed: " .$stmt->errno." ".$stmt->error;
			}
			while($stmt->fetch()){
				echo "<tr>\n<td>\n".$name."</td>\n<td>".$lat."</td>\n<td>".$lng."</td></tr>";
			}
			$stmt->close();
		?>
		</table></div>

		<!--stops forms !-->
		<!-- add to form !-->
		<div>
			<h3>Add a Stop</h3>
			<form method="post" action="addstop.php"> 

				<fieldset>
					<legend>New Stop Name Position (required)</legend>
					<p>Name: <input type="text" name="StopName" /></p>
					<p>Latitude: <input type="text" name="Lat" /></p>
					<p>Longitude: <input type="text" name="Lng" /></p>
				</fieldset>

				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- remove from form !-->
		<div>
			<h3>Remove a Stop</h3>
			<form method="post" action="remstop.php"> 

				<fieldset>
					<legend>Stop to Remove</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT sID, name FROM stops"))){
							echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
						}

						if(!$stmt->execute()){
							echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
						}
						if(!$stmt->bind_result($id, $stop)){
							echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
						}
						while($stmt->fetch()){
						 echo '<option value=" '. $id . ' "> ' . $stop . '</option>\n';
						}
						$stmt->close();
					?>
					</select>
				</fieldset>

				<p><input type="submit" value="Remove" /></p>
			</form>
		</div>
		<div>
			<h1><a href = "routes.php">--> Edit Routes</a></h1>
		</div>
	</div>
	</body>
</html>
