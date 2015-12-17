<?php
//Turn on error reporting
ini_set('display_errors', 'On');

//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

//add to database
if(!($stmt = $mysqli->prepare("INSERT into drink (name, drink_type_id, protein, carbs, fat, alcohol, proof, brand_id, serving_size) VALUES (?,(SELECT id FROM drink_type WHERE drink_type = ?), ?, ?, ?, ?, ?, (SELECT id FROM brand WHERE name = ?), ?)"))){
	 echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

//multiply percentage by 2 to get proof
$proof = $_POST['percent'] * 2.00;

//fill in parameters for drink
if(!($stmt->bind_param("ssdddidsd", $_POST['drink'], $_POST['type'], $_POST['protein'], $_POST['carbs'], $_POST['fat'], $_POST['alcohol'], $proof, $_POST['brand'], $_POST['serving_size']))){
	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//add rows
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to drink";
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
	<a href="start.php"><button class="btn btn-info">Back to Start</button></a>
</body>
</html>

