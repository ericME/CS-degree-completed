<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');

session_start();
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
$id = -1;
$name = "";
$address = "";
$phone ="";
$url = "";
$zip = "";
$hours = "";
$accepts = "";
$filter_val = 0;

// turn on error reporting
ini_set("display_errors", "On");

include 'pass.php';
$mysqli = new mysqli("mysql.eecs.oregonstate.edu", "cs419-g6", $db_pass, "cs419-g6");
if ($mysqli->connect_errno){
    echo "Database connection failed: (" . $mysqli->connect_errno . ")" . $mysqli->connect_error;
}

$categories = parsecategories($mysqli);

echo $hdr;
if (!isset($_SESSION['active']) || $_SESSION['active'] != true){
    echo '<h1>You must first <a href="./">log in</a> to view this page.</h1>';
    echo $ftr;
    exit();
}

//build the add and edit businesses form
echo "<form action=\"./logout.php\"
        method = \"post\">"; 
echo "<h1>Welcome, ".$_SESSION['username'];
echo "        <input type=\"submit\" value=\"Logout\" name=\"logout\" class=\"redbtn\">
    </form>";
echo "</h1>";

echo "<div id=\"leftcolumn\">";
echo "<form action=\"./categories.php\" 
        method = \"post\">
        <p><input type=\"submit\" value=\"Edit Categories\" class=\"blubtn\"></p>
    </form></div>";
echo "<div id=inner>";

