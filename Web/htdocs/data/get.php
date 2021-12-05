<?php
//namespace Phppot;
use \Phppot\DataQuery;

require_once "../class/DataQuery.php";

echo date("H:i:s");

$inizio = round(microtime(), 3);
$Timeout= 10;

//********************************************************************************
if(isset($_GET['Timeout']))	$Timeout = $_GET['Timeout']; 	

sleep($Timeout);
sleep($Timeout);
sleep($Timeout);

$fine = round(microtime(), 3);
$secondi = $fine - $inizio;

echo "- Ok timeout:". $Timeout  . " tempo:" . $secondi . " -" ;
echo date("H:i:s");
//********************************************************************************
?> 

