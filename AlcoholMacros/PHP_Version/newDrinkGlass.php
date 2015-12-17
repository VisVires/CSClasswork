<?php
//Turn on error reporting
ini_set('display_errors', 'On');

//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");

//check connection
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

//insert pair into drink_glassware
if(!($stmt = $mysqli->prepare("INSERT INTO drink_glassware (drink_id, glassware_id) VALUES ((SELECT id FROM drink WHERE name = ?), (SELECT id FROM glassware WHERE name = ?))"))){
	 echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

//seperate brand and drink using "|" delimited
list($brand, $drink) = explode('|', $_POST['drink']);

//bind drink and glass to ? in query
if(!($stmt->bind_param("ss", $drink, $_POST['glass']))){
	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//output confimation
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to drink_glassware";
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
<!-- Back to start -->
<a href="start.php"><button class="btn btn-info">Back to Start</button></a>
</body>
</html>