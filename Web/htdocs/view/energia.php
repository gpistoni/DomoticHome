 <?php 
use \Phppot\DataQuery;
use \Phppot\PrintObjects;

require_once "./class/DataQuery.php";
require_once "./class/PrintObjects.php";
?>
		
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
		<h1 class="h2">Energia</h1>
			<div class="btn-toolbar mb-2 mb-md-0">
			  <div class="btn-group me-2">
				<button type="button" class="btn btn-sm btn-outline-secondary">Share</button>
				<button type="button" class="btn btn-sm btn-outline-secondary">Export</button>
			  </div>
			</div>
	</div>

	<ul class="list-group">
		<li>
		<div id="Oraria" class="d-flex" >
		<p>Produzione Oraria</p></div>
		
		<?php	
		
		$dataquery = new DataQuery();
		$result = $dataquery->Wattage_dayh(4);

		$sz = count($result);
		
		echo PrintObjects::BuildTable( $result, "class='table table-striped table-sm w-auto'");
		
		//print_r($result);
		?>
		</li>
		
		<li>
		<div id="Giornaliera"><h2>Produzione Giornaliera</h2></div>	
		
		<div class="container">	
		    <div class="row">
			<div class="col-12">
			    <div class="card">
				<div class="card-body">
				    <canvas id="chLine"></canvas>
				</div>
			    </div>
			</div>
		     </div>     
		</div>
		
		<?php
	
		$dataquery = new DataQuery();
		$result = $dataquery->Wattage_day();
	
		//loop through the returned data
		foreach( $result as $key=>$row)
		 {
			$Item_Produced.= $row['Produced'] .',';
			$Item_Consumed.= $row['Consumed'] .',';
			
			$date = $row['Day'];
			$createDate = new DateTime($date);
			$strip = $createDate->format('d-m-Y');
			$Item_day .= '"'. $strip .'",';
		}
	 
		// removing the final comma with rtrim
		$Item_day = rtrim($Item_day,",");
		$Item_Produced = rtrim($Item_Produced,",");
		$Item_Consumed = rtrim($Item_Consumed,",");
		//End SQL		
		
		$sz = count($result);
		
		echo PrintObjects::BuildTable( $result, "class='table table-striped table-sm w-auto'");
		
		//print_r($result);
		?>		
		</li>
	</ul>
	
</body>
</html>

<script src="https://cdn.jsdelivr.net/npm/chart.js@2.9.4/dist/Chart.min.js" 
	integrity="sha384-zNy6FEbO50N+Cg5wap8IKA4M/ZnLJgzc6w2NqACZaK0u0FXfOWRRJOnQtpZun8ha" 
	crossorigin="anonymous"></script>
	
<script type="text/javascript">

// chart colors
var colors = ['#007bff','#28a745','#333333','#c3e6cb','#dc3545','#6c757d'];

/* large line chart */
var chLine = document.getElementById("chLine");

var chartData = 
{
  labels: [<?php echo $Item_day; ?>],
  datasets: [{
    data: [<?php echo $Item_Produced; ?>],
    backgroundColor: 'transparent',
    borderColor: 'green',
    borderWidth: 4,
    pointBackgroundColor: 'green',
  },
  {
    data: [<?php echo $Item_Consumed; ?>],
    backgroundColor: 'coral',
    borderColor: 'red',
    borderWidth: 4,
    pointBackgroundColor: 'red'
  }]
};

if (chLine) {
  new Chart(chLine, {
  type: 'line',
  data: chartData,
  options: {
    scales: {
      yAxes: [{
        ticks: {
          beginAtZero: false
        }
      }]
    },
    legend: {
      display: false
    }
  }
  });
}

</script>	
	
 <?php require_once (__DIR__ . "/_tail.php"); ?>
