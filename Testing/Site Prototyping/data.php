<?php
$con = mysql_connect("localhost","root","");

if (!$con) {
  die('Could not connect: ' . mysql_error());
}

mysql_select_db("smartsolar", $con);

$result = mysql_query("SELECT * FROM irradiancedata");

while($row = mysql_fetch_array($result)) {
  echo $row['time'] . "\t" . $row['irradiance']. "\n";
}

mysql_close($con);
?>