<?php
namespace Phppot;
use \Phppot\Member;

if (! empty($_SESSION["userId"])) 
{
    require_once (__DIR__ . "/../class/Member.php");
    $member = new Member();
    $memberResult = $member->getMemberById($_SESSION["userId"]);
    if(!empty($memberResult[0]["display_name"])) {
        $displayName = ucwords($memberResult[0]["display_name"]);
    } else {
        $displayName = $memberResult[0]["user_name"];
    }
}
?>

<html lang="en">
  <head>
    <meta charset="utf-8">
    <meta name="viewport" content="width=device-width, initial-scale=1">
	<title>DomoticHome</title>

    <!-- Bootstrap core CSS -->
	<link href="./view/css/bootstrap.min.css" rel="stylesheet">
	<meta name="theme-color" content="#7952b3">

    <style>
      .bd-placeholder-img {
        font-size: 1.125rem;
        text-anchor: middle;
        -webkit-user-select: none;
        -moz-user-select: none;
        user-select: none;
      }

      @media (min-width: 768px) {
        .bd-placeholder-img-lg {
          font-size: 3.5rem;
        }
      }
    </style>
    
    <!-- Custom styles for this template -->
	<link href="./view/css/dashboard.css" rel="stylesheet" type="text/css" />
	
  </head>