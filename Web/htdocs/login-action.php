<?php
namespace Phppot;

use \Phppot\Member;
if (!empty($_POST["login"])) 
{
    session_start();
    $username = filter_var($_POST["user_name"], FILTER_SANITIZE_STRING);
    $password = filter_var($_POST["password"], FILTER_SANITIZE_STRING);
    require_once (__DIR__ . "./class/Member.php");
    
    $member = new Member();
    $isLoggedIn = $member->processLogin($username, $password);
    if (! $isLoggedIn) 
	{
        $_SESSION["errorMessage"] = "Invalid Credentials";
    }
    header("Location: ./index.php");
    exit();
}

if (!empty($_POST["register"])) 
{
    session_start();
    $username = filter_var($_POST["user_name"], FILTER_SANITIZE_STRING);
    $password = filter_var($_POST["password"], FILTER_SANITIZE_STRING);
    require_once (__DIR__ . "./class/Member.php");
    
    $member = new Member();
    $isAddUser = $member->addUser($username, $password, "mail@io.com" );
    if (!$isAddUser) 
	{
        $_SESSION["errorMessage"] = "Invalid Add User";
    }
    header("Location: ./index.php");
    exit();
}