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
	
<<<<<<< HEAD
	$dataquery = new DataQuery();
	$result = $dataquery->Wattage_dayh(4);

	$sz = count($result);
=======
	<ul class="list-group">
		<li>
		<p>Produzione Oraria</p>
		
		<?php
		use \Phppot\DataQuery;
		use \Phppot\PrintObjects;
>>>>>>> 62ff707c3d9c6fbe04d8b70f3e9bc9b535b9e884

		require_once "./class/DataQuery.php";
		require_once "./class/PrintObjects.php";
		
		$dataquery = new DataQuery();
		$result = $dataquery->Wattage_dayh();

		$sz = count($result);
		
<<<<<<< HEAD
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
	$result = $dataquery->Wattage_all();

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
		echo "<td>" . $row['Dt'] . "</td>";
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
=======
		echo PrintObjects::BuildTable( $result, "class='table table-striped table-sm w-auto'");
		
		//print_r($result);
		?>
		
		</li>
	</ul>
>>>>>>> 62ff707c3d9c6fbe04d8b70f3e9bc9b535b9e884
	
</body>
</html>
	
	
 <?php require_once (__DIR__ . "/_tail.php"); ?>
