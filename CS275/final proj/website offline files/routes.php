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
		<title>Routes</title>
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
		<h1>CS275 Final Project - Routes</h1>
		<h4>by Eric Rouse</h4>
		<h3>Routes are collections of stops</h3>
		<p>There are four routes, stops can be added to them or removed. Order matters.</p>
		
		<!-- database view !-->
		<!-- Route #1 !-->
		<a name="Route1"></a>
		<div><table>
			
			<tr>
				<td colspan="1"><h3>Route 1 Stops</h3></td>
			</tr>
			<tr>
				<th>Stop Name</th>
			</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT stops.name FROM route1 INNER JOIN stops ON sID = stop"))){
				echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: " .$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->bind_result($name)){
				echo "Bind failed: " .$stmt->errno." ".$stmt->error;
			}
			while($stmt->fetch()){
				echo "<tr>\n<td>\n".$name."</td>\n</tr>";
			}
			$stmt->close();
		?>
		</table></div>
		
		<!-- Route #2 !-->
		<a name="Route2"></a>
		<div><table>
			
			<tr>
				<td colspan="1"><h3>Route 2 Stops</h3></td>
			</tr>
			<tr>
				<th>Stop Name</th>
			</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT stops.name FROM route2 INNER JOIN stops ON sID = stop"))){
				echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: " .$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->bind_result($name)){
				echo "Bind failed: " .$stmt->errno." ".$stmt->error;
			}
			while($stmt->fetch()){
				echo "<tr>\n<td>\n".$name."</td>\n</tr>";
			}
			$stmt->close();
		?>
		</table></div>
		<!-- Route #3 !-->
		<a name="Route3"></a>
		<div><table>
			
			<tr>
				<td colspan="1"><h3>Route 3 Stops</h3></td>
			</tr>
			<tr>
				<th>Stop Name</th>
			</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT stops.name FROM route3 INNER JOIN stops ON sID = stop"))){
				echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: " .$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->bind_result($name)){
				echo "Bind failed: " .$stmt->errno." ".$stmt->error;
			}
			while($stmt->fetch()){
				echo "<tr>\n<td>\n".$name."</td>\n</tr>";
			}
			$stmt->close();
		?>
		</table></div>
		<!-- Route #4 !-->
		<a name="Route4"></a>
		<div><table>
			
			<tr>
				<td colspan="1"><h3>Route 4 Stops</h3></td>
			</tr>
			<tr>
				<th>Stop Name</th>
			</tr>
		<?php
			if(!($stmt = $mysqli->prepare("SELECT stops.name FROM route4 INNER JOIN stops ON sID = stop"))){
				echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->execute()){
				echo "Execute failed: " .$stmt->errno." ".$stmt->error;
			}
			if(!$stmt->bind_result($name)){
				echo "Bind failed: " .$stmt->errno." ".$stmt->error;
			}
			while($stmt->fetch()){
				echo "<tr>\n<td>\n".$name."</td>\n</tr>";
			}
			$stmt->close();
		?>
		</table></div>
		<!-- forms !-->
		<!-- Route 1 add !-->
		<div>
			<h3>Add a Stop to Route 1</h3>
			<form method="post" action="addstopr1.php"> 

				<fieldset>
					<legend>Stop to Add</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT stops.sID, stops.name FROM stops"))){
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

				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- Route 1 remove !-->
		<div>
			<h3>Remove a Stop from Route 1</h3>
			<form method="post" action="remstopr1.php"> 

				<fieldset>
					<legend>Stop to Remove</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT stops.sID, stops.name FROM route1 INNER JOIN stops ON sID = stop"))){
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
		<!-- Route 2 add !-->
		<div>
			<h3>Add a Stop to Route 2</h3>
			<form method="post" action="addstopr2.php"> 

				<fieldset>
					<legend>Stop to Add</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT stops.sID, stops.name FROM stops"))){
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

				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- Route 2 remove !-->
		<div>
			<h3>Remove a Stop from Route 2</h3>
			<form method="post" action="remstopr2.php"> 

				<fieldset>
					<legend>Stop to Remove</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT stops.sID, stops.name FROM route2 INNER JOIN stops ON sID = stop"))){
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
		<!-- Route 3 add !-->
		<div>
			<h3>Add a Stop to Route 3</h3>
			<form method="post" action="addstopr3.php"> 

				<fieldset>
					<legend>Stop to Add</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT stops.sID, stops.name FROM stops"))){
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

				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- Route 3 remove !-->
		<div>
			<h3>Remove a Stop from Route 3</h3>
			<form method="post" action="remstopr3.php"> 

				<fieldset>
					<legend>Stop to Remove</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT stops.sID, stops.name FROM route3 INNER JOIN stops ON sID = stop"))){
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
		<!-- Route 4 add !-->
		<div>
			<h3>Add a Stop to Route 4</h3>
			<form method="post" action="addstopr4.php"> 

				<fieldset>
					<legend>Stop to Add</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT stops.sID, stops.name FROM stops"))){
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

				<p><input type="submit" /></p>
			</form>
		</div>
		<!-- Route 4 remove !-->
		<div>
			<h3>Remove a Stop from Route 4</h3>
			<form method="post" action="remstopr4.php"> 

				<fieldset>
					<legend>Stop to Remove</legend>
					<select name="StopName" >
					<?php
						if(!($stmt = $mysqli->prepare("SELECT stops.sID, stops.name FROM route4 INNER JOIN stops ON sID = stop"))){
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
			<h1><a href = "index.php">--> Back to Main</a></h1>
		</div>
	</div>
	</body>
</html>
