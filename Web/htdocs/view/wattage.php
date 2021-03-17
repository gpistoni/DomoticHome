 <?php require_once (__DIR__ . "/_head.php"); ?>

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
	<!-- titolo -->
	<div id="Wattage" class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pt-3 pb-2 mb-3 border-bottom ">
			<h1 class="h2">Produzione</h1>
			<div class="btn-toolbar mb-2 mb-md-0">
			  <div class="btn-group me-2">
				<button type="button" class="btn btn-sm btn-outline-secondary">Share</button>
				<button type="button" class="btn btn-sm btn-outline-secondary">Export</button>
			  </div>
			</div>
	</div>
	
	<ul class="list-group">
		<li>
		<p>Produzione Oraria</p>
		
		<?php
		use \Phppot\DataQuery;
		use \Phppot\PrintObjects;

		require_once "./class/DataQuery.php";
		require_once "./class/PrintObjects.php";
		
		$dataquery = new DataQuery();
		$result = $dataquery->Wattage_dayh();

		$sz = count($result);
		
		echo PrintObjects::BuildTable( $result, "class='table table-striped table-sm w-auto'");
		
		//print_r($result);
		?>
		
		</li>
	</ul>
	
</body>
</html>
	
	
 <?php require_once (__DIR__ . "/_tail.php"); ?>
