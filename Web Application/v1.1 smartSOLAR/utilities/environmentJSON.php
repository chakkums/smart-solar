<?php
	$con = mysql_connect("localhost","root","");

	if (!$con) {
	  die('Could not connect: ' . mysql_error());
	}

	mysql_select_db("smartsolar", $con);
	$result = mysql_query("SELECT datetime FROM environment WHERE location='".$_GET["locParam"]."' AND DATE(datetime) = '".$_GET["dateParam"]."'");
	$rows = array();
	$rows['name'] = 'datetime';
	while($r = mysql_fetch_array($result)) {
		$rows['data'][] = date_format(date_create($r['datetime']),'ga');
	}
	
	$result = mysql_query("SELECT irradiance FROM environment WHERE location='".$_GET["locParam"]."' AND DATE(datetime) = '".$_GET["dateParam"]."'");
	$rows1 = array();
	$rows1['name'] = 'Irradiance';
	while($rr = mysql_fetch_array($result)) {
		$rows1['data'][] = $rr['irradiance'];
	}
	
	$result = mysql_query("SELECT temperature FROM environment WHERE location='".$_GET["locParam"]."' AND DATE(datetime) = '".$_GET["dateParam"]."'");
	$rows2 = array();
	$rows2['name'] = 'Temperature';
	while($rrr = mysql_fetch_array($result)) {
		$rows2['data'][] = $rrr['temperature'];
	}

	

	$result = array();
	array_push($result,$rows);
	array_push($result,$rows1);
	array_push($result,$rows2);
	print json_encode($result, JSON_NUMERIC_CHECK);
	mysql_close($con);
?>