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
		<div class="col-sm-1"></div><!--Spacing-->
		<div class="col-sm-10">
			<!--Back Button -->
			<a href="start.php"><button class="btn btn-info btn-xs">Back </button></a>
			<div class="table-responsive">
				<table class="table table-striped table-hover">
					<caption>Drinks</caption>
					<thead>
						<tr>
							<th>Brand Name</th>
							<th>Drink Name</th>
							<th>Drink Type</th>
							<th>Carbs(g)</th>
							<th>Protein(g)</th>
							<th>Fat(g)</th>
							<th>Proof</th>
							<th>Alcohol(g)</th>
							<th>Serving Size</th>
							<th>Calories Per Serving</th>
						</tr>
					</thead>
					<tbody>
						<?php
							//Get Drink Info from drinks
							if(!$stmt = $mysqli->prepare("SELECT d.id, b.name, d.name, dt.drink_type, d.carbs, d.protein, d.fat, d.proof, d.serving_size FROM brand b INNER JOIN drink d ON b.id = d.brand_id INNER JOIN drink_type dt ON d.drink_type_id = dt.id ORDER BY b.name;")){
								echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->execute()){
								echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->bind_result($did, $brandName, $drinkName, $drinkType, $carbs, $protein, $fat, $proof, $size)){
								echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							while($stmt->fetch()){
								//calculate grams of alcohol
								$alcohol = (8 * (($size * 29.5735) * ($proof/2)))/1000;
								//calculate total calories
								$calories = (7 * $alcohol) + (4 * $carbs) + (4 * $protein) + (9 * $fat);
								//$alcohol = number_format((float)$alcohol,1);
								//put numbers and data in table
								echo "<tr>\n";
								echo "<td>".$brandName."</td>\n<td>".$drinkName."</td>\n<td>".$drinkType."</td>\n<td>".number_format((float)$carbs,1)."g</td>\n<td>".number_format((float)$protein,1)." g</td>\n<td>".number_format((float)$fat,1)." g</td>\n<td>".number_format((float)$proof,1)."</td>\n<td>".number_format((float)$alcohol,1)." g</td>\n<td>".number_format((float)$size,1)."oz</td>\n<td>".number_format((float)$calories,1)." cal</td>\n<td><form role='form' method='GET' action='deleteDrink.php'><input type='hidden' name='drink_id' value='".$did."'><input type=\"submit\"class=\"btn btn-info btn-xs\" name=\"deleteDrink\" value=\"Delete Drink\"></form></td>\n";
								echo "</tr>\n";
							}
						?>
					</tbody><!--End Table Body -->
				</table>
			</div>
			<!--Add Drink -->
			<a href="addItem.php"><input type="button" class="btn btn-info btn-xs" name="addDrink" value="Add Drink"></a>	
		</div>
		<div class="col-sm-1"></div><!--Spacing-->
	</div><!--End Row-->
</body>
</html>