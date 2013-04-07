<!DOCTYPE html>
<html>

<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<title>Register</title>
</head>

<body>

<?php
	include("config.php");
	if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		// username and password sent from Form
		$username=mysql_real_escape_string($_POST['username']); 
		$password=mysql_real_escape_string($_POST['password']); 
		$password=sha1($password); // Encrypted Password
		$sql="Insert into admin(username,password) values('$username','$password');";
		$result=mysql_query($sql);
		
		echo "Registered Successfully";
	}
?>

<form action="register.php" method="post">
<label>Choose a username and password:<br/></label>
<label>Username :</label>
<input type="text" name="username"/><br />


<label>Password :</label>
<input type="password" name="password"/><br/>
<input type="submit" value=" Register "/><br />
</form>
<div>
Or <a href="login.php">login</a> 
</div>
</body>

</html>
