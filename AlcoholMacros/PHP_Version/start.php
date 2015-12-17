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

<!DOCTYPE html PUBLIC>
<html>
<head>
	<title>Booze Macros</title>
	<link href="css/bootstrap.min.css" rel="stylesheet" type="text/css">
	<link href="css/custom.css" rel="stylesheet" type="text/css">
	<script src="js/ajax.js"></script>
</head>
<body>
	<div class="row">
		<div class="col-sm-1"></div><!--Spacing Col-->
		<div class="col-sm-10">
			<div class="form-group">	
				<form role="form" onsubmit="getDrink()" action="ajax.php">
					<div class="row">
						<div class="col-sm-1"></div>
						<div class="col-sm-10">
							<legend>WHAT DID I DRINK?</legend>
						</div>
						<div class="col-sm-1"></div>
					</div>
					<div class="row">
						<div class="col-sm-1"></div>
						<div class="col-sm-5">
							<select class="form-control" name="brand" id="brand">
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
								</select>
						</div><!--div for brand-->
						<div class="col-sm-5">
							<input type="text" class="form-control" id="drink" name="drink" value="" required>
						</div>
						<div class="col-sm-1"></div>								
					</div>
					<div class="row">
						<div class="col-sm-1"></div>
						<div class="col-sm-5">
						<label for="servings">How many servings?</label> 
							<select class="form-control" name="servings" id="servings">
								<?php
								for($i=1; $i < 11; $i++){
									echo "<option value= ".$i."> " . $i . " servings"."</option>\n";
								}	
								?>
							</select>
						</div>
						<div class="col-sm-6"></div>
					</div>
					<div class="row">
						<div class="col-sm-1"></div>
						<div class="col-sm-10">
								<input type="submit" name="searchDrink" id="search" class="btn btn-info" value="Search Drinks">
						</div>
						<div class="col-sm-1"></div>
					</div>
				</form><!--End Form-->
			</div><!--form group-->
			<div class="row">
				<div class="col-sm-1"></div>
				<div class="col-sm-10">
					<div class="table-responsive">
						<table class="table table-striped table-hover">
							<caption>Your Macros</caption>
							<thead>
								<tr>
									<th></th>
									<th>Drink</th>
									<th>Servings</th>
									<th>Serving Size (oz)</th>
									<th>Calories</th>
									<th>Alcohol(g)</th>
									<th>Carbs(g)</th>
									<th>Protein(g)</th>
									<th>Fat(g)</th>
								</tr>
							</thead>
							<tbody id="drinkTable">
							</tbody>
						</table>
					</div>
				</div>
				<div class="col-sm-1"></div>
			</div><!--End Table Row-->
			<div id="buttons">
				<h2>Quick Links</h2>
				<div class="row">
					<h4>DRINKS</h4>
					<div class="col-sm-1"></div>
					<div class="col-sm-2">
						<a href="drinkTable.php"><input type="button" class="btn btn-info" name="" value="See Drinks"></a>
					</div>
					<div class="col-sm-2">
						<a href="drink_glass_pair.php"><input type="button" class="btn btn-info" name="" value="Pair with Glass"></a>
					</div>
					<div class="col-sm-2">
						<a href="where_est.php"><input type="button" class="btn btn-info " name="" value="Pair with Place"></a>
					</div>
					<div class="col-sm-2">
						<a href="addItem.php"><input type="button" class="btn btn-info " name="" value="Add Drink"></a>
					</div>
					<div class="col-sm-2">
						<a href="addDrinkType.php"><input type="button" class="btn btn-info " name="" value="Add Type"></a>
					</div>
				</div><!--End Drinks Links-->
				<div class="row">
					<h4>GLASSWARE</h4>
					<div class="col-sm-1"></div>
					<div class="col-sm-2">
						<a href="glassTable.php"><input type="button" class="btn btn-info " name="" value="See Glassware"></a>
					</div>
					<div class="col-sm-2">
						<a href="drink_glass_pair.php"><input type="button" class="btn btn-info " name="" value="Pair with Drink"></a>
					</div>
					<div class="col-sm-2">
						<a href="est_glass_pair.php"><input type="button" class="btn btn-info " name="" value="Pair with Place"></a>
					</div>
					<div class="col-sm-2">
						<a href="addGlass.php"><input type="button" class="btn btn-info " name="" value="Add Glassware"></a>
					</div>
					<div class="col-sm-2">
						<a href="addMaterial.php"><input type="button" class="btn btn-info " name="" value="Add Material"></a>
					</div>
				</div><!--End Glassware Links-->
				<div class="row">
					<h4>WATERING HOLE</h4>
					<div class="col-sm-1"></div>
					<div class="col-sm-2">
						<a href="estTable.php"><input type="button" class="btn btn-info " name="" value="See Places"></a>
					</div>
					<div class="col-sm-2">
						<a href="est_glass_pair.php"><input type="button" class="btn btn-info " name="" value="Pair with Glass"></a>
					</div>
					<div class="col-sm-2">
						<a href="where_est.php"><input type="button" class="btn btn-info " name="" value="Pair with Drink"></a>
					</div>
					<div class="col-sm-2">
						<a href="addEst.php"><input type="button" class="btn btn-info " name="" value="Add Place"></a>
					</div>
					<div class="col-sm-2">
						<a href="addEstType.php"><input type="button" class="btn btn-info " name="" value="Add Type"></a>
					</div>
				</div><!--End Establishment Links-->
				<div class="row">
					<h4>BRAND</h4>
					<div class="col-sm-1"></div>
					<div class="col-sm-2">
						<a href="brandTable.php"><input type="button" class="btn btn-info " name="" value="See Brands"></a>
					</div>
					<div class="col-sm-2">
						<a href="addBrand.php"><input type="button" class="btn btn-info " name="" value="Add Brand"></a>
					</div>
					<div class="col-sm-2">
						<a href="addSize.php"><input type="button" class="btn btn-info " name="" value="Add Company Size"></a>
					</div>
					<div class="col-sm-2"></div>
					<div class="col-sm-2"></div>
				</div><!--End Brand Links-->
				<div class="row">
					<h4>REGION</h4>
					<div class="col-sm-1"></div>
					<div class="col-sm-3">
						<a href="addRegion.php"><input type="button" class="btn btn-info " name="" value="Add Region"></a>
					</div>
					<div class="col-sm-3"></div>
					<div class="col-sm-3"></div>
					<div class="col-sm-3"></div>
				</div><!--End Region Links-->
			</div><!--End Buttons Div-->
		</div><!--Outer Col-->
		<div class="col-sm-1"></div><!--Spacing Col-->
	</div><!--Outer Row-->
</body>
</html>