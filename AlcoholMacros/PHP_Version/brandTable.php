<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli("oniddb.cws.oregonstate.edu","georgew-db","bCCYYhX7UVXshOjb","georgew-db");
//check connnection
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
	<div class="col-sm-1"></div>
	<div class="col-sm-10">
		<button class="btn btn-info btn-xs" onclick="history.go(-1)">Back </button>
	</div>
	<div class="col-sm-1"></div>
</div><!--End Back Button row-->
	<div class="row">
		<div class="col-sm-1"></div><!--Spacing-->
		<div class="col-sm-10">
			<div class="table-responsive">
				<table class="table table-striped table-hover">
					<caption>Brand Information</caption>
					<thead>
						<tr>
							<th>Brand Name</th>
							<th>Parent Company</th>
							<th>Company Size</th>
							<th>City</th>
							<th>Country</th>
							<th>Delete</th>
						</tr>
					</thead>
					<tbody>
						<?php
							//select brand info from brand
							if(!$stmt = $mysqli->prepare("SELECT b.id, b.name, b.parent_company, cs.company_size, r.city, r.state_country FROM region r INNER JOIN brand b ON r.id = b.region_id INNER JOIN company_size cs ON b.company_size_id = cs.id ORDER BY b.name")){
								echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->execute()){
								echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->bind_result($id, $name, $parent, $size, $city, $country)){
								echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							//set brand info to table cells
							while($stmt->fetch()){
								echo "<tr>\n";
								echo "<td>".$name."</td>\n<td>".$parent."</td>\n<td>".$size."</td>\n<td>".$city."</td>\n<td>".$country."</td>\n<td><form role='form' method='GET' action='updateBrand.php'><input type='hidden' name='brand_id' value='".$id."'><input type=\"submit\"class=\"btn btn-info btn-xs\" name=\"updateBrand\" value=\"Edit Brand\"></form>";
								echo "</tr>\n";
							}
						?>
					</tbody>
				</table>
			</div>
			<!--Add Brand To List -->
			<a href="addBrand.php"><input type="button" class="btn btn-info btn-xs" name="addBrand" value="Add Brand"></a>	
		</div><!--End Main Col -->
		<div class="col-sm-1"></div><!-- Spacing-->
	</div><!--End Main Row -->
</body>
</html>