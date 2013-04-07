<?php
	$mysql_hostname = "localhost";
	$mysql_user = "root";
	$mysql_password = "";
	$mysql_database = "smartsolar";
	
	$bd = mysql_connect($mysql_hostname, $mysql_user, $mysql_password) 
	or die("Can't connect to MySql");
	
	mysql_select_db($mysql_database, $bd) or die("Can't connect to database");
?>
