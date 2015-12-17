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
		<div class="col-sm-3"></div><!-- Spacing -->
		<div class="col-sm-6">
			<!--Back Button -->
			<button class="btn btn-info btn-xs" onclick="history.go(-1)">Back </button>
			<div class="table-responsive">
				<table class="table table-striped table-hover">
					<caption>Glassware</caption>
					<thead>
						<tr>
							<th>Name</th>
							<th>Material</th>
							<th>Size (oz)</th>
						</tr>
					</thead>
					<tbody>
						<?php
						//get material, size and name of glassware	
						if(!$stmt = $mysqli->prepare("SELECT g.id, g.name, m.material_type, g.size FROM glassware g INNER JOIN material m ON g.material_id = m.id ORDER BY g.name")){
								echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->execute()){
								echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							if(!$stmt->bind_result($gid, $name, $material, $size)){
								echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
							}
							//get options
							while($stmt->fetch()){
								echo "<tr>\n";
								echo "<td>".$name."</td>\n<td>".$material."</td>\n<td>".$size."</td>\n<td><form role='form' method='GET' action='deleteGlassware.php'><input type='hidden' name='glass_id' value='".$gid."'><input type=\"submit\"class=\"btn btn-info btn-xs\" name=\"deleteGlass\" value=\"Delete\"></form></td>\n";
								echo "</tr>\n";
							}
						?>
					</tbody>
				</table>
			</div><!-- End Table -->
			<a href="addGlass.php"><input type="button" class="btn btn-info btn-xs" name="addGlass" value="Add Glass"></a>	
		</div> <!-- End Col -->
		<div class="col-sm-3"></div><!-- Spacing -->
	</div>
</body>
</html>