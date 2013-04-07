<!DOCTYPE html>
<html>

<head>
<link href="css/960/960.css" rel="stylesheet" />
<link href="css/960/reset.css" rel="stylesheet" />
<link href="css/960/text.css" rel="stylesheet" />
<link href="css/default.css" rel="stylesheet" />
<link href="css/condition.css" rel="stylesheet" />
<script src="js/jquery-1.9.1.min.js" type="text/javascript"></script>
<script src="js/highcharts.js" type="text/javascript"></script>
<script src="js/themes/smartSOLAR.js" type="text/javascript"></script>
<!-- DataTables CSS -->
<link href="css/dataTables.css" rel="stylesheet" type="text/css" />
<!-- jQuery -->
<script charset="utf8" src="js/jquery-1.9.1.min.js" type="text/javascript"></script>
<!-- DataTables -->
<script charset="utf8" src="js/jquery.dataTables.min.js" type="text/javascript"></script>
<link href="http://code.jquery.com/ui/1.10.2/themes/smoothness/jquery-ui.css" rel="stylesheet" />
<script src="http://code.jquery.com/ui/1.10.2/jquery-ui.js"></script>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<title>System Information - smartSOLAR</title>
</head>

<body>

<?php
	include('utilities/lock.php');
?>
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
					<li class="last"><a href="about.html"><span>About</span></a></li>
				</ul>
			</div>
		</div>
		<div id="logout" class="grid_2">
			<br />
			Welcome <?php echo $login_session;?>.<br />
			<a href="logout.php">Sign out</a> </div>
	</div>
