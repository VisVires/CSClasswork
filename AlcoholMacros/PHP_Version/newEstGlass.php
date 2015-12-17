<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//check connection
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

//prepare insert statement to est_glassware
if(!($stmt = $mysqli->prepare("INSERT INTO est_glassware (est_id, glassware_id)
VALUES ((SELECT e.id FROM est e INNER JOIN region r ON e.region_id = r.id WHERE e.est_name = ? AND r.city = ? and r.state_country = ?),(SELECT id FROM glassware WHERE name = ?))"))){
	 echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

//split est, city and state country
list($est, $city, $state_country) = explode('|', $_POST['est']);

//bind param to ?
if(!($stmt->bind_param("ssss", $est, $city, $state_country, $_POST['glass']))){
	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//confirm success
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to est_glassware";
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