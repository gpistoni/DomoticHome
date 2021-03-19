 <?php require_once (__DIR__ . "/_head.php"); ?>


 <?php
use \Phppot\DataQuery;
use \Phppot\PrintObjects;

require_once "./class/DataQuery.php";
require_once "./class/PrintObjects.php";

$sqltext = $_REQUEST['sqltext'];

function str_starts_with ( $haystack, $needle ) 
{
	return strpos( $haystack , $needle ) === 0;
}

if (str_starts_with($sqltext, 'SELECT') or str_starts_with($sqltext, 'select')   ) 
{
	$dataquery = new DataQuery();
	$resultSQL = $dataquery->select($sqltext);	
}
?>

<body>
<!-- Barra superiore -->
<?php require_once (__DIR__ . "/_topbar.php"); ?>
<div class="container-fluid">
  <div class="row">
	<!-- Barra sinistra con menu -->
	<?php require_once (__DIR__ . "/_leftbar.php"); ?>
	<!-------------------------------------------------------------------------------------------------------------->
	<!-- CENTRALE -->
    <main class="col-md-9 ms-sm-auto col-lg-10 px-md-4">
	<!-------------------------------------------------------------------------------------------------------------->
		<div id="Dashboard" class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pt-3 pb-2 mb-3 border-bottom">
			<h1 class="h2">Database</h1>
			<div class="btn-toolbar mb-2 mb-md-0">		
			</div>
		</div>  	
		
	<form class="nav-link" action="" method="POST">
  		<input  type="text" name="sqltext">
		<input  type="submit" name="NewPage" value="database">
	</form>
	
	Result:
	<?php
	//print_r($resultSQL);
	echo PrintObjects::BuildTable($resultSQL, "")
	?>
	
	</main>
  </div>
</div>

 <?php require_once (__DIR__ . "/_tail.php"); ?>

