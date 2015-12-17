<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");

//check connection
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

//insert data into material
if(!($stmt = $mysqli->prepare("INSERT INTO material (material_type) VALUES (?)"))){
	 echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

//bind param to material
if(!($stmt->bind_param("s", $_POST['material']))){
	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//check if successful
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to material";
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
<!-- Back to Start-->
	<a href="start.php"><button class="btn btn-info">Back to Start</button></a>
</body>
</html>