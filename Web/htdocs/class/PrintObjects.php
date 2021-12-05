<?php
namespace Phppot;

// class contains the query used to add rows and print tables
class PrintObjects
{
	public static function BuildTable($array, $tableinfo)
	{
		// start table
		$html = '<table '. $tableinfo . '>';
		// header row
		$html .= '<tr>';
		foreach($array[0] as $key=>$value){
				$html .= '<th>' . htmlspecialchars($key) . '</th>';
			}
		$html .= '</tr>';

		// data rows
		foreach( $array as $key=>$value){
			$html .= '<tr>';
			$firstCol = true;
			foreach($value as $key2=>$value2){
				if ($firstCol)
				{
					$html .= '<td>' . get_class($a). htmlspecialchars($value2) . '</td>';
					$firstCol = false;
					}
				else
					$html .= '<td>' . get_class($a) . htmlspecialchars(intval($value2)) . '</td>';					
			}
			$html .= '</tr>';
		}

		// finish table and return it
		$html .= '</table>';
		return $html;
   	}
}