</header>
<div id="content">
	<div class="container_12">
		<div>
			<br />
		</div>
		<div class="grid_4 prefix_1">
			<h1>System Information</h1>
		</div>
		<div class="grid_5 prefix_2">
			<form action="" method="post">
				<select id="locations" name="location">
				<option value="">Select a location</option>
				<?php
						$result = mysql_query("SELECT * FROM locations");
						while ($row = mysql_fetch_array($result)) { ?>
				<option value="<?php echo $row['name']?>"><?php echo $row['name']?>
				</option>
				<?php } ?></select><button id="submit" type="submit"><span>Load 
				condition data</span></button>
			</form>
		</div>
		<div class="clear">
		</div>
		<div class="grid_12">
			<p>To generate an system usage and condition report select a location from the 
			dropdown box above and hit 'load condition data'.</p>
		</div>
		<div class="clear">
		</div>
		<div id="data" class="container_12">
			<?php
				if($_SERVER["REQUEST_METHOD"] == "POST")
				{
					// Location sent from form
					$location=($_POST['location']);

					if($location != ""){?>
			<div class="grid_12">
				<h2>Report for <?php echo($location); ?></h2>
				<p>Asset condition summaries for at the charging station in <?php echo($location); ?>
				.</p>
				<h4>System Condition</h4>
				<?php 
					$result = mysql_query("SELECT AVG(stateOfHealth) FROM batteries WHERE location='".$location."'");
					$averageHealth =  mysql_fetch_array($result)[0];
				?>
				<p>Average battery condition: <b><?php echo number_format($averageHealth,2) ?>
				</b>%</p>
			</div>
			<div class="clear">
			</div>
			<script type="text/javascript">
        $(document).ready(function() {
                     var options = {
                chart: {
                    renderTo: 'assetPercent',
                    plotBackgroundColor: null,
                    plotBorderWidth: null,
                    plotShadow: false
                },
                title: {
                    text: 'Asset Condition Summary'
                },
                subtitle: {
                    text: 'Higher percentage is better',
                },

                tooltip: {
                    formatter: function() {
                        return '<b>'+ this.point.name +' SOH</b>: '+ this.percentage.toFixed(0) +' %';
                    }
                },
                legend: {
                    layout: 'vertical',
                    align: 'left',
                    verticalAlign: 'top',
                    x: -5,
                    y: 150,
                    borderWidth: 0
                },

                plotOptions: {
                    pie: {
                        allowPointSelect: true,
                        cursor: 'pointer',
                        dataLabels: {
                            enabled: false
                        },
                        showInLegend: true
                    }
                },
                series: [{
                    type: 'pie',
					name: 'Asset Condition',
                    data: []
                }]
            }                     
			$.getJSON("utilities/percentBattJSON.php?locParam=<?php echo $location?>", function(json) {
    	            options.series[0].data = json;
    	            chart = new Highcharts.Chart(options);
    	        });         
        });   
        </script>
			<div id="assetPercent" class="grid_6">
			</div>
			<script type="text/javascript">
        $(document).ready(function() {
                     var options = {
                chart: {
                    renderTo: 'worstTen',
                    plotBackgroundColor: null,
                    plotBorderWidth: null,
                    plotShadow: false,
                    type: 'column'
                },
                title: {
                    text: 'Worst 10 batteries for SOH'
                },
                tooltip: {
                    formatter: function() {
                            return '<b>'+ this.series.name +'</b><br/>'+
                            'Num: ' + this.x +', SOH: '+ this.y + ' %';
                    }
                },  
                xAxis: {
                    categories: [],
                    title: {
                        text: 'Battery Number'
                    },

				},
				 yAxis: [{
                	min: 0,
                    title: {
                        text: 'State of Heath %'
                    },
                    plotLines: [{
                        value: 0,
                        width: 1,
                    }]
                }],
                
                series: []
            }                     
			$.getJSON("utilities/worstTenBattJSON.php?locParam=<?php echo $location?>", function(json) {
    	            options.xAxis.categories = json[0]['data'];
                    options.series[0] = json[1];
                    options.series[0].showInLegend = false;
    	            chart = new Highcharts.Chart(options);
    	        });         
        });   
        </script>
			<div id="worstTen" class="grid_6">
			</div>
			<div class="clear">
			</div>
			<div class="grid_12">
				<br />
				<h4>System Usage</h4>
				<p>To maximise income, most batteries should be in use.</p>
			</div>
			<div id="highlightsub" class="grid_8 prefix_2">
				Percentage of the asset base currently in use:</div>
			<div class="clear"></div>
			<div id="highlight" class="grid_6 prefix_3">
				<?php
				$result = mysql_query("SELECT AVG(withCustomer) FROM batteries WHERE location='".$location."'");
					$assetUsage =  mysql_fetch_array($result)[0] *100;
					echo ($assetUsage.'%');
				?></div>
			<div class="clear"></div>
				<div id="highlightsub" class="grid_8 prefix_2">
				Average length of time batteries are constantly delivering power:</div>
				<div class="clear"></div>
				<div id="highlight" class="grid_6 prefix_3">
				<?php
				$result = mysql_query("SELECT AVG(timeOn) FROM loaddata WHERE location='".$location."'");
					$timeOn =  number_format(mysql_fetch_array($result)[0] /60,2);
					echo ($timeOn.' h');
				?></div>
				<div class="clear"></div>
				<div id="highlightsub" class="grid_8 prefix_2">
				Average load on batteries:</div>
				<div class="clear"></div>
				<div id="highlight" class="grid_6 prefix_3">
				<?php
				$result = mysql_query("SELECT AVG(averageLoad) FROM loaddata WHERE location='".$location."'");
					$avLoad =  mysql_fetch_array($result)[0];
					$inmA = $avLoad *1000;
					echo (number_format($inmA,2)).' mA';
				?></div>
				<div class="clear"></div>
					<div id="highlightsub" class="grid_8 prefix_2">
				Average battery lifetime:</div>
				<div class="clear"></div>
				<div id="highlight" class="grid_6 prefix_3">
				<?php
				$result = mysql_query("SELECT AVG(availableCapacity) FROM batteries WHERE location='".$location."'");
					$avgAvCap =  mysql_fetch_array($result)[0];
					$avLifetime = $avgAvCap/$avLoad;
					echo (number_format($avLifetime,2)).' h';
				?></div>
				<div class="clear"></div>
					<div id="highlightsub" class="grid_8 prefix_2">
				Average time to charge battery:</div>
				<div class="clear"></div>
				<div id="highlight" class="grid_6 prefix_3">
				<?php
				$result = mysql_query("SELECT AVG(timeTakenToCharge) FROM batteries WHERE location='".$location."'");
					$avgCharge =  mysql_fetch_array($result)[0]/60;
					echo (number_format($avgCharge,2)).' h';
				?></div>
				<div class="clear"></div>


			<div class="grid_12">
				<h4>System Information</h4>
				<p>Asset data can be found below, see the dropdown box to show more 
				entries at once.</p>
			</div>
			<div class="clear"></div>
			<script type="text/javascript">
			$(document).ready(function() {
					$('#batteryData').dataTable( {
					"sScrollY": "300px",
					"bPaginate": true
					} );
				} );</script>
			<div class="grid_12">
				<table id="batteryData">
					<thead>
						<tr>
							<th>#</th>
							<th>Battery ID</th>
							<th>Battery Type</th>
							<th>Number of Cycles</th>
							<th>Predicted Cycles</th>
							<th>State of Health (%)</th>
							<th>Initial Capacity (Ah)</th>
							<th>Available Capacity (Ah)</th>
							<th>Last Charged</th>
							<th>Time to charge (h)</th>
							<th>With Customer</th>
						</tr>
					</thead>
					<tbody>

					<?php
							$result = mysql_query("SELECT * FROM batteries WHERE location ='".$location."'");
							while ($row = mysql_fetch_array($result)) { ?>
					<tr>
						<td><?php echo $row['number']?></td>
						<td><?php echo $row['batteryID']?></td>
						<td><?php echo $row['type']?></td>
						<td><?php echo $row['numberOfCycles']?></td>
						<td><?php echo $row['recommendedCycles']?></td>
						<td><?php echo number_format($row['stateOfHealth'],2)?></td>
						<td><?php echo number_format($row['initialCapacity'],2)?></td>
						<td><?php echo number_format($row['availableCapacity'],2)?></td>
						<?php $time = strtotime($row['timeCharged'])?>
						<td><?php echo date('d-m-y H:i',$time)?></td>
						<?php $timeToCharge = number_format($row['timeTakenToCharge']/60,2)?>
						<td><?php echo $timeToCharge?></td>
						

						<?php if($row['withCustomer'] == 1){
										$withCust = "Yes";
									}else{
										$withCust = "No";
									}
									?>
						<td><?php echo $withCust?></td>
					</tr>
					<?php } ?>
				</tbody>
				</table>
			</div>
			<div class="clear">
			</div>
			<div>
				<br />
			</div>
			<?php }
				}
			?></div>
	</div>
	<div>
		<br />
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