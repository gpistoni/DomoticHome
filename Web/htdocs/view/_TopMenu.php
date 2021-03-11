<div class="dashboard">
	<div class="dashboard">
		Welcome <b>	<?php echo $displayName; ?></b>, Click to <a href="./logout.php" class="logout-button">Logout </a>
	</div>
	<div class="dashboard">
		<?php if(!empty($displayPage)) { echo $displayPage; } ?>
	</div>
	<div class="dashboard">
		<form name="TopMenuForm" action="./index.php" method="POST">
			<input type="submit" name="NewPage" value="dashboard" />
			<input type="submit" name="NewPage" value="wattage" />
			<input type="submit" name="NewPage" value="status" />
		</form>
	</div>
 </div>
