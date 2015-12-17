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
	<div class="col-sm-2"></div>
	<div class="col-sm-8">
		<div class="form-group">
			<form role="form" class="form-vertical" action="newDrink.php" method="post">
				<fieldset>
					<legend>Add Drink</legend>
					<label for="drink">Drink: </label>
						<!--Get Brand-->
						<input type="text" class="form-control" name="drink" value="" required>	
						<label for="brand">Brand: </label>
						<div class="form-group row">
							<div class="col-sm-6">
								<select class="form-control" name="brand">
									<?php
										if(!$stmt = $mysqli->prepare("SELECT name FROM brand ORDER BY name")){
											echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										if(!$stmt->execute()){
											echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										if(!$stmt->bind_result($name)){
											echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
										}
										while($stmt->fetch()){
											echo "<option value='".$name."'>".$name."</option>";
										}
									?>
								</select><!--End Select -->
							</div>
							<div class="col-sm-3">
								<!--Add Brand -->
								<a href="addBrand.php"><input type="button" class="btn btn-info" name="addBrand" value="Add Brand"></a>
							</div>
								<!--See Brands -->
							<div class="col-sm-3">
								<a href="brandTable.php"><input type="button" class="btn btn-info" name="seeBrand" value="See Brand Info"></a>
							</div>
						</div>
						<label for="type">Type: </label>
							<!--Get Type-->
							<select class="form-control" name="type">
								<?php
									//select options from drink type
									if(!$stmt = $mysqli->prepare("SELECT drink_type FROM drink_type")){
										echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->execute()){
										echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->bind_result($type)){
										echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									//set types to options
									while($stmt->fetch()){
										echo "<option value='".$type."'>".$type."</option>";
									}
								?>
							</select>
					
				</fieldset><!--End Fieldset for Drink Info-->
				<fieldset>
					<legend>Nutrition Info: </legend>
						<div class="form-group row">
								<div class="col-sm-4">
									<label>Protein (g): 
									<!--Get Protein-->
										<input type="number" step="0.1" class="form-control" name="protein" value="" placeholder="0.0g">
									</label>
								</div>
								<div class="col-sm-4">
									<label>Carbs (g): 
									<!--Get Carbs-->
										<input type="number" step="0.1" class="form-control" name="carbs" value="" placeholder="0.0g">
									</label>
								</div>
								<div class="col-sm-4">
									<label>Fat (g):
									<!--Get Fat--> 
										<input type="number" step="0.1" class="form-control" name="fat" value="" placeholder="0.0g">
									</label>
								</div>
						</div><!--End Nutrition Row -->
						<div class="row">
							<div class="col-sm-4">
							<!--Get Alcohol Boolean-->
								<label for="alcohol">Does it contain alcohol? </label>
								<label class = "checkbox-inline">
										<input type = "radio" name = "alcohol" value = "true" checked> YES
									</label>

									<label class = "checkbox-inline">
	 									<input type = "radio" name = "alcohol" value = "false"> NO
									</label>
							</div>
							<div class="col-sm-4">
							<!--Get Percentage-->
								<label>Percentage: 
									<input type="number" step="0.1" class="form-control" name="percent" value="" placeholder="0.0%">
								</label>
							</div>
							<div class="col-sm-4">
							<!--Get Serving Size-->
								<label>Serving Size: 
									<input type="number" step="0.1" class="form-control" name="serving_size" value="" placeholder="0.0oz">
								</label>
							</div>
						</div><!--End Alcohol Row -->
				</fieldset>
				<input type="submit" class="btn btn-info" name="addItem" value="Add Drink">
			</form><!--End Form -->
		</div><!--End Form Group -->
	</div><!--Outer Col -->
	<div class="col-sm-2"></div>
</body>			
