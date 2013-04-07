<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">
<html xmlns="http://www.w3.org/1999/xhtml">

<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<title>Login</title>
</head>

<body>

<?php
	include("config.php");
	session_start();
	if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		// username and password sent from Form 
		$myusername=mysql_real_escape_string($_POST['username']); //insecure, should be changed to mysql_real_escape_string 
		$mypassword=sha1(mysql_real_escape_string($_POST['password'])); 
		
		$sql="SELECT id FROM admin WHERE username='$myusername' and password='$mypassword'";
		$result=mysql_query($sql);
		$row=mysql_fetch_array($result);
		$active=$row['active'];
		$count=mysql_num_rows($result);
		
		
		// If result matched $myusername and $mypassword, table row must be 1 row
		if($count==1)
		{
			session_start();
			$_SESSION['login_user']=$myusername;
			
			header("location: welcome.php");
		}
		else 
		{
			$error="Your username or password is invalid.";
		}
	}
?>

<form action="" method="post">
	<label>Username :</label> <input name="username" type="text" /><br />
	<label>Password :</label> <input name="password" type="password" /><br />
	<input type="submit" value=" Submit " /><br />
	<label>
	<?php 
		if(!empty($error)){
			echo $error; 
		}		
	?>
	</label>
</form>

<div>
Or <a href="register.php">register</a> a new user. 
</div>

</body>

</html>
