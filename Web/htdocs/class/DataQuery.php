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
	
<<<<<<< HEAD
public function addWattageRow($produced, $consumed, $l1, $l2, $l3)
{

	$query = "INSERT INTO Wattage (Dt, Produced, Consumed, L1, L2, L3) VALUES (CURRENT_TIME(), ?, ?, ?, ?, ?) ";
	$paramType = "iiiii";
	$paramArray = array($produced, $consumed, $l1, $l2, $l3);
	$id = $this->ds->insert($query, $paramType, $paramArray);
	//DEBUG// printf("\n ID inserted: %d", $id );
	return $id;
}

public function Wattage_remove() 
{
	$query =  "DELETE FROM Wattage";
	$query .= " WHERE Dt < ADDDATE( NOW(), INTERVAL -360 DAY)";
	
	$Result = $this->ds->execute($query);
	return $Result;
}

public function Wattage_all() 
{
	$query = "SELECT * FROM Wattage";
	$Result = $this->ds->select($query);
	return $Result;
}

public function Wattage_day() 
{
	$this->Wattage_remove();
=======
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
>>>>>>> 62ff707c3d9c6fbe04d8b70f3e9bc9b535b9e884
	
	$query = "SELECT CAST(`Dt` as DATE) AS Day, ";
	$query .= "AVG(`Produced`) AS Produced, ";
	$query .= "AVG(`Consumed`) AS Consumed, ";
	$query .= "AVG(`L1`) AS L1, ";
	$query .= "AVG(`L2`) AS L2, "; 
	$query .= "AVG(`L3`) AS L3 "; 
	$query .= "FROM `Wattage` ";
	$query .= "WHERE 1 ";
	$query .= "GROUP BY CAST(`Dt` as DATE) ";

	$Result = $this->ds->select($query);
	return $Result;
}

public function Wattage_dayh($hours) 
{
	$query = "SELECT CAST(`Dt` as DATETIME) AS Day, ";
	$query .= "AVG(`Produced`) AS Produced, ";
	$query .= "AVG(`Consumed`) AS Consumed, ";
	$query .= "AVG(`L1`) AS L1, ";
	$query .= "AVG(`L2`) AS L2, "; 
	$query .= "AVG(`L3`) AS L3 "; 
	$query .= "FROM `Wattage` ";
	$query .= "WHERE 1 ";
	$query .= "GROUP BY FLOOR( HOUR(`Dt`) / 4 ), DAY(`Dt`); "; 
	
	$Result = $this->ds->select($query);
	return $Result;
}
	
}
