<?php
error_reporting(E_ALL);
ini_set('display_errors', 'On');
//declares some useful vars
$hdr = "{\n";
$ftr = "\n}";
$item = array(26);

include '../cats.php';
include '../pass.php';
$mysqli = new mysqli("mysql.eecs.oregonstate.edu", "cs419-g6", $db_pass, "cs419-g6");
if ($mysqli->connect_errno){
    echo "Database connection failed: (" . $mysqli->connect_errno . ")" . $mysqli->connect_error;
}

echo $hdr;

//a function to pull out the accept data from that data structure
function findaccept($accepts, $cat_id, $sub_id){
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

        if ($item[0] == $cat_id && in_array($sub_id, $item[1])){
            return true;
        }

    }

    return false;
}

//check request method
if ($_SERVER['REQUEST_METHOD'] === 'GET'){
    //return JSON based on businesses by ID
    //otherwise return them all
    if (isset($_GET['BusinessByID'])){
        if(!($stmt = $mysqli->prepare("SELECT name, address, phone, url, accepts, zip, hours FROM businesses
            WHERE id = ?"))){
            echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->bind_param("s", $_GET['BusinessByID'])){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->bind_result($name, $address, $phone, $url, $accepts, $zip, $hours)){
            echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
        }
        echo "\"Business\":\n";
        while($stmt->fetch()){
            echo "{\n \"id\": \"$_GET[BusinessByID]\",\n";
            echo "\"name\": \"$name\",\n";
            echo "\"address\": \"$address\",\n";
            echo "\"phone\": \"$phone\",\n";
            echo "\"url\": \"$url\",\n";
            echo "\"hours\": \"$hours\",\n";
            echo "\"zip\": \"$zip\",\n";
            echo "\"accepts\": \"".$accepts."\"\n";
            echo "}\n";
            
        }
        $stmt->close();
    //all buisnesses
    } else if (isset($_GET['BusinessAll'])){
        if(!($stmt = $mysqli->prepare("SELECT name, address, phone, url, accepts, zip, hours, id FROM businesses
            "))){
            echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->bind_result($name, $address, $phone, $url, $accepts, $zip, $hours, $id)){
            echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
        }
        $seperator = "";
        echo "\"Businesses\": [\n";
        while($stmt->fetch()){
            echo $seperator;
            echo "{\n \"id\": \"$id\",\n";
            echo "\"name\": \"$name\",\n";
            echo "\"address\": \"$address\",\n";
            echo "\"phone\": \"$phone\",\n";
            echo "\"url\": \"$url\",\n";
            echo "\"hours\": \"$hours\",\n";
            echo "\"zip\": \"$zip\",\n";
            echo "\"accepts\": \"".$accepts."\"\n";
            echo "}";
            $seperator = ",\n";
        }
        echo "\n]";
        $stmt->close();
    //category by id
    } else if (isset($_GET['CategoryByID'])){
        if(!($stmt = $mysqli->prepare("SELECT name, id,
            item_1, item_2, item_3, item_4, item_5,
            item_6, item_7, item_8, item_9, item_10, 
            item_11, item_12, item_13, item_14, item_15,
            item_16, item_17, item_18, item_19, item_20, 
            item_21, item_22, item_23, item_24, item_25
            FROM categories
            WHERE id = ?"))){
            echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->bind_param("s", $_GET['CategoryByID'])){
            echo "Bind failed: " .$stmt->errno." ".$stmt->error;
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
        echo "\"Category\": ";
        $seperator = "";
        while($stmt->fetch()){
            echo $seperator;
            $seperator = "";
            echo "{\n \"id\": \"$id\",\n";
            echo "\"name\": \"$name\",\n";
            echo "\"items\": [\n";
            for ($i = 1; $i <26; $i++){
                if ($item[$i] == "")
                    break;
                echo $seperator;
                echo "\"".$item[$i]."\"";
                $seperator = ",\n";
            }
            echo "]}";
        }
        $stmt->close();
    //all categories
    } else if (isset($_GET['CategoryAll'])){
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
        $seperator = "";
        echo "\"Categories\": [\n";
        while($stmt->fetch()){
            echo $seperator;
            $seperator = "";
            echo "{\n \"id\": \"$id\",\n";
            echo "\"name\": \"$name\",\n";
            echo "\"items\": [\n";
            for ($i = 1; $i <26; $i++){
                if ($item[$i] == "")
                    break;
                echo $seperator;
                echo "\"".$item[$i]."\"";
                $seperator = ",\n";
            }
            echo "]}";
            $seperator = ",\n";
        }
        echo "\n]";
        $stmt->close();
    //return JSON of businesses that match a category/sub-category pair
    } else if (isset($_GET['BusinessesByCatID']) && isset($_GET['SubcategoryID'])) {
        
        if(!($stmt = $mysqli->prepare("SELECT name, address, phone, url, accepts, zip, hours, id FROM businesses
            "))){
            echo "Prepare failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->execute()){
            echo "Execute failed: "  . $stmt->errno . " " . $stmt->error;
        }
        if(!$stmt->bind_result($name, $address, $phone, $url, $accepts, $zip, $hours, $id)){
            echo "Bind failed: "  . $stmt->errno . " " . $stmt->error;
        }
        $seperator = "";
        echo "\"Businesses\": [\n";
        while($stmt->fetch()){
            if (findaccept($accepts, $_GET['BusinessesByCatID'], $_GET['SubcategoryID'])){
                echo $seperator;
                echo "{\n \"id\": \"$id\",\n";
                echo "\"name\": \"$name\",\n";
                echo "\"address\": \"$address\",\n";
                echo "\"phone\": \"$phone\",\n";
                echo "\"url\": \"$url\",\n";
                echo "\"hours\": \"$hours\",\n";
                echo "\"zip\": \"$zip\",\n";
                echo "\"accepts\": \"".$accepts."\"\n";
                echo "}";
                $seperator = ",\n";
            }
        }
        echo "\n]";
        $stmt->close();
    }
}
    echo $ftr;
?>
