<!DOCTYPE html>
<html>

<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<link href="css/960/960.css" rel="stylesheet" />
<link href="css/960/reset.css" rel="stylesheet" />
<link href="css/960/text.css" rel="stylesheet" />
<link href="css/default.css" rel="stylesheet" />
<link href="css/login.css" rel="stylesheet" />
<title>Register - smartSOLAR</title>
</head>

<body>

<?php
	include("utilities/config.php");
	if($_SERVER["REQUEST_METHOD"] == "POST")
	{
		// username and password sent from Form
		$username=mysql_real_escape_string($_POST['username']); 
		$password=mysql_real_escape_string($_POST['password']); 
		$cpassword=mysql_real_escape_string($_POST['cPassword']);
		if($password == $cpassword){
			$password=sha1($password); // Encrypted Password
			$sql="SELECT username FROM admin WHERE username='".$username."'";
			$result=mysql_query($sql);
			
			if(mysql_num_rows($result) == 0){

				$sql="Insert into admin(username,password) values('$username','$password');";
				$result=mysql_query($sql);
		
				$message = "Registered Successfully, please wait for admin approval before <a href=\"login.php\">logging in</a>.";
			}else{
				$error = "Username already in use, please choose another one.";
			}
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
			<form action="register.php" method="post">
				<label id="message"><?php 
		if(!empty($message)){
			echo $message;
			echo("<br/><br/>");	 
		}	
		
	?></label><label id="error"><?php 
		if(!empty($error)){
			echo $error;
			echo("<br/><br/>");	 
		}	
		
	?></label><label>Choose a username and password:<br />
				<br />
				</label><label>Username &nbsp;:</label>
				<input name="username" type="text" required /><br />
				<br />
				<label>Password &nbsp;:</label>
				<input name="password" type="password" required onchange="form.cPassword.pattern = this.value;"/><br />
				<br/>
				<label>Confirm  &nbsp;&nbsp;&nbsp;  : </label>
				<input name="cPassword" type="password" required/>
				<br /><br />
				<button id="button" type="submit"><span>Register</span></button>
				<br />
			</form>
			<div>
				Or <a href="login.php">login</a> as an existing user. </div>
		</div>
	</div>
</header>

</body>

</html>