<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");

//check connection
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

//fill est_drink
if(!($stmt = $mysqli->prepare("INSERT INTO est_drink (est_id, drink_id) 
VALUES ((SELECT e.id FROM est e INNER JOIN region r ON e.region_id = r.id WHERE e.est_name = ? AND r.city = ? AND r.state_country = ?), (SELECT d.id FROM drink d INNER JOIN brand b ON d.brand_id = b.id WHERE d.name = ? AND b.name = ?))"))){
	 echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

//split brand and drink
list($brand, $drink) = explode('|', $_POST['drink']);
//split city state est
list($est, $city, $state_country) = explode('|', $_POST['est']);

//bind param to ?
if(!($stmt->bind_param("sssss", $est, $city, $state_country, $drink, $brand))){
	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//check success of query
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to est_drink";
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
<!-- Back to Start -->
<a href="start.php"><button class="btn btn-info">Back to Start</button></a>
</body>
</html>