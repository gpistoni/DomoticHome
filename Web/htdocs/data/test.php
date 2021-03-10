<?php

public function addWattageRow($produced, $consumed, $l1, $l2, $l3)
{
	$passwordHash = md5($password);		
	/*$query = "INSERT INTO `registered_users` (`user_name`, `display_name`, `password`, `email`) VALUES (?, ?, ?, ?)";*/
	$query = "INSERT INTO `wattage` (`DT`, `Produced`, `Consumed`, `L1`, `L2`, `L3`) VALUES (CURRENT_TIME(), ?, ?, ?, ?, ?) ";
	$paramType = "iiiii";
	$paramArray = array($produced, $consumed, $l1, $l2, $l3);
	$id = $this->ds->insert($query, $paramType, $paramArray);
	printf("%d Row inserted:", $id );
	return $id;
}
	
if(isset($_GET['Prod']))	$Prod = $_GET['Prod'];
if(isset($_GET['Cons']))	$Cons = $_GET['Cons'];
if(isset($_GET['L1']))		$L1 = $_GET['L1'];
if(isset($_GET['L2']))		$L2 = $_GET['L2'];
if(isset($_GET['L3']))		$L3 = $_GET['L3'];


//INSERT INTO `wattage` (`DT`, `Produced`, `Consumed`, `L1`, `L2`, `L3`) VALUES (CURRENT_TIME(), '1', '2', '3', '4', '5') 

?> 

<html>
<head>
<title>User Login</title>
<link href="./view/css/style.css" rel="stylesheet" type="text/css" />
</head>
<body>
    <div>
        <div class="dashboard">
            <div class="member-dashboard">
			myvar: <?php echo $Prod; ?> 
			myvar: <?php echo $Cons; ?> 
			myvar: <?php echo $L1; ?> 
			myvar: <?php echo $L2; ?> 
			myvar: <?php echo $L3; ?> 			
            </div>
        </div>
    </div>
</body>
</html>