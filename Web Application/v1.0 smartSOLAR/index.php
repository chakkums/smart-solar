<!DOCTYPE html>
<html lang="en">

<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<link href="css/960/960.css" rel="stylesheet" />
<link href="css/960/reset.css" rel="stylesheet" />
<link href="css/960/text.css" rel="stylesheet" />
<link href="css/default.css" rel="stylesheet" />
<link href="css/main.css" rel="stylesheet" />
<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.6.2/jquery.min.js" type="text/javascript"></script>
<script src="js/jquery.cycle.all.js" type="text/javascript"></script>
<script type="text/javascript">
$(document).ready(function(){
	$('#slideshowSlides').cycle();
});
</script>
<title>smartSOLAR</title>
</head>

<body>

<header>
	<div id="container" class="container_12">
		<div id="logo" class="grid_10 prefix_1">
			<img alt="smartSOLAR" src="images/smartSolarMain.png" /> </div>
	</div>
	<div class="clear">
	</div>
</header>
<div id="content">
	<div class="container_12">
		<div>
			<br />
		</div>
		<div id="slideshowSlides" class="grid_12">
			<img alt="1" src="images/slideshow/1.png" />
			<img alt="2" src="images/slideshow/2.png" />
			<img alt="3" src="images/slideshow/3.png" />
			<img alt="4" src="images/slideshow/4.png" /> </div>
		<div class="clear">
		</div>
		<div>
			<br />
		</div>
		<div class="grid_8">
			<img alt="How it works" src="images/howitworks.png" /> </div>
		<div class="grid_4">
			<div>
				<br />
				<br />
				<br />
			</div>

			<button id="button" onclick="parent.location='summary.php'" type="button">
			Start Here</button></div>
		<div class="clear">
		</div>
		<div>
			<br />
		</div>
		<div class="container_12">
			<div class="grid_3">
				<h1>Solar System</h1>
				<p>Battery Charging Stations are an affordable way for people living 
				in rural areas of developing countries to have access to electricity.&nbsp; 
				However many systems that are currently installed fail prematurely, 
				and very little is known as to the specific cause of the failures.</p>
				<p>Any data gathered is often anecdotal and inaccurate, and there 
				is a clear need for reliable information about the usage of these 
				systems.</p>
			</div>
			<div class="grid_3">
				<h1>Communications</h1>
				<p>Using modern mobile technologies, it is possible to remotely 
				monitor the battery charging stations, and understand the usage 
				and the deterioration of the batteries.&nbsp; This allows the developer 
				to design more robust and reliable solutions in the future.</p>
				<p>Small low powered microcontrollers, paired with GSM modems have 
				the capability to upload data directly to a remote server over the 
				internet.</p>
			</div>
			<div class="grid_3">
				<h1>Web Server</h1>
				<p>This remote server situated in the UK&nbsp; receives data from 
				the remote units, and then parses and stores the information in 
				a SQL database, which can be accessed from clients all over the 
				world, including the developing country.</p>
				<p>Once the data has been gathered and stored, calculations can 
				be carried out on the batteries in order to understand their condition.
				</p>
			</div>
			<div class="grid_3">
				<h1>Analysis</h1>
				<p>Assistance can be given remotely through the communication channel 
				to the operator of the system.&nbsp; The operator may not be technically 
				qualified, so any assistance in proloinging the life of their assets 
				will be welcome.</p>
				<p>When limited maintenance and repair services are offered, it 
				allows savings in costs, if it is known in advance which systems 
				need attention, when very often the systems are very far apart geographically.</p>
			</div>
		</div>
		<div class="clear">
		</div>
	</div>
</div>
<footer>
	<div id="container" class="container_12">
		<div id="footer1" class="grid_4">
&nbsp;<img alt="Affiliate Logos" src="images/logos.png" /></div>
		<div id="footer2" class="grid_4">
			<br />
			<h4>Site Index</h4>
			<ul>
				<li>Stuff</li>
				<li>More Stuff</li>
			</ul>
		</div>
		<div id="footer3" class="grid_4 ">
			<br />
			<h4>Contacts</h4>
			<ul>
				<li><a href="http://www.strath.ac.uk">University of Strathclyde</a></li>
				<li><a href="http://www.strath.ac.uk/eee/gambiaproject/">Gambia 
				Project</a></li>
				<li><a href="http://arduino.cc">Arduino</a></li>
			</ul>
		</div>
	</div>
</footer>

</body>

</html>