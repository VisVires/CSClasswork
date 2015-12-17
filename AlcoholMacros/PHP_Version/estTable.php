<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//check connection info
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
		<div class="col-sm-2"></div><!--Spacing -->
		<div class="col-sm-8">
			<button class="btn btn-info btn-xs" onclick="history.go(-1)">Back </button>
			<div class="table-responsive">
				<table class="table table-striped table-hover">
					<caption>Establishment</caption>
					<thead>
						<tr>
							<th>Name</th>
							<th>City</th>
							<th>Country</th>
							<th>Establishment Type</th>
							<th>Price Range</th>
						</tr>
					</thead>
					<tbody>
						<?php
						//get establishment info name, city, state/country, type and price	
						if(!$stmt = $mysqli->prepare("SELECT e.est_name, r.city, r.state_country, tmp.type, pr.price_range FROM region r INNER JOIN est e ON r.id = e.region_id INNER JOIN(SELECT et.type, e.id, e.est_price_range_id FROM est_type et INNER JOIN est e ON et.id = e.type_id) AS tmp ON e.id = tmp.id INNER JOIN est_price_range pr ON tmp.est_price_range_id = pr.id ORDER BY e.est_name")){
								echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->execute()){
								echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->bind_result($name, $city, $country, $type, $price)){
								echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							//set info to table
							while($stmt->fetch()){
								echo "<tr>\n";
								echo "<td>".$name."</td>\n<td>".$city."</td>\n<td>".$country."</td>\n<td>".$type."</td>\n<td>".$price."</td>\n";
								echo "</tr>\n";
							}
						?>
					</tbody>
				</table><!--End Table-->
			</div><!--End Table Div-->
			<a href="addEst.php"><input type="button" class="btn btn-info btn-xs" name="addEst" value="Add Place"></a>	
		</div><!--Outer Col-->
		<div class="col-sm-2"></div> <!--Spacing-->
	</div>
</body>
</html>