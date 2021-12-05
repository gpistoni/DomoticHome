<?php require_once (__DIR__ . "/_head.php"); ?>
if (
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
				<div id="Luci" class="d-flex justify-content-between flex-wrap flex-md-nowrap align-items-center pt-3 pb-2 mb-3 border-bottom">
					<h1 class="h2">Luci</h1>
					<div class="btn-toolbar mb-2 mb-md-0">
						<div class="btn-group me-2">
							<button type="button" class="btn btn-sm btn-outline-secondary">Share</button>
							<button type="button" class="btn btn-sm btn-outline-secondary">Export</button>
						</div>
					</div>
				</div>
				<div class="btn-group-vertical">
					<button type="submit" class="btn btn-outline-primary btn-lg disabled" name="NewPage" value="luci">luciAngolo</button>
					<div class="btn-group border-bottom" role="group">
						<button type="submit" class="btn btn-success" name="NewPage" value="luci">ON</button>
						<button type="submit" class="btn btn-secondary" name="NewPage" value="luci">OFF</button>
						<span></span>
						<button type="submit" class="btn btn-outline-primary" name="NewPage" value="luci">ForceOn</button>
						<button type="submit" class="btn btn-outline-primary" name="NewPage" value="luci">ForceOff</button>						
					</div>
					<br>
					<button type="submit" class="btn btn-outline-primary btn-lg disabled" name="NewPage" value="luci">luciLato</button>
					<div class="btn-group" role="group">
						<button type="submit" class="btn btn-outline-primary" name="NewPage" value="luci">ON</button>
						<button type="submit" class="btn btn-outline-primary" name="NewPage" value="luci">OFF</button>
						<span></span>
						<button type="submit" class="btn btn-outline-primary" name="NewPage" value="luci">ForceOn</button>
						<button type="submit" class="btn btn-outline-primary" name="NewPage" value="luci">ForceOff</button>						
					</div>
				</div>
			</div>
		</main>
	</div>
	<?php require_once (__DIR__ . "/_tail.php"); ?>
