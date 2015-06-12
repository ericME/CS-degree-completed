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
$filter_val = 0;
$max_items = 26;
$item_1  = "";
$item_2  = "";
$item_3  = "";
$item_4  = "";
$item_5  = "";
$item_6  = "";
$item_7  = "";
$item_8  = "";
$item_9  = "";
$item_10 = "";
$item_11 = "";
$item_12 = "";
$item_13 = "";
$item_14 = "";
$item_15 = "";
$item_16 = "";
$item_17 = "";
$item_18 = "";
$item_19 = "";
$item_20 = "";
$item_21 = "";
$item_22 = "";
$item_23 = "";
$item_24 = "";
$item_25 = "";

// turn on error reporting
ini_set("display_errors", "On");

//include necessary files
include 'pass.php';
$mysqli = new mysqli("mysql.eecs.oregonstate.edu", "cs419-g6", $db_pass, "cs419-g6");
if ($mysqli->connect_errno){
    echo "Database connection failed: (" . $mysqli->connect_errno . ")" . $mysqli->connect_error;
}

echo $hdr;
if (!isset($_SESSION['active']) || $_SESSION['active'] != true){
    echo '<h1>You must first <a href="./">log in</a> to view this page.</h1>';
    echo $ftr;
    exit();
}

echo "<form action=\"./logout.php\"
        method = \"post\">"; 
echo "<h1>Welcome, ".$_SESSION['username'];
echo "        <input type=\"submit\" value=\"Logout\" name=\"logout\" class=\"redbtn\">
    </form>";
echo "</h1>";

echo "<div id=\"leftcolumn\">";
echo "<form action=\"./admin.php\" 
        method = \"post\">
        <p><input type=\"submit\" value=\"Edit Businesses\" class=\"blubtn\"></p>
    </form></div>";
echo "<div id=inner>";

