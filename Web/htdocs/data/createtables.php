<?php
//namespace Phppot;
use \Phppot\DataQuery;

require_once "../class/DataQuery.php";

$dataquery = new DataQuery();

$result = $dataquery->WattageTable();
echo $result;


//********************************************************************************
?> 

