<?php
session_start();
if(!empty($_SESSION["userId"])) 
{
	if(!empty($_POST["NewPage"]))		// richiesta nuova pagina
	{
		$newP = $_POST["NewPage"];
		require_once './view/'.$newP.'.php';
	}
	else								// richiesta dashboard
	{
		require_once './view/dashboard.php';
	}
}
else
{
    require_once './login-form.php';
}
?>