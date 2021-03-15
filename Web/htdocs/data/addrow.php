<?php
//namespace Phppot;
use \Phppot\DataQuery;

require_once "../class/DataQuery.php";

$NewRows=0;

//********************************************************************************
// raccolgo variabili GET
if(isset($_GET['Prod']))	$Prod = $_GET['Prod']; 	else $Prod =0;
if(isset($_GET['Cons']))	$Cons = $_GET['Cons']; 	else $Cons =0;
if(isset($_GET['L1']))		$L1 = $_GET['L1']; 	else $L1 =0;
if(isset($_GET['L2']))		$L2 = $_GET['L2']; 	else $L2 =0;
if(isset($_GET['L3']))		$L3 = $_GET['L3']; 	else $L3 =0;

if ($Cons!=0)
{
 	$dataquery = new DataQuery();
	$newID = $dataquery->addWattageRow($Prod, $Cons, $L1, $L2, $L3);
	$NewRows++;
}

//********************************************************************************
?> 

echo $NewRows;

