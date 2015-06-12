<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');
//declares some useful vars
$hdr = '<!DOCTYPE html>
<html lang = "en">
  <head>
    <meta charset="UTF-8">
    <title>Business Directory Editor</title>
    <link rel="stylesheet" href="./style.css" type="text/css" media="all" />
  </head>
  <body>
  <div id="content">';
$ftr = '  </div>
  </body>
</html>';

include '../pass.php';
$mysqli = new mysqli("mysql.eecs.oregonstate.edu", "cs419-g6", $db_pass, "cs419-g6");
if ($mysqli->connect_errno){
    echo "Database connection failed: (" . $mysqli->connect_errno . ")" . $mysqli->connect_error;
}




//check request method
if ($_SERVER['REQUEST_METHOD'] === 'POST'){
    //show a businesses by ID
    if (isset($_POST['BusinessByID'])){
        if(!($stmt = $mysqli->prepare("SELECT name, address, phone, url, accepts FROM businesses
            WHERE id = ?"))){
            echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->bind_param("i", $_POST['BusinessByID'])){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->bind_result($name, $address, $phone, $url, $accepts)){
            echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
        }
        while($stmt->fetch()){
         if($name != ""){echo '<option value="'. $name .'"> ' . $name . '</option>\n';}
        }
        $stmt->close();
        echo "
        <form action=\"./admin.php\"
            method = \"post\">
            <fieldset>
                <legend>Edit a Business</legend>
                <table>
                    <tr><td>Name:<td><input type=\"text\" name=\"name\" value =\"$name\">
                    <tr><td>Address:<td><input type=\"text\" name=\"address\" value =\"$address\">
                    <tr><td>Phone:<td><input type=\"text\" name=\"phone\" value =\"$phone\">
                    <tr><td>Website:<td><input type=\"text\" name=\"url\" value =\"$url\">
                    <tr><td>Accepts:<td><input type=\"text\" name=\"accepts\" value =\"$accepts\">
                </table>
                <p><input type=\"submit\" name=\"Edit\" value=\"update\" class=\"grnbtn\">
                   <input type=\"hidden\" name=\"EditID\" value=\"$_POST[EditID]\"></p>
            </fieldset>
            
        </form>
        ";
    }
    //add business section
    if (!empty($_POST['AddBusiness']) && $_POST['AddBusiness'] == 'add business'){
        checkadd($mysqli);
        if(!($stmt = $mysqli->prepare("INSERT INTO businesses(name, address, phone, url, accepts)
                VALUES (?, ?, ?, ?, ?)
                "))) {
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }

        if(!$stmt->bind_param("sssss", $_POST['name'], $_POST['address'], $_POST['phone'], $_POST['url'], createaccept($_POST['cat']))){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: " .$stmt->errno." ".$stmt->error;
        }

        $stmt->close();
    }
    //delete a business
    if (!empty($_POST['DeleteRow']) && $_POST['DeleteRow'] == 'delete'){


        if(!($stmt = $mysqli->prepare("DELETE FROM businesses WHERE id=?
                "))) {
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->bind_param("i", $_POST['DeleteRowID'])){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: " .$stmt->errno." ".$stmt->error;
        }

        $stmt->close();
    }
    //update a business
    if (!empty($_POST['Edit']) && $_POST['Edit'] == 'update'){


        if(!($stmt = $mysqli->prepare("UPDATE businesses
                SET name = ?, address = ?, phone = ?, url = ?, accepts = ?
                WHERE id = ?
                "))) {
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->bind_param("sssssi", $_POST['name'], $_POST['address'], $_POST['phone'], $_POST['url'], $_POST['accepts'], $_POST['EditID'])){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: " .$stmt->errno." ".$stmt->error;
        }

        $stmt->close();
    }

    //filter the business section
    if (!empty($_POST['filter'])){

        if ($_POST['filter'] === '_allbusiness_') {
            $filter_val = 0;
        }
        else {
            $filter_val = $_POST['filter'];
        }
    }
}
    echo $ftr;
?>
