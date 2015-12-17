<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");

//check connection
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

//insert into drink type
if(!($stmt = $mysqli->prepare("INSERT INTO drink_type (drink_type) VALUES (?)"))){
	 echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

//bind drink type to ?
if(!($stmt->bind_param("s", $_POST['drink_type']))){
	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//output success 
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to drink_type ";
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