<?php
//namespace Phppot;
use \Phppot\DataQuery;

require_once "../class/DataQuery.php";
  
// raccolgo variabili GET
if(isset($_GET['Prod']))	$Prod = $_GET['Prod']; 	else $Prod =0;
if(isset($_GET['Cons']))	$Cons = $_GET['Cons']; 	else $Cons =0;
if(isset($_GET['L1']))		$L1 = $_GET['L1']; 		else $L1 =0;
if(isset($_GET['L2']))		$L2 = $_GET['L2']; 		else $L2 =0;
if(isset($_GET['L3']))		$L3 = $_GET['L3']; 		else $L3 =0;

 $dataquery = new DataQuery();
 $dataquery->addWattageRow($Prod, $Cons, $L1, $L2, $L3);

//INSERT INTO `wattage` (`DT`, `Produced`, `Consumed`, `L1`, `L2`, `L3`) VALUES (CURRENT_TIME(), '1', '2', '3', '4', '5') 

?> 

<?php if ($Cons==0) {?> 
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
<?php }?>