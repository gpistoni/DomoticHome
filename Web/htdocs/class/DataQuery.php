<?php
namespace Phppot;
use \Phppot\DataSource;

// class contains the query used to add rows and print tables

class DataQuery
{
    private $dbConn;
    private $ds;

    function __construct()
    {
        require_once "DataSource.php";
        $this->ds = new DataSource();
    }
/*
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
	*/	
	
	public function addWattageTable()
	{	
		$query =  "CREATE TABLE IF NOT EXIST `Wattage` (";
		$query .= "`id` int PRIMARY KEY  AUTO_INCREMENT,";
		$query .= "`Dt` datetime NOT NULL,";
		$query .= "`Produced` int,";
		$query .= "`Consumed` int,";
		$query .= "`SelfConsumed` int,";
		$query .= "`Surplus` int, ";
		$query .= "`L1` int, ";
		$query .= "`L2` int, ";
		$query .= "`L3` int );";
		
		$id = $this->ds->execute($query);
		return $id;
	}
	
	public function addWattageRow($produced, $consumed, $selfConsumed, $surplus, $l1, $l2, $l3)
	{	
		$query = "INSERT INTO `Wattage` (`Dt`, `Produced`, `Consumed`, `SelfConsumed`, `Surplus`, `L1`, `L2`, `L3`)";
		$query .= "VALUES (CURRENT_TIME(), ?, ?, ?, ?, ?, ?, ?) ";
        $paramType = "iiiiiii";
        $paramArray = array($produced, $consumed, $selfConsumed, $surplus, $l1, $l2, $l3);
		$id = $this->ds->insert($query, $paramType, $paramArray);
		return $id;
    }
	
	public function Wattage_day() 
	{
        $query = "select * FROM Wattage";
        $Result = $this->ds->select($query);
		return $Result;
    	}
	
	public function Wattage_dayh() 
	{
        $query = "select * FROM Wattage";
        $Result = $this->ds->select($query);
		return $Result;
    }
	
}
