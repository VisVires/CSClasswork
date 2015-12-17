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
	<form role="form" action="newBrand.php" method="post">		
		<fieldset>
			<legend>Brand Info</legend>
			<label for="brand">Brand Name</label>
				<input type="text" class="form-control" name="brand" value="" required>
			<label for="parent">Parent Company</label>
				<input type="text" class="form-control" name="parent" value="">
			<label for="company_size">Business Size</label>
				<select class="form-control" name="company_size">
					<?php
						//empty first option
						//get company size info
						echo "\t<option value='\"\"'></option>\n";
						if(!$stmt = $mysqli->prepare("SELECT company_size FROM company_size")){
							echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->execute()){
							echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($size)){
							echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						//set company size to options
						while($stmt->fetch()){
							echo "<option value='".$size."'>".$size."</option>\n";
						}
					?>
				</select>
			<label for="city">City, State/Country</label>
				<select class="form-control" name="city">
					<?php
						//get city and state_country from mysql
						if(!$stmt = $mysqli->prepare("SELECT city, state_country FROM region")){
							echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->execute()){
							echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($city, $country)){
							echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						//set each city/state_country with "|" delimiter
						while($stmt->fetch()){
							echo "<option value='".$city."|".$country."'>".$city.", ".$country."</option>";
						}
					?>
				</select>
			<!-- Add Region Button -->
			<a href="addRegion.php"><input type="button" class="btn btn-info" value="Add Region"></a>	
		</fieldset>
		<input type="submit" value="Add Brand" class="btn btn-info">
	</form>	<!--End form-->
</body>