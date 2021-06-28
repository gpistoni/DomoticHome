<?php
//namespace Phppot;
use \Phppot\DataQuery;

require_once "../class/DataQuery.php";

$dataquery = new DataQuery();
$result = $dataquery->Wattage_day();

echo json_encode($result);		
?> 

