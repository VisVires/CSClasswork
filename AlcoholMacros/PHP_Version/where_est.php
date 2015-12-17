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
		<form action="est_drink_pair.php" method="post" role="form" class="form-horizontal">
			<legend>Where are you Drinking?</legend>
			<!-- Get City State Info -->
			<select name="city" class="form-control">
				<?php
					//get city and state info from region
					if(!$stmt = $mysqli->prepare("SELECT city, state_country FROM region")){
						echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->execute()){
						echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					if(!$stmt->bind_result($city, $country)){
						echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
					}
					//set each option
					while($stmt->fetch()){
						echo "<option value='".$city."|".$country."'>".$city.", ".$country."</option>";
					}
				?>
			</select>
			<input type="submit" name="getPlace" class="btn btn-info" value="Submit Location">
			<!-- Back Button -->
			<button class="btn btn-info" onclick="history.go(-1)">Back </button>
		</form><!-- End Form -->
	</div><!-- End Div Col -->
	<div class="col-sm-2"></div><!--Spacing-->
</div><!--Outside row-->
</body>
</html>