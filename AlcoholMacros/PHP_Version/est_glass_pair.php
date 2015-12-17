<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//check connection
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
	<div class="row">
		<div class="col-sm-2"></div><!--Spacing-->
		<div class="col-sm-8">
			<div class="form-group">
				<form role="form" class="form-vertical" action="newEstGlass.php" method="post">
					<fieldset>
						<legend>Watering Hole Glassware</legend>
						<div class="form-group row">
							<div class="col-sm-6">
							<!--Get Glassware-->
							<label for="glass">Glassware: </label>
								<select class="form-control" name="glass">
									<?php
										//select name, material and size from glassware 
										if(!($stmt = $mysqli->prepare("SELECT name, material_id, size FROM glassware"))){
											echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										if(!$stmt->execute()){
											echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										if(!$stmt->bind_result($name, $material, $size)){
											echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										//add to options
										while($stmt->fetch()){
											echo "<option value='" .$name. " '> " . $name ."</option>";
										}
									?>
								</select>
							</div>
							<div class="col-sm-6">
							<!--Get info for Establishment-->
							<label for="est">Establishment: </label>		
								<select class="form-control" name="est">
									<?php
										//select name, city and state from establishment
										if(!($stmt = $mysqli->prepare("SELECT e.est_name, r.city, r.state_country FROM est e INNER JOIN region r ON e.region_id = r.id"))){
											echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										if(!$stmt->execute()){
											echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										if(!$stmt->bind_result($name, $city, $state_country)){
											echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										//set option
										while($stmt->fetch()){
											echo "<option value='" .$name."|".$city."|".$state_country."'> " .$name." ".$city.", ".$state_country."</option>";
										}
									?>
								</select>
							</div>	
						</div><!--End form row-->
						<input type="submit" class="btn btn-info" value="Pair">
					</fieldset><!--End fieldset-->
				</form><!--End Form-->
			</div><!--Outer Form Group-->
		</div><!--Outer Col-->
		<div class="col-sm-2"></div>
	</div><!--Outer Row-->
</body>
</html>