if (isset($_POST['Edit']) && $_POST['Edit'] == 'edit'){
    if(!($stmt = $mysqli->prepare("SELECT name,
        item_1, item_2, item_3, item_4, item_5,
        item_6, item_7, item_8, item_9, item_10,
        item_11, item_12, item_13, item_14, item_15,
        item_16, item_17, item_18, item_19, item_20,
        item_21, item_22, item_23, item_24, item_25
        FROM categories WHERE id = ?"))){
        echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!$stmt->bind_param("s", $_POST['EditID'])){
        echo "Bind failed: " .$stmt->errno." ".$stmt->error;
    }
    if(!$stmt->execute()){
        echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
    }
    if(!$stmt->bind_result($name,
        $item_1, $item_2, $item_3, $item_4, $item_5,
        $item_6, $item_7, $item_8, $item_9, $item_10,
        $item_11, $item_12, $item_13, $item_14, $item_15,
        $item_16, $item_17, $item_18, $item_19, $item_20,
        $item_21, $item_22, $item_23, $item_24, $item_25
        )){
        echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
    }
    while($stmt->fetch()){
     if($name != ""){echo '<option value="'. $name .'"> ' . $name . '</option>';}
    }
    $stmt->close();
    $item_array = array($max_items,
        $item_1, $item_2, $item_3, $item_4, $item_5,
        $item_6, $item_7, $item_8, $item_9, $item_10,
        $item_11, $item_12, $item_13, $item_14, $item_15,
        $item_16, $item_17, $item_18, $item_19, $item_20,
        $item_21, $item_22, $item_23, $item_24, $item_25
        );
    echo "
    <form action=\"./categories.php\"
        method = \"post\">
        
        <fieldset>
            <legend>Edit a Category</legend>
            <table>
                <tr><td>Name:<td colspan = 3><input type=\"text\" name=\"name\" value =\"$name\">
                <tr><td>Sub-Categories:<td>";
                for ($i=1; $i<$max_items; $i++) {
                    echo "\n<strong>Item ".$i.":</strong><br>";
                    echo "\n<input type=\"text\" name=\"item[]\" value=\"".$item_array[$i]."\"><br>";
                    if ($i % 10 == 0){
                        echo "<td>";
                    }
                    
                }
    echo "
            </table>
            <p><input type=\"submit\" name=\"Edit\" value=\"update\" class=\"grnbtn\">
               <input type=\"hidden\" name=\"EditID\" value=\"$_POST[EditID]\"></p>
        </fieldset>
        
    </form>
    ";
} else {
    
    echo "
    <form action=\"./categories.php\"
        method = \"post\">
        
        <fieldset>
            <legend>Add a Category</legend>
            <table>
                <tr><td>Name:<td colspan = 3><input type=\"text\" name=\"name\">  <em>REQUIRED</em>
                <tr><td>Sub-Categories:<td>";
                for ($i=1; $i<$max_items; $i++) {
                    echo "\n<strong>Item ".$i.":</strong><br>";
                    echo "\n<input type=\"text\" name=\"item[]\"><br>";
                    if ($i % 10 == 0){
                        echo "<td>";
                    }
                    
                }
    echo "
            </table>
            <p><input type=\"submit\" name=\"AddCategory\" value=\"add category\" class=\"grnbtn\"></p>
        </fieldset>
        
    </form>
    ";
}


function checkadd($mysqli){
    $name = $_POST['name'];
    $errorIn_parms = False;

    if(empty($name)){
        echo '<div id="error_message">Name of Category is required.<br></div>';
        $errorIn_parms = True;
    } else {
        if(!($stmt = $mysqli->prepare("SELECT name FROM categories WHERE name = ? ORDER BY name
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
            echo '<div id="error_message">Name of Category must be unique.<br></div>';
            $errorIn_parms = True;
        }
        $stmt->close();
    }

    if($errorIn_parms){
        exit(0);
    }

}

//check request method
if ($_SERVER['REQUEST_METHOD'] === 'POST'){
    //add category section
    if (!empty($_POST['AddCategory']) && $_POST['AddCategory'] == 'add category'){
        checkadd($mysqli);
        //remove spaces
        $j = 0;
        for ($i = 0; $i < 25; $i++){
            if(isset($_POST['item'][$i]) && $_POST['item'][$i] !== ""){
                $_POST['item'][$j] = $_POST['item'][$i];
                if ($i !== $j) {
                    $_POST['item'][$i] = "";
                }
                $j += 1;
            }
        }
        if(!($stmt = $mysqli->prepare("INSERT INTO categories(name, 
            item_1, item_2, item_3, item_4, item_5,
            item_6, item_7, item_8, item_9, item_10,
            item_11, item_12, item_13, item_14, item_15,
            item_16, item_17, item_18, item_19, item_20,
            item_21, item_22, item_23, item_24, item_25
            )
                VALUES (?,
                    ?, ?, ?, ?, ?,
                    ?, ?, ?, ?, ?,
                    ?, ?, ?, ?, ?,
                    ?, ?, ?, ?, ?,
                    ?, ?, ?, ?, ?)
                "))) {
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->bind_param("ssssssssssssssssssssssssss", $_POST['name'],
            $_POST['item'][0], $_POST['item'][1], $_POST['item'][2], $_POST['item'][3], $_POST['item'][4],
            $_POST['item'][5], $_POST['item'][6], $_POST['item'][7], $_POST['item'][8], $_POST['item'][9],
            $_POST['item'][10], $_POST['item'][11], $_POST['item'][12], $_POST['item'][13], $_POST['item'][14],
            $_POST['item'][15], $_POST['item'][16], $_POST['item'][17], $_POST['item'][18], $_POST['item'][19],
            $_POST['item'][20], $_POST['item'][21], $_POST['item'][22], $_POST['item'][23], $_POST['item'][24]
            )){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: " .$stmt->errno." ".$stmt->error;
        }

        $stmt->close();
    }
    //delete a category
    if (!empty($_POST['DeleteRow']) && $_POST['DeleteRow'] == 'delete'){


        if(!($stmt = $mysqli->prepare("DELETE FROM categories WHERE id=?
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
    //update a category
    if (!empty($_POST['Edit']) && $_POST['Edit'] == 'update'){

        $j = 0;
        for ($i = 0; $i < 25; $i++){
            if(isset($_POST['item'][$i]) && $_POST['item'][$i] !== ""){
                $_POST['item'][$j] = $_POST['item'][$i];
                if ($i !== $j) {
                    $_POST['item'][$i] = "";
                }
                $j += 1;
            }
        }
        if(!($stmt = $mysqli->prepare("UPDATE categories
                SET name = ?,
                item_1 = ?, item_2 = ?, item_3 = ?, item_4 = ?, item_5 = ?,
                item_6 = ?, item_7 = ?, item_8 = ?, item_9 = ?, item_10 = ?,
                item_11 = ?, item_12 = ?, item_13 = ?, item_14 = ?, item_15 = ?,
                item_16 = ?, item_17 = ?, item_18 = ?, item_19 = ?, item_20 = ?,
                item_21 = ?, item_22 = ?, item_23 = ?, item_24 = ?, item_25 = ?
                WHERE id = ?
                "))) {
            echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->bind_param("ssssssssssssssssssssssssssi", $_POST['name'],
            $_POST['item'][0], $_POST['item'][1], $_POST['item'][2], $_POST['item'][3], $_POST['item'][4],
            $_POST['item'][5], $_POST['item'][6], $_POST['item'][7], $_POST['item'][8], $_POST['item'][9],
            $_POST['item'][10], $_POST['item'][11], $_POST['item'][12], $_POST['item'][13], $_POST['item'][14],
            $_POST['item'][15], $_POST['item'][16], $_POST['item'][17], $_POST['item'][18], $_POST['item'][19],
            $_POST['item'][20], $_POST['item'][21], $_POST['item'][22], $_POST['item'][23], $_POST['item'][24],
            $_POST['EditID']
            )){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: " .$stmt->errno." ".$stmt->error;
        }

        $stmt->close();
    }

    //filter the category section
    if (!empty($_POST['filter'])){

        if ($_POST['filter'] === '_allcategory_') {
            $filter_val = 0;
        }
        else {
            $filter_val = $_POST['filter'];
        }
    }
}
//build the filter form
echo '<form action="./categories.php"
        method = "post">
        <fieldset>
        <legend>Show</legend>
        <select name="filter">
            <option value="_allcategory_">All Categories</option>';
            if(!($stmt = $mysqli->prepare("SELECT name FROM categories ORDER BY name"))){
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
//build the list
echo '</select>
        <input type="submit" name="FilterCategory" value="apply" class="blubtn">
    </fieldset>
    </form>';

    echo "<fieldset>
        <legend>Category List</legend>
        <table class = special_table>
            
            <tr>
                <th style=\"width:5%\">id#
                <th style=\"width:65%\">Name
                <th style=\"width:15%\">Delete
                <th style=\"width:15%\">Edit
            </tr>";
            
            if ($filter_val === 0){
                echo "showing all categories";
                if(!($stmt = $mysqli->prepare("SELECT c.id, c.name,
                        c.item_1, c.item_2, c.item_3, c.item_4, c.item_5,
                        c.item_6, c.item_7, c.item_8, c.item_9, c.item_10,
                        c.item_11, c.item_12, c.item_13, c.item_14, c.item_15,
                        c.item_16, c.item_17, c.item_18, c.item_19, c.item_20,
                        c.item_21, c.item_22, c.item_23, c.item_24, c.item_25
                        FROM categories AS c
                        ORDER BY c.name
                        "))){
                    echo "Prepare failed: :".$stmt->errno." ".$stmt->error;
                }
            } else {
                echo "showing only $filter_val";
                if(!($stmt = $mysqli->prepare("SELECT c.id, c.name,
                        c.item_1, c.item_2, c.item_3, c.item_4, c.item_5,
                        c.item_6, c.item_7, c.item_8, c.item_9, c.item_10,
                        c.item_11, c.item_12, c.item_13, c.item_14, c.item_15,
                        c.item_16, c.item_17, c.item_18, c.item_19, c.item_20,
                        c.item_21, c.item_22, c.item_23, c.item_24, c.item_25                    
                        FROM categories AS c
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
            if(!$stmt->bind_result($id, $name,
                    $item_1, $item_2, $item_3, $item_4, $item_5,
                    $item_6, $item_7, $item_8, $item_9, $item_10,
                    $item_11, $item_12, $item_13, $item_14, $item_15,
                    $item_16, $item_17, $item_18, $item_19, $item_20,
                    $item_21, $item_22, $item_23, $item_24, $item_25
                )){
                echo "Bind failed: " .$stmt->errno." ".$stmt->error;
            }


            while($stmt->fetch()){
                $item_array = array($max_items,
                    $item_1, $item_2, $item_3, $item_4, $item_5,
                    $item_6, $item_7, $item_8, $item_9, $item_10,
                    $item_11, $item_12, $item_13, $item_14, $item_15,
                    $item_16, $item_17, $item_18, $item_19, $item_20,
                    $item_21, $item_22, $item_23, $item_24, $item_25
                );
                echo "<tr>\n<td rowspan = 2>\n".$id."\n<td><strong>".$name."\n</strong>\n";
                echo '<td rowspan = 2><form action="./categories.php"
                          method = "post">
                          <input type="submit" name="DeleteRow" value="delete" class="redbtn">
                          <input type="hidden" name="DeleteRowID" value="'.$id.'">
                        </form>';
                echo '<td rowspan = 2><form action="./categories.php"
                          method = "post">
                          <input type="submit" name="Edit" value="edit" class="blubtn">
                          <input type="hidden" name="EditID" value="'.$id.'">
                        </form>';
                echo "</tr>";
                echo "<tr>\n<td>\n<em><strong>Sub-Categories:</em></strong><br>";
                $seperator = "";
                for ($i=1; $i < $max_items; $i++) {
                    if ($item_array[$i] === "" || !isset($item_array[$i]))
                        break; 
                    echo $seperator.$item_array[$i];
                    $seperator = " | ";
                    if ($i % ($max_items/4) === 0){
                        echo "<br>";
                        $seperator = "";
                    }
                }
                echo "";
                echo "</tr>";
            }
            $stmt->close();
    echo "</table>
    </fieldset>";

    echo $ftr;
?>
