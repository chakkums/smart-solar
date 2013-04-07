<?php
	$con = mysql_connect("localhost","root","");

	if (!$con) {
	  die('Could not connect: ' . mysql_error());
	}

	mysql_select_db("smartsolar", $con);
	$result = mysql_query("SELECT number,stateOfHealth FROM batteries WHERE location='".$_GET["locParam"]."' ORDER BY stateOfHealth LIMIT 10");
	$ID = array();
	$ID['name'] = 'Battery #';
	$SOH = array();
	$SOH['name'] = 'SOH';
	
	while($r = mysql_fetch_array($result)) {
		$ID['data'][] = $r['number'];
		$SOH['data'][] = number_format($r['stateOfHealth'],2);
		
	}	

	$final = array();
	
	array_push($final,$ID);
	array_push($final,$SOH);

	print json_encode($final, JSON_NUMERIC_CHECK);
	mysql_close($con);
?>