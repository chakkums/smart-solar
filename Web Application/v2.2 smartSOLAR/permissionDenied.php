<!DOCTYPE html>
<html>

<head>
<link href="css/960/960.css" rel="stylesheet" />
<link href="css/960/reset.css" rel="stylesheet" />
<link href="css/960/text.css" rel="stylesheet" />
<link href="css/default.css" rel="stylesheet" />
<link href="css/summary.css" rel="stylesheet" />


<script src="js/jquery-1.9.1.min.js" type="text/javascript"></script>
<script src="js/highcharts.js" type="text/javascript"></script>
<script src="js/themes/gray.js" type="text/javascript"></script>
<!-- DataTables CSS -->
<link href="css/dataTables.css" rel="stylesheet" type="text/css">
<!-- jQuery -->
<script charset="utf8" src="js/jquery-1.9.1.min.js" type="text/javascript"></script>
<!-- DataTables -->
<script charset="utf8" src="js/jquery.dataTables.min.js" type="text/javascript"></script>
<link href="http://code.jquery.com/ui/1.10.2/themes/smoothness/jquery-ui.css" rel="stylesheet" />
<script src="http://code.jquery.com/ui/1.10.2/jquery-ui.js"></script>
<link href="/resources/demos/style.css" rel="stylesheet" />


<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<title>Summary - smartSOLAR</title>

<script type="text/javascript">
$(document).ready(function() {
	$('#locations').dataTable( {
		"sScrollY": "310px",
		"bPaginate": false
	} );
} );</script>


</head>

<body>
<header>
	<div class="container_12">
		<div class="grid_3">
			<a href="index.php">
			<img alt="smartSOLAR" src="images/smartSolarHeader.png" /> </a>
		</div>
		<div class="grid_7">
			<br />
			<div id="cssmenu">
				<ul>
					<li class="active"><a href="summary.php"><span>Summary</span></a></li>
					<li class="has-sub"><a href="#"><span>Charging Station</span></a>
					<ul>
						<li><a href="environment.php"><span>Environment</span></a></li>
						<li class="last"><a href="systemInformation.php"><span>System Information</span></a></li>
					</ul>
					</li>
					<li><a href="loadDetails.php"><span>Battery Load</span></a></li>
					<li class="last"><a href="index.php"><span>About</span></a></li>
				</ul>
			</div>
		</div>
		<div id="logout" class="grid_2">
			<br />
			Welcome <?php 
				session_start();
			echo $_SESSION['login_user'];?>.<br />
			<a href="logout.php">Sign out</a> </div>
	</div>
</header>
<div id="content">
<div class="container_12">
	<div class="grid_4 prefix_4" id="error">
		<br/>
		<br/>
		<h1>Access denied</h1>
		<p> You do not have the permissions to access this page, please contact an admin.</p>
		<br/>
		<br/>
		<br/>
		<br/>
		<br/>
		<br/>
	</div>
	</div>
</div>
<footer>
	<div id="container" class="container_12">
		<div id="footer1" class="grid_4">
		<img alt="Affiliate Logos" src="images/logos.png" /></div>
		<div id="footer2" class="grid_4">
			<br />
			<h4>Site Index</h4>
			<ul>
				<li><a href="index.php">Home</a></li>
				<li><a href="summary.php">Summary</a></li>
				<li><a href="environment.php">Environment Data</a></li>
				<li><a href="systemInformation.php">System Information</a></li>
				<li><a href="loadDetails.php">Battery Details</a></li>

			</ul>
		</div>
		<div id="footer3" class="grid_4 ">
			<br />
			<h4>Contacts</h4>
			<ul>
				<li><a href="http://www.strath.ac.uk">University of Strathclyde</a></li>
				<li><a href="http://www.strath.ac.uk/eee/gambiaproject/">Gambia 
				Project</a></li>
				<li><a href="http://www.strath.ac.uk/viprojects/">VIP</a></li>
				<li><a href="http://arduino.cc">Arduino</a></li>
			</ul>
		</div>
	</div>
</footer>

</body>

</html>
