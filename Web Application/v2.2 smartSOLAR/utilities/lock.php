<?php
	include('utilities/config.php');
	session_start();
	$user_check=$_SESSION['login_user'];
	
	$ses_sql=mysql_query("select username,approved from admin where username='".$user_check."'");
	
	$row=mysql_fetch_array($ses_sql);
	
	$login_session=$row['username'];
	$approvedLevel = $row['approved'];
	
	if(!isset($login_session))
	{
		if($approvedLevel < 1){
			session_start(); //If somehow user is logged in as 'user', logout and redirect
			if(session_destroy())
			{
				header("Location: login.php");
			}
		}
	}
?>
