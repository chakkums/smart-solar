<?php
	$con = mysql_connect("localhost","root","");

	if (!$con) {
	  die('Could not connect: ' . mysql_error());
	}
	
	date_default_timezone_set('UTC');


	mysql_select_db("smartsolar", $con);
	$result = mysql_query("SELECT * FROM loaddata WHERE batteryID='".$_GET['batteryID']."'");
	$charge = array();
	$load = array();
	while($r = mysql_fetch_array($result)) {
		$date = date_create($r['timeLoadOn']);
		$row[0] =  date_timestamp_get($date) *1000;
		$row[1] = $r['startChargeLevel'];
		array_push($charge ,$row);
		
		$date = date_create($r['timeLoadOff']);
		$row[0] =  date_timestamp_get($date)*1000;
		$row[1] = $r['endChargeLevel'];
		array_push($charge ,$row);
		
		$date = date_create($r['timeLoadOn']);
		$row[0] =  date_timestamp_get($date)*1000;
		$row[1] = $r['averageLoad'];
		array_push($load ,$row);
		
		$date = date_create($r['timeLoadOff']);
		$row[0] =  date_timestamp_get($date)*1000;
		$row[1] = $r['averageLoad'];
		array_push($load ,$row);

	}
	
	$final = array();
	
	array_push($final,$charge);
	array_push($final,$load);
	
	print json_encode($final , JSON_NUMERIC_CHECK);
	mysql_close($con);
?>