<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli('oniddb.cws.oregonstate.edu','georgew-db','bCCYYhX7UVXshOjb','georgew-db');
//check connnection
if($mysqli->connect_errno){
	echo 'Connection error ' . $mysqli->connect_errno . ' ' . $mysqli->connect_error;
	}

if(!($stmt = $mysqli->prepare("UPDATE brand SET name = ?, parent_company = ?,  company_size_id = (SELECT id FROM company_size WHERE company_size = ?) WHERE id = ?"))){
			 echo 'Prepare failed: ' . $stmt->errno . ' ' . $stmt->error;
}
// region_id = (SELECT id FROM region WHERE city = ? AND state_country = ?)
//seperate city and state_country
//list($city, $state_country) = explode('|', $_POST['city']);
//$city, $state_country,
//bind param to query
if(!($stmt->bind_param('sssi', $_POST['brand'], $_POST['parent'], $_POST['company_size'], $_POST['brand_id']))){
	echo 'Bind failed: ' . $stmt->errno . ' ' . $stmt->error;
}

if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Updated " . $stmt->affected_rows . " rows in Brand";
}
?>

<!doctype html>
<html>
<head>
	<title>Booze Macros</title>
	<link href='css/bootstrap.min.css' rel='stylesheet' type='text/css'>
	<link href='css/custom.css' rel='stylesheet' type='text/css'>
</head>
<body>
<!--Go Back to brand table-->
<a href="brandTable.php"><button class="btn btn-info btn-xs">Back </button></a>
</body>
</html>