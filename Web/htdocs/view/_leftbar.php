<?php 

function active($pagecheck) 
{
	global $newPage; 
	if ($newPage==$pagecheck) echo "active";
}

function hidden($pagecheck) 
{
	global $newPage; 
	if ($newPage!=$pagecheck) echo "d-none";
}

?>

    <nav id="sidebarMenu" class="col-md-3 col-lg-2 d-md-block bg-light sidebar collapse">
      <div class="position-sticky pt-3">
        <ul class="nav flex-column">
			<li class="nav-item">
				<form class="nav-link <?php active("dashboard"); ?>" action="" method="POST">
				<button type="submit" class="btn btn-flat btn-lg" name="NewPage" value="dashboard">
					<span data-feather="home"></span>
					Dashboard
				</button>	
				</form>			
			</li>
			<li class="nav-item">
				<form class="nav-link <?php active("energia"); ?>" action="" method="POST">
				<button type="submit" class="btn btn-flat btn-lg" name="NewPage" value="energia">
					<span data-feather="file"></span>
					Energia
				</button>
				</form>	
				<ul class="nav flex-column mb-2 <?php hidden("energia"); ?> ">
				  <li class="nav-item">
				    <a class="nav-link   ?>" href="#Oraria">
				      <span data-feather="file-text"></span>
				      Oraria
				    </a>
				  </li>
				  <li class="nav-item">
				    <a class="nav-link" href="#Giornaliera">
				      <span data-feather="file-text"></span>
				      Giornaliera
				    </a>
				  </li>
				   <li class="nav-item">
				    <a class="nav-link" href="#Mensile">
				      <span data-feather="file-text"></span>
				      Mensile
				    </a>
				  </li>
				</ul>
			</li>
			<li class="nav-item">
				<form class="nav-link <?php active("luci"); ?>" action="" method="POST">
				<button type="submit" class="btn btn-flat btn-lg" name="NewPage" value="luci" >
					<span data-feather="shopping-cart"></span>
				Luci
				</button>
				</form>
            </li>
			<li class="nav-item">
				<form class="nav-link <?php active("status"); ?>" action="" method="POST">
				<button type="submit" class="btn btn-flat btn-lg" name="NewPage" value="status" >
					<span data-feather="shopping-cart"></span>
				Status
				</button>
				</form>
            </li>
			<li class="nav-item">
				<form class="nav-link <?php active("database"); ?>" action="" method="POST">
				<button type="submit" class="btn btn-flat btn-lg" name="NewPage" value="database" >
					<span data-feather="database"></span>
				Database
				</button>
				</form>
            </li>
            <li class="nav-item">
			    <span data-feather="bar-chart-2"></span>
     		</li>
			<li class="nav-item">				
				<span data-feather="layers"></span>		
			</li>	
        </ul>

        <h6 class="sidebar-heading d-flex justify-content-between align-items-center px-3 mt-4 mb-1 text-muted">
          <span>Saved reports</span>
          <a class="link-secondary" href="#" aria-label="Add a new report">
            <span data-feather="plus-circle"></span>
          </a>
        </h6>
        <ul class="nav flex-column mb-2">
          <li class="nav-item">
            <a class="nav-link" href="#">
              <span data-feather="file-text"></span>
              Current month
            </a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="#">
              <span data-feather="file-text"></span>
              Last quarter
            </a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="#">
              <span data-feather="file-text"></span>
              Social engagement
            </a>
          </li>
          <li class="nav-item">
            <a class="nav-link" href="#">
              <span data-feather="file-text"></span>
              Year-end sale
            </a>
          </li>
        </ul>
      </div>
    </nav>
