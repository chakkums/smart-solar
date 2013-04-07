<?php
	$con = mysql_connect("localhost","root","");

	if (!$con) {
	  die('Could not connect: ' . mysql_error());
	}

	mysql_select_db("smartsolar", $con);
	$result = mysql_query("SELECT stateOfHealth FROM batteries WHERE location='".$_GET["locParam"]."'");
	
	$overEighty = 0;
	$overSixty = 0;
	$overForty = 0;
	$overTwenty = 0;
	$overTen = 0;
	$belowOrTen = 0;
	
	$numberBatt = mysql_num_rows($result);
	
	while($r = mysql_fetch_array($result)) {
		$soh = $r['stateOfHealth']; 
		if($soh >= 80){
		
			$overEighty = $overEighty + ((1/$numberBatt)*100);
			
		}else if(($soh < 80) && ($soh >= 60)){

			$overSixty = $overSixty + ((1/$numberBatt)*100);
			
		}else if(($soh < 60) && ($soh >= 40)){
		
			$overForty = $overForty + ((1/$numberBatt)*100);
			
		}else if(($soh < 40) && ($soh >= 20)){
		
			$overTwenty = $overTwenty + ((1/$numberBatt)*100);
			
		}else if(($soh < 20) && ($soh >= 10)){
		
			$overTen = $overTen + ((1/$numberBatt)*100);
			
		}else if($soh < 10){
		
			$belowOrTen = $belowOrTen + ((1/$numberBatt)*100);
			
		}
	}
	$rows = array();
	$row[0] = "Over 80%";
	$row[1] = $overEighty;
	array_push($rows,$row);
	
	$row[0] = "Over 60%";
	$row[1] = $overSixty;
	array_push($rows,$row);
	
	$row[0] = "Over 40%";
	$row[1] = $overForty;
	array_push($rows,$row);

	$row[0] = "Over 20%";
	$row[1] = $overTwenty;
	array_push($rows,$row);
	
	$row[0] = "Over 10%";
	$row[1] = $overTen;
	array_push($rows,$row);

	$row[0] = "Below 10%";
	$row[1] = $belowOrTen;
	array_push($rows,$row);

	print json_encode($rows, JSON_NUMERIC_CHECK);
	mysql_close($con);
?>