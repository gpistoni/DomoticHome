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

	
<?php

use \Phppot\DataQuery;

require_once "./class/DataQuery.php";

$dataquery = new DataQuery();
$result = $dataquery->Wattage_dayh();

$sz = count($result);

echo "<table class='table table-striped table-sm'>";
echo "<thead><tr>";
echo "	  <th>Day</th>";
echo "	  <th>Produced</th>";
echo "	  <th>Consumed</th>";
echo "	  <th>L1</th>";
echo "	  <th>L2</th>";
echo "	  <th>L3</th>";
echo "	</tr>";
echo "</thead>";

for($i=0; $i<$sz; $i++)
{
	$row = $result[$i];
	
	echo "<tr>";
	echo "<td>" . $row['Dt'] . "</td>";
	echo "<td>" . $row['Produced'] . "</td>";
	echo "<td>" . $row['Consumed'] . "</td>";
	echo "<td>" . $row['L1'] . "</td>";
	echo "<td>" . $row['L2'] . "</td>";
	echo "<td>" . $row['L3'] . "</td>";
	echo "</tr>";
}
echo "</table>";
		
?>
