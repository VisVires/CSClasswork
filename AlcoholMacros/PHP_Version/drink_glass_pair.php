<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//check connection 
if(!$mysqli || $mysqli->connect_errno){
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
	<div class="col-sm-1"></div><!--Spacing -->
	<div class="col-sm-10">
		<div class="form-group">
		<fieldset>
			<legend>Which Glass Works Best for the Drink?</legend>
			<form role="form" class="form-horizontal" action="newDrinkGlass.php" method="post">
				<fieldset>
				<!-- Get Glassware Info-->
				<label for="glass">Glassware: </label>
					<div class="form-group row">
						<div class="col-sm-3">
							<select class="form-control" name="glass">
							<?php
								if(!($stmt = $mysqli->prepare("SELECT name, material_id, size FROM glassware"))){
									echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
								}
								if(!$stmt->execute()){
									echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
								}
								if(!$stmt->bind_result($name, $material, $size)){
									echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
								}
								while($stmt->fetch()){
									echo "<option value='" .$name. " '> " . $name ."</option>";
								}
							?>
							</select>
						</div>
						<div class="col-sm-3">
						<!--Add Glassware -->
							<a href="addGlass.php"><input type="button" class="btn btn-info" name="addGlass" value="Add Glassware To List"></a>
						</div>
						<div class="col-sm-3">
						<!--Get Drink Info -->
							<select class="form-control" name="drink">
							<?php
								//Get brand and drink names
								if(!($stmt = $mysqli->prepare("SELECT b.name, d.name FROM brand b INNER JOIN drink d ON b.id = d.brand_id"))){
									echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
								}
								if(!$stmt->execute()){
									echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
								}
								if(!$stmt->bind_result($bname, $dname)){
									echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
								}
								//set options to brand and drink names
								while($stmt->fetch()){
									echo "<option value='" .$bname."|".$dname." '>".$bname." ".$dname."</option>";
								}
							?>
							</select>
						</div>	
						<div class="col-sm-3">
							<!--Add Drink -->
							<a href="addItem.php"><input type="button" class="btn btn-info" name="addGlass" value="Add Drink To List"></a>
						</div>
					</div>
				</fieldset><!--End Field -->
				<input type="submit" name="pair" value="Pair" class="btn btn-info">
			</form><!--End Form -->
		</fieldset><!--End outer Field -->
		</div><!--End Form Group -->
	</div><!--End Outer Col -->
	<div class="col-sm-1"></div><!-- Spacing -->
</body>
</html>