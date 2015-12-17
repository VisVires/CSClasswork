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
<form role="form" action="newEst.php" method="post">
		<fieldset>
			<legend>Drinking Institutions</legend>
			<label for="establishment">Establishment</label>
			<div class="row">
				<div class="col-sm-9">
					<input type="text" class="form-control" name="establishment" value="" required>
				</div>
				<div class="col-sm-3">
					<a href="estTable.php"><input type="button" class="btn btn-info" name="seeEst" value="See Establishments"></a>
				</div>
			</div>
			<label for="est_type">Type of Establishment</label>
				<select class="form-control" name="est_type">
					<?php
						//get types for option
						if(!$stmt = $mysqli->prepare("SELECT type FROM est_type")){
							echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->execute()){
							echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($type)){
							echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						//set options
						while($stmt->fetch()){
							echo "<option value='".$type."'>".$type."</option>";
						}
					?>
				</select>
			<label for="est_price">Approximate Cost Per Drink</label>
				<select class="form-control" name="est_price">
					<?php
						//get price_range options
						if(!$stmt = $mysqli->prepare("SELECT price_range FROM est_price_range")){
							echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->execute()){
							echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($price_range)){
							echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						//set to options
						while($stmt->fetch()){
							echo "<option value='".$price_range."'>".$price_range."</option>";
						}
					?>
				</select>
			<label for="city">City, State/Country</label>
				<!-- <input list="city" name="city" class="form-control">	 -->
				<select class="form-control" name="city">
					<?php
						//get city/state options
						if(!($stmt = $mysqli->prepare("SELECT city, state_country FROM region"))){
							echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->execute()){
							echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						if(!$stmt->bind_result($city, $country)){
							echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
						}
						//set to options
						while($stmt->fetch()){
							echo "<option value='".$city."|".$country."'>".$city.", ".$country."</option>";
						}
					?>
				</select>
			<!--Add Region to options  -->
			<a href="addRegion.php"><input type="button" class="btn btn-info" value="Add Region"></a>	
			<!-- Add Price Range to options -->
			<a href="addPriceRange.php"><input type="button" class="btn btn-info" value="Add Price Range"></a>
			<input type="submit" name="addEst" class="btn btn-info">
		</fieldset><!--End Fieldset-->
	</form><!--End Form-->
</body>
</html>