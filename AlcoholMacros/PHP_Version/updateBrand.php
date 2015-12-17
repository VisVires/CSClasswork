<?php
//Turn on error reporting
ini_set('display_errors', 'On');
//Connects to the database
$mysqli = new mysqli('oniddb.cws.oregonstate.edu','georgew-db','bCCYYhX7UVXshOjb','georgew-db');
//check connnection
if($mysqli->connect_errno){
	echo 'Connection error ' . $mysqli->connect_errno . ' ' . $mysqli->connect_error;
	}
?>

<!doctype html>
<html>
<head>
	<title>Booze Macros</title>
	<link href='css/bootstrap.min.css' rel='stylesheet' type='text/css'>
	<link href='css/custom.css' rel='stylesheet' type='text/css'>
</head>
<body>
	<form role='form' action='finishUpdateBrand.php' method='post'>
		<fieldset>
			<legend>Brand Info</legend>
			<label for='brand'>Brand Name</label>
	<?php
		if(!($stmt = $mysqli->prepare("SELECT b.id, b.name, c.id, c.company_size, r.id, r.city, r.state_country, b.parent_company FROM region r INNER JOIN brand b ON r.id = b.region_id INNER JOIN company_size c ON b.company_size_id = c.id WHERE b.id = ?"))){
			 echo 'Prepare failed: ' . $stmt->errno . ' ' . $stmt->error;
		}
		//bind param to query
		if(!($stmt->bind_param('i', $_GET['brand_id']))){
			echo 'Bind failed: ' . $stmt->errno . ' ' . $stmt->error;
		}

		if(!$stmt->execute()){
			echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
		}

		//get results from query
		if(!($stmt->bind_result($brand_id, $brandName, $cid, $csize, $region_id, $city, $state_country, $parent_company))){
			echo 'Bind failed: ' . $stmt->errno . ' ' . $stmt->error;
		}

		while($stmt->fetch()){
			echo "<input type='hidden' name='brand_id' value='".$brand_id."' required>";
			echo "<input type='text' class='form-control' name='brand' value='".$brandName."' placeholder='".$brandName."'>\n";
			echo "<label for='parent'>Parent Company</label>\n";
			echo "<input type='text' class='form-control' name='parent' value='".$parent_company."' placeholder='".$parent_company."'>\n";
			echo "<label for='company_size'>Business Size</label>\n";
			echo "<select class='form-control' name='company_size'>\n";
			//get company size info
			echo "<option value='".$csize."'>".$csize."</option>";

			// if(!($stmt2 = $mysqli->prepare("SELECT company_size FROM company_size WHERE id != ?"))){
			//  	echo 'Prepare failed: ' . $mysqli->connect_errno . ' ' . $mysqli->connect_error;
			// }

			// if(!($stmt2->bind_param('i', $cid))){
			// 	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
			// }

			// if(!$stmt2->execute()){
			// 	echo 'Execute failed: ' . $mysqli->connect_errno . ' ' . $mysqli->connect_error;
			// }
			
			// if(!$stmt2->bind_result($size)){
			// 	echo 'Bind failed: ' . $mysqli->connect_errno . ' ' . $mysqli->connect_error;
			// }
			// //set company size to options
			// while($stmt2->fetch()){
			// echo "<option value='".$size.">".$size."</option>\n";
			// }
			echo "</select>";
			// echo "<label for='city'>City, State/Country</label>\n
			//  		<select class='form-control' name='city'>\n";
			
			// echo "<option value='".$city."|".$state_country."'>".$city.", ".$state_country."</option>\n";
			//get city and state_country from mysql
			//if(!$stmt3 = $mysqli->prepare("SELECT city, state_country FROM region WHERE id NOT ?")){
			// 	echo 'Prepare failed: ' . $mysqli->connect_errno . ' ' . $mysqli->connect_error;
			// }

			// if(!($stmt3->bind_param("i", $region_id))){
			// 	echo "Bind failed: " . $stmt->errno . " " . $stmt->error;
			// }

			// if(!$stmt3->execute()){
			// 	echo 'Execute failed: ' . $mysqli->connect_errno . ' ' . $mysqli->connect_error;
			// }

			// if(!$stmt3->bind_result($cityNext, $countryNext)){
			// 	echo 'Bind failed: ' . $mysqli->connect_errno . ' ' . $mysqli->connect_error;
			// }
			// //set each city/state_country with '|' delimiter
			// while($stmt3->fetch()){
			// 	echo "<option value='".$cityNext."|".$countryNext."'>".$cityNext.", ".$countryNext."</option>\n";
			// }
			// echo "</select>";			
		}						
?>
	</fieldset>
	<input type='submit' value='Update Brand' class='btn btn-info'>
</form><!--End form-->
</body>
</html>