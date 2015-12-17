<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//Check for errors
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
	<form action="newGlass.php" role="form" method="POST">
		<fieldset>
			<legend>Add Glassware</legend>
			<label for="glassware">Glassware Type</label>
				<!--Get Name-->
				<input type="text" name="glassware" class="form-control" value="" required>
			<label for="size">Size(oz)</label>
				<!--Get Size-->
				<input type="number" name="size" class="form-control" value="">
			<label for="material">What is it made of?</label>
				<!--Get Material-->
				<select name="material" class="form-control">
					<?php
						//get materials from material_type
						if(!$stmt = $mysqli->prepare("SELECT material_type FROM material")){
							echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->execute()){
							echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($material)){
							echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						//set material options
						while($stmt->fetch()){
							echo "<option value='" .$material. " '> " .$material."</option>";
						}
					?>
				</select>
		</fieldset><!--End Field-->
		<input type="submit" class="btn btn-info">
	</form><!--End Form-->
</body>