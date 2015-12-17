<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");

//check connection
if(!$mysqli || $mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}

//insert into price range
if(!($stmt = $mysqli->prepare("INSERT INTO est_price_range (price_range) VALUES (?)"))){
	 echo "Prepare failed: " . $stmt->errno . " " . $stmt->error;
}

//bind range info to range
if(!($stmt->bind_param("s", $_POST['range']))){
	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
}

//check if query is successful
if(!$stmt->execute()){
	echo "Execute failed: " . $stmt->errno . " " . $stmt->error;
} else {
	 echo "Added " . $stmt->affected_rows . " rows to price_range";
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
<!-- Back to Add Establishment -->
	<a href="addEst.php"><button class="btn btn-info">Back to Add Place</button></a>
</body>
</html>