if (isset($_POST['Edit']) && $_POST['Edit'] == 'edit'){
    if(!($stmt = $mysqli->prepare("SELECT name, address, phone, url, accepts, zip, hours FROM businesses
        WHERE id = ?"))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!$stmt->bind_param("s", $_POST['EditID'])){
        echo "Bind failed: " .$stmt->errno." ".$stmt->error;
    }
    if(!$stmt->execute()){
        echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!$stmt->bind_result($name, $address, $phone, $url, $accepts, $zip, $hours)){
        echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
    }
    while($stmt->fetch()){
     if($name != ""){echo '<option value="'. $name .'"> ' . $name . '</option>';}
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
                <tr><td>ZIP Code:<td><input type=\"text\" name=\"zip\" value =\"$zip\">
                <tr><td>Phone:<td><input type=\"text\" name=\"phone\" value =\"$phone\">
                <tr><td>Website:<td><input type=\"text\" name=\"url\" value =\"$url\">
                <tr><td>Hours:<td><input type=\"text\" name=\"hours\" value =\"$hours\">
                <tr><td colspan = 4>Accepts:";
                $items = explode("]],[[", $accepts);
                $acc_array = array();
                foreach($items as $item){
                    $item = explode("],[", $item);
                    if (!isset($item[1])){
                        return null;
                    }
                    $item[0] = str_replace("[", "", $item[0]);
                    if (isset($categories[$item[0]])){
                        $item[0] = $categories[$item[0]][0][0];
                        $item[1] = str_replace("]", "", $item[1]);
                        $item[1] = explode(",", $item[1]);
                        $acc_array[$item[0]] = $item[1];
                    }
                }

                //var_dump($acc_array);
                foreach ($categories as $cat){
                    $i = 0;
                    echo "<tr>\n<td>\n<strong>".$cat[0][0].":</strong>";
                    echo "<td>";
                    $temp = array();
                    $sub_arr = 0;
                    $sub_cat = 1;
                    foreach ($cat[1] as $c) {
                        $checked = "";
                        if ($c != null && $c != ""){
                            if (!empty($acc_array[$cat[0][0]][$sub_arr]) && ($acc_array[$cat[0][0]][$sub_arr] === (string)$sub_cat)){
                                $checked = "checked";
                                $sub_arr += 1;
                            }
                            $temp[$i] = "<input type=\"checkbox\" name=\"cat[]\" value=\"".$cat[0][1]."||".($i+1)."\" $checked > $c <br>";
                            $i = $i + 1;
                        }
                        $sub_cat += 1;
                    }

                    $k = ceil($i/3);
                    for ($j=0;$j<$i;$j++) {
                        if ($j % $k == 0 && $j!=0){
                            echo "<td>";
                        }
                        echo $temp[$j];
                    }
                }
            echo"
            </table>
            <p><input type=\"submit\" name=\"Edit\" value=\"update\" class=\"grnbtn\">
               <input type=\"hidden\" name=\"EditID\" value=\"$_POST[EditID]\"></p>
        </fieldset>
        
    </form>
    ";
} else {
    
    echo "
    <form action=\"./admin.php\"
        method = \"post\">
        
        <fieldset>
            <legend>Add a Business</legend>
            <table>
                <tr><td>Name:<td colspan = 3><input type=\"text\" name=\"name\"> <em>REQUIRED</em>
                <tr><td>Address:<td colspan = 3><input type=\"text\" name=\"address\">
                <tr><td>ZIP Code:<td colspan = 3><input type=\"text\" name=\"zip\" value =\"$zip\"> <em>REQUIRED</em>
                <tr><td>Phone:<td colspan = 3><input type=\"text\" name=\"phone\">
                <tr><td>Website:<td colspan = 3><input type=\"text\" name=\"url\">
                <tr><td>Hours:<td><input type=\"text\" name=\"hours\" value =\"$hours\">
                <tr><td colspan = 4>Accepts:";
                foreach ($categories as $cat){
                    $i = 0;
                    echo "<tr>\n<td>\n<strong>".$cat[0][0].":</strong>";
                    echo "<td>";
                    $temp = array();
                    foreach ($cat[1] as $c) {
                        if ($c != null && $c != ""){
                            $temp[$i] = "<input type=\"checkbox\" name=\"cat[]\" value=\"".$cat[0][1]."||".($i+1)."\"> $c <br>";
                            $i = $i + 1;
                        }
                    }
                    $k = ceil($i/3);
                    for ($j=0;$j<$i;$j++) {
                        if ($j % $k == 0 && $j!=0){
                            echo "<td>";
                        }
                        echo $temp[$j];
                    }
                }
    echo "
            </table>
            <p><input type=\"submit\" name=\"AddBusiness\" value=\"add business\" class=\"grnbtn\"></p>
        </fieldset>
        
    </form>
    ";
}

//a function to verify properties for adding a business
function checkadd($mysqli){
    $name = $_POST['name'];
    $address = $_POST['address'];
    $phone = $_POST['phone'];
    $url = $_POST['url'];
    $user = $_SESSION['username'];
    $zip = $_POST['zip'];
    $errorIn_parms = False;

    if(empty($name)) {
        echo '<div id="error_message">Name of Business is required.<br></div>';
        $errorIn_parms = True;
    } elseif(empty($zip)) {
        echo '<div id="error_message">ZIP code is required.<br></div>';
        $errorIn_parms = True;
    } else {
        if(!($stmt = $mysqli->prepare("SELECT name FROM businesses WHERE name = ? ORDER BY name
                "))){
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->bind_param("s", $name)){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: " .$stmt->errno." ".$stmt->error;
        }
        $stmt->store_result();
        if($stmt->num_rows != 0){
            echo '<div id="error_message">Name of Business must be unique.<br></div>';
            $errorIn_parms = True;
        }
        $stmt->close();
    }

    if($errorIn_parms){
        exit(0);
    }

}

//a function to take the accept data and correlate it to real named categories
function parseaccept($accepts, $categories, $name){
    $items = explode("]],[[", $accepts);
    $iter = 0;
    $seperator = "";
    $output = "";
    foreach($items as $item){
        $item = explode("],[", $item);
        if (!isset($item[1])){
            return null;
        }
        $item[0] = str_replace("[", "", $item[0]);
        $item[1] = str_replace("]", "", $item[1]);
        $item[1] = explode(",", $item[1]);
        $q = 0;
        if (isset($categories[$item[0]])) {
            foreach ($categories[$item[0]] as $c) {
                if ($q === 1 && $c != null && $c != ""){
                    foreach ($item[1] as $i) {
                        if ($c[$i] != null && $c[$i] != ""){
                            $output = $output.$seperator.$c[$i];
                            $seperator = ", ";
                        }
                    }
                } else if ($q === 0){
                    $seperator = "<br>";
                    $output = $output.$seperator."<strong>".$c[0].":</strong>".$seperator;
                    $seperator = "";
                }
                $q = 1;
            }
        }
    }

    return $output;
}

//a function to clone a list
function myclone($item){
    return $item;
}

//a function to parse the category items and fill a data structure with proper names
function parsecategories($mysqli){
    $output = array();
    $clone = array();
    $seperator = "";
    if(!($stmt = $mysqli->prepare("SELECT name, id,
        item_1, item_2, item_3, item_4, item_5,
        item_6, item_7, item_8, item_9, item_10, 
        item_11, item_12, item_13, item_14, item_15,
        item_16, item_17, item_18, item_19, item_20, 
        item_21, item_22, item_23, item_24, item_25
        FROM categories
        "))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!$stmt->execute()){
        echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!$stmt->bind_result($name, $id,
        $item[1], $item[2], $item[3], $item[4], $item[5],
        $item[6], $item[7], $item[8], $item[9], $item[10],
        $item[11], $item[12], $item[13], $item[14], $item[15],
        $item[16], $item[17], $item[18], $item[19], $item[20],
        $item[21], $item[22], $item[23], $item[24], $item[25]
        )){
        echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
    }
    while($stmt->fetch()){
        $clone = array_map('myclone', $item);
        $output[$id] = [[$name,$id], $clone];
    }


    $stmt->close();
    return $output;
}

//a function to create a proper accepts array from selected items
function createaccept($cat){
    $seperator = "";
    $terminator = "";
    $out_arr = array();
    $current = 0;
    $temp = array();
    $output = "[";
    foreach ($cat as $c) {
        $out_arr = explode("||",$c);
        if ($current != $out_arr[0]){
            $current = $out_arr[0];
            $output = $output.$terminator."[[".$current."],[";
            $terminator = "]],";
            $seperator = "";
        }
        $output = $output.$seperator.$out_arr[1];
        $seperator = ",";
    }
    $output = $output."]]]";
    return $output;
}

//check request method
if ($_SERVER['REQUEST_METHOD'] === 'POST'){
    //delete all businesses button
    if (!empty($_POST['Delete']) && $_POST['Delete'] == 'delete all businesses'){
        if(!($stmt = $mysqli->prepare("DELETE
                FROM businesses
                "))) {
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: " .$stmt->errno." ".$stmt->error;
        }

        $stmt->close();
    }
    //add business section
    if (!empty($_POST['AddBusiness']) && $_POST['AddBusiness'] == 'add business'){
        checkadd($mysqli);
        if(!($stmt = $mysqli->prepare("INSERT INTO businesses(name, address, phone, url, accepts, hours, zip)
                VALUES (?, ?, ?, ?, ?, ?, ?)
                "))) {
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }
        $local_accept = createaccept($_POST['cat']);
        if(!$stmt->bind_param("sssssss", $_POST['name'], $_POST['address'], $_POST['phone'], $_POST['url'], $local_accept, $_POST['hours'], $_POST['zip'])){
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
                SET name = ?, address = ?, phone = ?, url = ?, accepts = ?, hours = ?, zip = ?
                WHERE id = ?
                "))) {
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }
        $local_accept = createaccept($_POST['cat']);
        if(!$stmt->bind_param("sssssssi", $_POST['name'], $_POST['address'], $_POST['phone'], $_POST['url'], $local_accept, $_POST['hours'], $_POST['zip'], $_POST['EditID'])){
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
//build the filter form
echo '<form action="./admin.php"
        method = "post">
        <fieldset>
        <legend>Show</legend>
        <select name="filter">
            <option value="_allbusiness_">All Businesses</option>';
            if(!($stmt = $mysqli->prepare("SELECT name FROM businesses ORDER BY name"))){
                echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
            }
            if(!$stmt->execute()){
                echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
            }
            if(!$stmt->bind_result($name)){
                echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
            }
            while($stmt->fetch()){
             if($name != ""){echo '<option value="'. $name .'"> ' . $name . '</option>\n';}
            }
            $stmt->close();
//build the actual data table
echo '</select>
        <input type="submit" name="FilterBusiness" value="apply" class="blubtn">
    </fieldset>
    </form>';

    echo "<fieldset>
        <legend>Business List</legend>
        <table class = special_table>
            
            <tr>
                <th style=\"width:5%\">id#
                <th style=\"width:30%\">Name
                <th style=\"width:45%\">Details
                <th style=\"width:10%\">Delete
                <th style=\"width:10%\">Edit
            </tr>";
            
            if ($filter_val === 0){
                echo "showing all business";
                if(!($stmt = $mysqli->prepare("SELECT b.id, b.name, b.address, b.phone, b.url, b.accepts, b.hours, b.zip
                        FROM businesses AS b ORDER BY b.name
                        "))){
                    echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
                }
            } else {
                echo "showing only $filter_val";
                if(!($stmt = $mysqli->prepare("SELECT b.id, b.name, b.address, b.phone, b.url, b.accepts, b.hours, b.zip
                        FROM businesses AS b
                        WHERE name = ?
                        "))){
                    echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
                }
                if(!$stmt->bind_param("s", $filter_val)){
                    echo "Bind failed: " .$stmt->errno." ".$stmt->error;
                }
            }
           
            if(!$stmt->execute()){
                echo "Execute failed: " .$stmt->errno." ".$stmt->error;
            }
            if(!$stmt->bind_result($id, $name, $address, $phone, $url, $accepts, $hours, $zip)){
                echo "Bind failed: " .$stmt->errno." ".$stmt->error;
            }

            while($stmt->fetch()){
                echo "<tr>\n<td rowspan = 2>\n".$id."\n<td><strong>".$name."\n</strong><td>
                <img src=\"./address.png\" width=\"12.5\" height=\"12.5\" >  ".$address.
                "\n<br><img src=\"./zip.png\" width=\"12.5\" height=\"12.5\" >  ".$zip.
                "\n<br><img src=\"./phone.png\" width=\"12.5\" height=\"12.5\">  ".$phone.
                "\n<br><img src=\"./hours.png\" width=\"12.5\" height=\"12.5\" >  ".$hours.
                "\n<br><img src=\"./web.png\" width=\"12.5\" height=\"12.5\">  <a href=\"http://$url\">".$url."</a>\n";
                echo '<td rowspan = 2><form action="./admin.php"
                          method = "post">
                          <input type="submit" name="DeleteRow" value="delete" class="redbtn">
                          <input type="hidden" name="DeleteRowID" value="'.$id.'">
                        </form>';
                echo '<td rowspan = 2><form action="./admin.php"
                          method = "post">
                          <input type="submit" name="Edit" value="edit" class="blubtn">
                          <input type="hidden" name="EditID" value="'.$id.'">
                        </form>';
                echo "</tr>";
                echo "<tr>\n<td colspan = 2>\n<em><strong>Accepts:</em></strong> ".parseaccept($accepts, $categories, $name)."\n";
                echo "</tr>";
            }
            $stmt->close();
    echo "</table>
    </fieldset>";
    echo "</div>";
    echo $ftr;
?>
