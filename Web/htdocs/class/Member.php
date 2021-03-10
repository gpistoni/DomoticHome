<?php
namespace Phppot;
use \Phppot\DataSource;

class Member
{
    private $dbConn;
    private $ds;

    function __construct()
    {
        require_once "DataSource.php";
        $this->ds = new DataSource();
    }

    function getMemberById($memberId)
    {
        $query = "select * FROM registered_users WHERE id = ?";
        $paramType = "i";
        $paramArray = array($memberId);
        $memberResult = $this->ds->select($query, $paramType, $paramArray);
        
        return $memberResult;
    }
    
    public function processLogin($username, $password) {
        $passwordHash = md5($password);
        $query = "select * FROM registered_users WHERE user_name = ? AND password = ?";
        $paramType = "ss";
        $paramArray = array($username, $passwordHash);
        $memberResult = $this->ds->select($query, $paramType, $paramArray);
        if(!empty($memberResult)) {
            $_SESSION["userId"] = $memberResult[0]["id"];
            return true;
        }
    }
	
	public function addUser($username, $password, $email)
	{
        $passwordHash = md5($password);		
		$query = "INSERT INTO `registered_users` (`user_name`, `display_name`, `password`, `email`) VALUES (?, ?, ?, ?)";
        $paramType = "ssss";
        $paramArray = array( $username, $username, $passwordHash, $email);
		$id = $this->ds->insert($query, $paramType, $paramArray);
		printf("%d Row inserted:", $id );
		return $id;
    }
	
	
	public function addWattageRow($produced, $consumed, $l1, $l2, $l3)
	{
        $passwordHash = md5($password);		
		/*$query = "INSERT INTO `registered_users` (`user_name`, `display_name`, `password`, `email`) VALUES (?, ?, ?, ?)";*/
		$query = "INSERT INTO `wattage` (`DT`, `Produced`, `Consumed`, `L1`, `L2`, `L3`) VALUES (CURRENT_TIME(), ?, ?, ?, ?, ?) ";
        $paramType = "iiiii";
        $paramArray = array($produced, $consumed, $l1, $l2, $l3);
		$id = $this->ds->insert($query, $paramType, $paramArray);
		printf("%d Row inserted:", $id );
		return $id;
    }
}