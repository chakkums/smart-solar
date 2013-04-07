<!DOCTYPE html>
<html>

<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<link href="css/960/960.css" rel="stylesheet" />
<link href="css/960/reset.css" rel="stylesheet" />
<link href="css/960/text.css" rel="stylesheet" />
<link href="css/default.css" rel="stylesheet" />
<link href="css/login.css" rel="stylesheet" />
<title>Login - smartSOLAR</title>
</head>

<body>

<?php
	include("utilities/config.php");

	session_start();
	if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		// username and password sent from Form 
		$myusername=mysql_real_escape_string($_POST['username']); //insecure, should be changed to mysql_real_escape_string 
		$mypassword=sha1(mysql_real_escape_string($_POST['password'])); 
		
		$sql="SELECT id FROM admin WHERE username='$myusername' and password='$mypassword' and approved > 1"; //1=user, so anyone with access greater than that
		$result=mysql_query($sql);
		$row=mysql_fetch_array($result);
		$active=$row['active'];
		$count=mysql_num_rows($result);
		
		
		// If result matched $myusername and $mypassword, table row must be 1 row
		if($count==1)
		{
			session_start();
			$_SESSION['login_user']=$myusername;
			
			header("location: summary.php");
		}
		else 
		{
			$error="Your username or password is invalid, or you have not been approved by an admin.";
		}
	}
?>
<header>
	<div class="container_12">
		<div>
			<br />
			<br />
			<br />
		</div>
		<div class="grid_6 prefix_3">
			<a href="index.php"><img alt="smartSOLAR" src="images/login/smartSolarLogin.png" /> </a>
		</div>
		<div class="clear">
		</div>
		<div>
			<br />
		</div>
		<div class="grid_4 prefix_4">
			<form action="" method="post">
				<label id="error"><?php 
		if(!empty($error)){
			echo $error;
			echo("<br/><br/>");	 
		}	
		
	?></label><label>Username :</label> <input name="username" type="text" required/><br />
				<br />
				<label>Password :</label>
				<input name="password" type="password" required/><br />
				<br />
				<button id="button" type="submit" ><span>Login</span></button>
			</form>
			<div>
				Or <a href="register.php">register</a> a new user. </div>
		</div>
	</div>
</header>

</body>

</html>