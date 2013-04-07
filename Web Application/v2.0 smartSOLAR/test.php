<?php
	$con = mysql_connect("localhost","root","");

	if (!$con) {
	  die('Could not connect: ' . mysql_error());
	}

	mysql_select_db("smartsolar", $con);
	$result = mysql_query("SELECT * FROM environment WHERE location='Kudang'");
	$irr = array();
	$temp = array();
	while($r = mysql_fetch_array($result)) {
		$date = date_create($r['datetime']);
		$row[0] =  date_timestamp_get($date) *1000;
		$row[1] = $r['irradiance'];
		array_push($irr ,$row);
		
		$date = date_create($r['datetime']);
		$row[0] =  date_timestamp_get($date)*1000;
		$row[1] = $r['temperature'];
		array_push($temp ,$row);
	}
	
	$final = array();
	
	array_push($final,$irr);
	array_push($final,$temp);
	
	echo json_encode($final , JSON_NUMERIC_CHECK);
	mysql_close($con);
?>