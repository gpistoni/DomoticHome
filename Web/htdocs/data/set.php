<?php
//namespace Phppot;
use \Phppot\DataQuery;

require_once "../class/DataQuery.php";

$NewRows=0;

function GetVar($varname)
{
	if(isset($_GET[$varname]))	return $_GET[$varname]; 	
	return 0;
}


$Prod = GetVar('Prod');
$Cons = GetVar('Cons');
$SelfCons = GetVar('SelfCons');
$Surplus = GetVar('Surplus');
$L1 = GetVar('L1');
$L2 = GetVar('L2');
$L3 = GetVar('L3');

$dataquery = new DataQuery();

$newID=0;

if ($Cons>0)
{
	$newID .= $dataquery->addWattageRow($Prod, $Cons, $SelfCons, $Surplus, $L1, $L2, $L3);
}

echo $newID;

//********************************************************************************
?> 

