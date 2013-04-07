<?php
$con = mysql_connect("localhost","root","");

if (!$con) {
  die('Could not connect: ' . mysql_error());
}

mysql_select_db("smartsolar", $con);

$result = mysql_query("SELECT irradiance FROM irradiancedata WHERE DATE(time) = '2013-02-12'");
$rows = array();
$rows['name'] = '12/02/2013';
while($r = mysql_fetch_array($result)) {
  $rows['data'][] = $r['irradiance'];
}

$result = mysql_query("SELECT irradiance FROM irradiancedata WHERE DATE(time) = '2013-02-13'");
$rows1 = array();
$rows1['name'] = '13/02/2013';
while($rr = mysql_fetch_array($result)) {
  $rows1['data'][] = $rr['irradiance'];
}

$final = array();
array_push($final,$rows);
array_push($final,$rows1);

print json_encode($final, JSON_NUMERIC_CHECK);
mysql_close($con);
?>