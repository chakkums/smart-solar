<?php
$con = mysql_connect("localhost","root","");

if (!$con) {
  die('Could not connect: ' . mysql_error());
}

mysql_select_db("test", $con);

$result = mysql_query("SELECT time FROM time");
$rows = array();
$rows['name'] = 'millis/1000';
while($r = mysql_fetch_array($result)) {
  $rows['data'][] = $r['time'];
}

$final = array();
array_push($final,$rows);

print json_encode($final, JSON_NUMERIC_CHECK);
mysql_close($con);
?>