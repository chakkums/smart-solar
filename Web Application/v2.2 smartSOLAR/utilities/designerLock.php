<?php
	include('utilities/config.php');
	session_start();
	$user_check=$_SESSION['login_user'];
	
	$ses_sql=mysql_query("select username,approved from admin where username='".$user_check."'");
	
	$row=mysql_fetch_array($ses_sql);
	
	$login_session=$row['username'];
	$approvedLevel = $row['approved'];
	
	if(isset($login_session))
	{
		if($approvedLevel < 1){
			session_start();
			if(session_destroy())
			{
			header("Location: login.php");
			}
		}
		if($approvedLevel < 3){//if not designer
			header("Location: permissionDenied.php");
		}
	}
?>
