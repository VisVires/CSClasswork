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
	<link href="css/bootstrap.min.css" rel="stylesheet" type="text/css">
	<link href="css/custom.css" rel="stylesheet" type="text/css">
	<script src="js/ajax.js"></script>
</head>
<body>
<?php
	//get info from get request and set brand and servings
	$servings = $_GET['servings'];
	//filter based on drink name
	if(!($stmt = $mysqli->prepare("SELECT b.name, d.name, d.proof, d.carbs, d.protein, d.fat, d.serving_size FROM drink d INNER JOIN brand b ON d.brand_id = b.id WHERE b.name = ? AND d.name LIKE ?"))){
		echo "Prepare failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	//set variable for query
	if(!($stmt->bind_param("ss", $_GET['brand'], $_GET['drink']))){
		echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	} 

	if(!($stmt->execute())){
		echo "Execute failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	//bind results to variables
	if(!$stmt->bind_result($bname ,$dname, $proof, $carbs, $protein, $fat, $size)){
		echo "Bind failed: " . $mysqli->connect_errno . " " . $mysqli->connect_error;
	}
	//send info back with innerHTML
	while($stmt->fetch()){
		//get totals from servings
		$carbs = $carbs * $servings;
		$protein = $protein * $servings;
		$fat = $fat * $servings;
		//get alcohol grams
		$alcohol = (8 * (($size * 29.5735) * ($proof/2)))/1000;
		$alcohol = $alcohol * $servings;
		//get total calories
		$calories = (7 * $alcohol) + (4 * $carbs) + (4 * $protein) + (9 * $fat);
	    //inner html
	    echo "<tr>";
	    echo "<td></td>";
	    echo "<td>" . $bname ." ". $dname . "</td>";
	    echo "<td>" . $servings . "</td>";
	    echo "<td>" . number_format((float)$size,1) . "</td>";
	    echo "<td>" . number_format((float)$calories,1) . "</td>";
	    echo "<td>" . number_format((float)$alcohol,1) . "</td>";
	    echo "<td>" . number_format((float)$carbs,1) . "</td>";
	    echo "<td>" . number_format((float)$protein,1) . "</td>";
	    echo "<td>" . number_format((float)$fat,1) . "</td>";
	    echo "</tr>";
	}
	//if no drinks match input send message to user
	if($stmt->num_rows == 0 ){
		$name = "No Drinks Match That Criteria, Please Add Drink";
		echo "<p>".$name."</p>\n";
	}
?>
</body>
</html>