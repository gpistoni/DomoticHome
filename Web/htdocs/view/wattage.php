<?php
namespace Phppot;
use \Phppot\Member;

if (! empty($_SESSION["userId"])) 
{
    require_once __DIR__ . './../class/Member.php';
    $member = new Member();
    $memberResult = $member->getMemberById($_SESSION["userId"]);
    if(!empty($memberResult[0]["display_name"])) {
        $displayName = ucwords($memberResult[0]["display_name"]);
    } else {
        $displayName = $memberResult[0]["user_name"];
    }
}
?>

<html>
<head>
	<title>WATTAGE</title>
	<link href="./view/css/style.css" rel="stylesheet" type="text/css" />
</head>
<body>
	<?php 
	 $displayPage = "WATTAGE";
	  require_once (__DIR__ . "/_TopMenu.php");
	?>
	
	
	<?php
	use \Phppot\DataQuery;

	require_once "./class/DataQuery.php";
	
	$dataquery = new DataQuery();
	$result = $dataquery->Wattage_day();

	$sz = count($result);

	echo "<table border='1'>
	<tr>
	<th>Day</th>
	<th>Produced</th>
	<th>Consumed</th>
	<th>L1</th>
	<th>L2</th>
	<th>L3</th>
	</tr>";

	for($i=0; $i<$sz; $i++)
	{
		$row = $result[$i];
		
		echo "<tr>";
		echo "<td>" . $row['Day'] . "</td>";
		echo "<td>" . $row['Produced'] . "</td>";
		echo "<td>" . $row['Consumed'] . "</td>";
		echo "<td>" . $row['L1'] . "</td>";
		echo "<td>" . $row['L2'] . "</td>";
		echo "<td>" . $row['L3'] . "</td>";
		echo "</tr>";
	}
	echo "</table>";
	
	//////////////////////////////////////////////////////////
	$result = $dataquery->Wattage_dayh("4");

	$sz = count($result);

	echo "<table border='1'>
	<tr>
	<th>Day</th>
	<th>Produced</th>
	<th>Consumed</th>
	<th>L1</th>
	<th>L2</th>
	<th>L3</th>
	</tr>";

	for($i=0; $i<$sz; $i++)
	{
		$row = $result[$i];
		
		echo "<tr>";
		echo "<td>" . $row['Day'] . "</td>";
		echo "<td>" . $row['Produced'] . "</td>";
		echo "<td>" . $row['Consumed'] . "</td>";
		echo "<td>" . $row['L1'] . "</td>";
		echo "<td>" . $row['L2'] . "</td>";
		echo "<td>" . $row['L3'] . "</td>";
		echo "</tr>";
	}
	echo "</table>";
	
	//echo "</br>";
	//DEBUG//
	//for($i=0; $i<$sz; $i++)
	//{
	//	$row = $result[$i];
	//	print_r($row);
	//	}	
	?>
	
</body>
</html>
