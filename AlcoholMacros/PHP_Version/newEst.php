<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");

//Check Connection
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

//set est name, type and price range query
$sql1 = "INSERT INTO est (est_name,type_id,est_price_range_id, region_id)
VALUES (?,(SELECT id FROM est_type WHERE type = ?), (SELECT id FROM est_price_range WHERE price_range = ?),(SELECT id FROM region WHERE city = ? AND state_country = ?))";

//split city and state from city
list($city, $state_country) = explode('|', $_POST['city']);

//run query
if(!($stmt = $mysqli->prepare($sql1))){
	  echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

//bind param to ?
if(!($stmt->bind_param("sssss", $_POST['establishment'], $_POST['est_type'], $_POST['est_price'], $city, $state_country))){
	 echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//execute query
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to Establishment";
}

?>
<!doctype html>
<html>
<head>
	<title>Booze Macros</title>
	<link href="css/bootstrap.min.css" rel="stylesheet" type="text/css">
	<link href="css/custom.css" rel="stylesheet" type="text/css">
</head>
<body>
<!-- Back to  Start -->
<a href="start.php"><button class="btn btn-info">Back to Start</button></a>
</body>
</html>