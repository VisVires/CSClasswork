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
	<div class="col-sm-2"></div><!--Spacing-->
	<div class="col-sm-8">
		<div class="form-group">
			<form role="form" class="form-horizontal" action="newEstDrink.php" method="post">
				<fieldset>
					<legend>Where can you get it?</legend>
					<!--Get Place -->
					<label for="est">Establishment: </label>
						<div class="form-group row">
							<div class="col-sm-6">
								<select class="form-control" name="est">
								<?php
									//get city and state from post by splitting using "|" delimiter
									list($city, $state_country) = explode('|', $_POST['city']);
									echo $city. "\n";
									echo $state_country. "\n";
									//select establishment based on city and state/country
									if(!($stmt = $mysqli->prepare("SELECT e.est_name FROM est e INNER JOIN region r ON e.region_id = r.id WHERE r.city = ? AND r.state_country = ?"))){
										echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									//set city and state_country parameters
									if(!($stmt->bind_param("ss", $city, $state_country))){
										echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									} 

									if(!($stmt->execute())){
										echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									//bind est name to result
									if(!$stmt->bind_result($name)){
										echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									//output name city and country/state to options
									while($stmt->fetch()){
											echo "<option value='".$name."|".$city."|".$state_country." '> ".$name." ".$city.", ".$state_country."</option>\n";
											echo "</select>\n";
									}	
									//output error if no establishments
									if($stmt->num_rows == 0 ){	
										$name = "No Establishments Returned";
										echo "<option value='" .$name. " '> " .$name ."</option>\n";
										echo "</select>\n"; 
										echo "<p>No Establishments in that City, Please Add a Place!</p>\n";
									}

									echo "</div>\n</div>\n</fieldset>\n";
									//add establishment button
									echo "<a href=\"addEst.php\"><input type=\"button\" class=\"btn btn-info\" name=\"addEst\" value=\"Add New Place\"></a>\n";
									//if establishments are returned output pair button
									if($stmt->num_rows != 0){
									 	echo "<input type=\"submit\" name=\"pair\" value=\"Pair\" class=\"btn btn-info\">\n";
									}  
								?>
								</select>
							</div>
							<div class="col-sm-6">
								<select class="form-control" name="drink">
								<?php
									//select drink from list 
									if(!($stmt = $mysqli->prepare("SELECT b.name, d.name FROM brand b INNER JOIN drink d ON b.id = d.brand_id"))){
										echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->execute()){
										echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									if(!$stmt->bind_result($bname, $dname)){
										echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
									}
									//output drinks as options
									while($stmt->fetch()){
										echo "<option value='" .$bname."|".$dname." '>".$bname." ".$dname."</option>";
									}
								?>
								
			</form>
		</div>
	</div><!--End Outer Div-->
	<div class="col-sm-2"></div><!--Spacing-->
</body>
</html>
