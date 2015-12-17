<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//check for errors
if($mysqli->connect_errno){
	echo "Connection error " . $mysqli->connect_errno . " " . $mysqli->connect_error;
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
	<form action="newDrinkType.php" role="form" method="POST">
		<fieldset>
			<legend>Add New Drink Type</legend>
			<label for="type">Type</label>
				<input type="text" name="drink_type" class="form-control" value="" required>
		</fieldset>
		<input type="submit" class="btn btn-info">
	</form><!--End Form-->
</body>