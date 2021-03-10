<?php
session_start();
if(!empty($_SESSION["userId"])) 
{
	if(!empty($_POST["NewPage"]))		// richiesta nuova pagina
	{
		$newP = $_POST["NewPage"];
		if ($newP == "Wattage")
			require_once './view/'.$newP.'.php';
		else
			require_once './view/dashboard.php';
	}
	else								// richiesta dashboard
	{
		echo "Dashboard";
		require_once './view/dashboard.php';
	}
}
else
{
    require_once './login-form.php';
}
?>