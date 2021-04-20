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
		
		<div class="container">	
		    <div class="row">
			<div class="col-12">
			    <div class="card">
				<div class="card-body">
				    <canvas id="chLine_h"></canvas>
				</div>
			    </div>
			</div>
		     </div>     
		</div>
		
		<?php	
		
		$dataquery = new DataQuery();
		$result = $dataquery->Wattage_dayh(4);
		$oldstrip = "";
			$hour = 0;

		//loop through the returned data
		foreach( $result as $key=>$row)
		 {
			$Item_Produced_h.= $row['Produced'] .',';
			$Item_Consumed_h.= $row['Consumed'] .',';
			$Item_SelfC_h.= $row['SelfConsumed'] .',';
			$Item_NetC_h.= $row['NetConsumed'] .',';
			
			$date = $row['Day'];
			$createDate = new DateTime($date);
			$strip = $createDate->format('d-m-Y');
			if ($strip!=$oldstrip)
				{
				$Item_day_h .= '"'. $strip .'",';
				$hour=0;
				}
			else
				{
				$Item_day_h .= '"h'. $hour .'",';
				$hour+=4;
				$oldstrip=$strip;
				}
		}
	 
		// removing the final comma with rtrim
		$Item_day_h = rtrim($Item_day_h,",");
		$Item_Produced_h = rtrim($Item_Produced_h,",");
		$Item_Consumed_h = rtrim($Item_Consumed_h,",");
		$Item_SelfC_h = rtrim($Item_SelfC_h,",");
		$Item_NetC_h = rtrim($Item_NetC_h,",");
		//End SQL
		
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
				    <canvas id="chLine_d"></canvas>
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
			$Item_Produced_d.= $row['Produced'] .',';
			$Item_Consumed_d.= $row['Consumed'] .',';
			$Item_SelfC_d.= $row['SelfConsumed'] .',';
			$Item_NetC_d.= $row['NetConsumed'] .',';
			
			$date = $row['Day'];
			$createDate = new DateTime($date);
			$strip = $createDate->format('d-m-Y');
			$Item_day_d .= '"'. $strip .'",';
		}
	 
		// removing the final comma with rtrim
		$Item_day_d = rtrim($Item_day_d ,",");
		$Item_Produced_d = rtrim($Item_Produced_d ,",");
		$Item_Consumed_d = rtrim($Item_Consumed_d ,",");
		$Item_SelfC_d = rtrim($Item_SelfC_d ,",");
		$Item_NetC_d = rtrim($Item_NetC_d ,",");
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

<!-------------------------------------------------------------------------------------------------------------->
/* large line chart */
var chLine_h = document.getElementById("chLine_h");
var chLine_d = document.getElementById("chLine_d");

var chartData_h = 
{
  labels: [<?php echo $Item_day_h; ?>],
  datasets: [{
    data: [<?php echo $Item_Produced_h; ?>],
    backgroundColor: 'lightgreen',
    borderColor: 'green',
    borderWidth: 4,
    pointBackgroundColor: 'green',
  },
  {
    data: [<?php echo $Item_SelfC_h; ?>],
    backgroundColor: 'transparent',
    borderColor: 'yellow',
    borderWidth: 4,
  },
  {
    data: [<?php echo $Item_NetC_h; ?>],
    backgroundColor: 'transparent',
    borderColor: 'orange',
    borderWidth: 4,
  },
  {
    data: [<?php echo $Item_Consumed_h; ?>],
    backgroundColor: 'coral',
    borderColor: 'red',
    borderWidth: 4,
    pointBackgroundColor: 'red'
  }]
};

var chartData_d = 
{
  labels: [<?php echo $Item_day_d; ?>],
  datasets: [{
    data: [<?php echo $Item_Produced_d; ?>],
    backgroundColor: 'lightgreen',
    borderColor: 'green',
    borderWidth: 4,
    pointBackgroundColor: 'green',
  },
  {
    data: [<?php echo $Item_SelfC_d; ?>],
    backgroundColor: 'transparent',
    borderColor: 'yellow',
    borderWidth: 4,
  },
  {
    data: [<?php echo $Item_NetC_d; ?>],
    backgroundColor: 'transparent',
    borderColor: 'orange',
    borderWidth: 4,
  },
  {
    data: [<?php echo $Item_Consumed_d; ?>],
    backgroundColor: 'coral',
    borderColor: 'red',
    borderWidth: 4,
    pointBackgroundColor: 'red'
  }]
};

if (chLine_h) {
  new Chart(chLine_h, {
  type: 'line',
  data: chartData_h,
  options: {
    scales: {
      yAxes: [{
        ticks: {
          beginAtZero: true
        }
      }]
    },
    legend: {
      display: false
    }
  }
  });
}

if (chLine_d) {
  new Chart(chLine_d, {
  type: 'line',
  data: chartData_d,
  options: {
    scales: {
      yAxes: [{
        ticks: {
          beginAtZero: true
        }
      }]
    },
    legend: {
      display: false
    }
  }
  });
}

<!-------------------------------------------------------------------------------------------------------------->
</script>	
	
 <?php require_once (__DIR__ . "/_tail.php"); ?>
