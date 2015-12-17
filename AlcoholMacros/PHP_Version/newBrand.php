<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//check connection
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
//insert info into brand table
 if(!($stmt = $mysqli->prepare("INSERT INTO brand (name, company_size_id, region_id, parent_company) VALUES (?,(SELECT id FROM company_size WHERE company_size = ?),(SELECT id FROM region WHERE city= ? AND state_country= ?), ?)"))){
	  echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}
//split city and state_country info
list($city, $state_country) = explode('|', $_POST['city']);

//bind parameters to ? in prepare
 if(!($stmt->bind_param("sssss", $_POST['brand'], $_POST['company_size'], $city, $state_country, $_POST['parent']))){
	 echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to Brand";
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
<!-- Back Button -->
<a href="start.php"><button class="btn btn-info">Back to Start</button></a>
</body>
</html>