<?php
	$con = mysql_connect("localhost","root","");

	if (!$con) {
	  die('Could not connect: ' . mysql_error());
	}

	mysql_select_db("smartsolar", $con);
	$result = mysql_query("SELECT * FROM batteries WHERE batteryID = '".$_GET['batID']."'");
	
	$r = mysql_fetch_array($result);
	
	if(mysql_num_rows($result) !=  0){
		
		$final = array();
		
		$row[0] = $r['location'];
		array_push($final,$row);
		
		$row[0] = $r['number'];
		array_push($final,$row);
	
		$row[0] = $r['type'];
		array_push($final,$row);
			
		$row[0] = date_format(date_create($r['timeCharged']),'d-m-Y H:i:s');
		array_push($final,$row);
		
		$row[0] = number_format($r['timeTakenToCharge']/60,2);
		array_push($final,$row);
		
		$row[0] = number_format($r['stateOfHealth']);
		array_push($final,$row);
	
		$row[0] = number_format($r['availableCapacity']);
		array_push($final,$row);
			
		$row[0] = $r['disabled'];
		array_push($final,$row);
	}else{
		$final = array();
		$final[0] = "NULL";	
	}	
	echo json_encode($final, JSON_NUMERIC_CHECK);
?>
