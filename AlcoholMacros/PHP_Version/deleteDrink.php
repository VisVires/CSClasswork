<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//check connnection
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
if(!($stmt = $mysqli->prepare("DELETE FROM drink WHERE id = ?"))){
	 echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

if(!($stmt->bind_param("i", $_GET['drink_id']))){
	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//check status
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Deleted " . $stmt->affected_rows . " row from drink";
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
<div class="row">
	<div class="col-sm-1"></div>
	<div class="col-sm-10">
		<a href="drinkTable.php"><button class="btn btn-info btn-xs">Back </button></a>
	</div>
	<div class="col-sm-1"></div>
</div><!--End Back Button row-->