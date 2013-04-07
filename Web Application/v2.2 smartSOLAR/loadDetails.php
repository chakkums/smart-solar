<!DOCTYPE html>
<html>

<head>
<link href="css/960/960.css" rel="stylesheet" />
<link href="css/960/reset.css" rel="stylesheet" />
<link href="css/960/text.css" rel="stylesheet" />
<link href="css/default.css" rel="stylesheet" />
<link href="css/loadDetails.css" rel="stylesheet" />

<link href="css/loadDetails.css" rel="stylesheet" />
<script src="js/jquery-1.9.1.min.js" type="text/javascript"></script>

<!-- DataTables CSS -->
<link href="css/dataTables.css" rel="stylesheet" type="text/css" />
<!-- jQuery -->
<script charset="utf8" src="js/jquery-1.9.1.min.js" type="text/javascript"></script>
<!-- DataTables -->
<script charset="utf8" src="js/jquery.dataTables.min.js" type="text/javascript"></script>
<link href="http://code.jquery.com/ui/1.10.2/themes/smoothness/jquery-ui.css" rel="stylesheet" />
<script src="http://code.jquery.com/ui/1.10.2/jquery-ui.js"></script>

<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<title>Electrical Loads - smartSOLAR</title>
</head>

<body>

<?php
	include('utilities/designerLock.php');
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
						<li class="last"><a href="systemInformation.php"><span>System 
						Information</span></a></li>
					</ul>
					</li>
					<li><a href="loadDetails.php"><span>Battery Load</span></a></li>
					<li class="last"><a href="index.php"><span>About</span></a></li>
				</ul>
			</div>
		</div>
		<div id="logout" class="grid_2">
			<br />
			Welcome <?php echo $login_session;?>.<br />
			<a href="logout.php">Sign out</a> </div>
	</div>
</header>
<script type="text/javascript">
			var disabled = 0;

			$(document).ready(function() {
					$('#batteryData').dataTable( {
					"sScrollY": "300px",
					"bPaginate": true
					} );
					$('#batteryData tbody').delegate("tr", "click", rowClick);
					$('#loadData').dataTable( {
					"sScrollY": "200px",
					"bPaginate": true,
					"aaSorting": [[ 0, "desc" ]]
					} );

				} );
				
				var hlr = 0;   // Reference to the currently highlighted row

			function rowClick()
			{
			   if (hlr)
			      $("td:first", hlr).parent().children().each(function(){$(this).removeClass('markrow');});
			   hlr = this;
			   $("td:first", this).parent().children().each(function(){$(this).addClass('markrow');});
			
			   var ID = $("td:eq(0)", this).text();  //Assign to hidden field on form
			   document.getElementById("batteryID").value=ID;
			}
</script>
<div id="content">
	<div class="container_12">
		<div>
			<br/>
		</div>
		<div class="grid_4 prefix_1">
			<h1>Battery Load Details</h1>
		</div>
		<div class="clear"></div>
		<div id="data" class="container_12">
			<?php
				if($_SERVER["REQUEST_METHOD"] == "POST")
				{
					// Location sent from form
					$batteryID=($_POST['batID']);

					if(($batteryID != "")){
					?>
			<div class="grid_12">
				<h2>Report for Battery <?php echo($batteryID); ?></h2>
			</div>
				
			<div class="grid_6 prefix_1">
				<?php 
				$result = mysql_query("SELECT * FROM batteries WHERE batteryID ='".$batteryID."'");
				$row = mysql_fetch_array($result);
				
				echo ("Location: <b>".$row['location']."</b> <br/>");
				echo("Number: <b>".$row['number']."</b><br/>");
				echo("Battery Type: <b>".$row['type']."</b><br/>");
				echo("Manufacturer Predicted Cycles: <b>".$row['recommendedCycles']."</b><br/>");
				echo("Initial Capacity: <b>".$row['initialCapacity']." Ah</b><br/>");
				echo "<br/>";
				echo("Number of Cycles: <b>".$row['numberOfCycles']."</b><br/>");
				echo("Battery Wear: <b>".(100-number_format($row['stateOfHealth'],2))."%</b><br/>");
				echo("Available Capacity: <b>".number_format($row['availableCapacity'],2)." Ah</b><br/>");
				echo("Battery State of Health: <b>".number_format($row['stateOfHealth'],2)."%</b><br/>");
				$soh = $row['stateOfHealth'];
				$disabled = $row['disabled'];
				?>
				<br/>
				
			</div>	

			<div class="grid_5">
				<?php if($disabled == 1){?>
					<img id="status" src="images/cross.png" alt="Not OK"/>
					<?php }else{ ?>
					<img id="status" src="images/tick.png" alt="OK"/>
					<?php } ?>			
			</div>
			<div class="grid_5 prefix_1" >
			<form action="tEnable.php" method="post">
				<input name="batID" readonly="" type="hidden" value="<?php echo $batteryID ?>" />
				<input id="disable" name="disabled" readonly="" type="hidden" value="<?php echo $disabled ?>" />
				<button id="disable" type="submit"><span><?php 
				if($disabled == 1){
					echo "Enable";
					}else{ 
					echo "Disable";
					} ?>	</span>
				</button>
			</form>

			</div>
		
			<div class="grid_4 prefix_1" id="highlight">
					<?php if($disabled == 1){?>
						<label id="batteryStatus">Battery disabled.<br/></label>
					<?php }else{ ?>
						<label id="batteryStatus">Battery enabled.<br/></label>
					<?php } ?>
				</div>
			<div class="clear"></div>
				<div class="clear"></div>
			<div class="grid_10 prefix_1">
				<label id="info"><br/>Use the button above to enable, or disable this battery for usage by customers. The system will
				automatically disable batteries that have a state of health below 10%. <br/><br/></label>
			</div>			
			<div class="grid_12" id="trends"></div>

			<script src="js/highstock.js" type="text/javascript"></script>
						<script src="js/themes/smartSOLAR.js" type="text/javascript"></script>


			<script>
$(function() {

$.getJSON('utilities/loadTrends.php?batteryID=<?php echo $batteryID ?>', function(json) {
		// Create the chart
		$('#trends').highcharts('StockChart', {			
			buttons: [{
			    type: 'day',
			    count: 1,
			    text: '1d'
			}, {
			    type: 'week',
			    count: 1,
			    text: '1w'
			}, {
			    type: 'month',
			    count: 1,
			    text: '1m'
			}, {
			    type: 'ytd',
			    text: 'YTD'
			}, {
			    type: 'year',
			    count: 1,
			    text: '1y'
			}, {
			    type: 'all',
			    text: 'All'
			}],
			rangeSelector : {
			buttonTheme: { // styles for the buttons
	    		fill: 'none',
	    		stroke: 'none',
	    		style: {
	    			color: '#5E5E5E',
	    			fontWeight: 'bold'
	    		},
	    		states: {
	    			hover: {
	    				fill: '5E5E5E'
	    			},
	    			select: {
	    				style: {
	    					color: 'white'
	    				}
	    			}
	    		}
	    	},
	    	inputStyle: {
	    		color: '#039',
	    		fontWeight: 'bold'
	    	},
	    	labelStyle: {
	    		color: 'silver',
	    		fontWeight: 'bold'
	    	},
				selected : 1,
				inputEnabled: false,
				buttons: [{
					type: 'day',
					count: 1,
					text: '1d'
				}, {
					type: 'week',
					count: 1,
					text: '1w'
				}, {
					type: 'month',
					count: 1,
					text: '1m'
				}, {
					type: 'ytd',
					text: 'YTD'
				}, {
					type: 'year',
					count: 1,
					text: '1y'
				}, {
					type: 'all',
					text: 'All'
				}]
			},
scrollbar: {
				barBackgroundColor: 'gray',
				barBorderRadius: 7,
				barBorderWidth: 0,
				buttonBackgroundColor: 'gray',
				buttonBorderWidth: 0,
				buttonBorderRadius: 7,
				trackBackgroundColor: 'none',
				trackBorderWidth: 1,
				trackBorderRadius: 8,
				trackBorderColor: '#CCC'
		    },
			title : {
				text : 'Charge Level History for <?php echo $batteryID ?>'
			},
                yAxis: [{
                	min: 0,
                	max:100,
                    plotLines: [{
                        value: 0,
                        width: 1,
                    }]
                },{
                	min: 0,
                	opposite: true,
                    plotLines: [{
                        value: 0,
                        width: 1,
                    }]
                }],
			
			series : [{
				name : 'Charge %',
				data : json[0],
				type: 'areaspline',
				tooltip: {
					valueDecimals: 2
				}
			},{
				name : 'Load A',
				data : json[1],
				type: 'spline',
				yAxis: 1,
				tooltip: {
					valueDecimals: 2
				}
			},]
		});
	});

});
</script>
			<div class="clear"></div>
			<div class="grid_12">
			<p><br/>Below is list of all historical samples recorded from battery <?php echo $batteryID ?> over 10 minute runtimes. <br/></p>
			<table id="loadData">
				<thead>
					<tr>
						<th>Time Switched On</th>
						<th>time Switched Off</th>
						<th>Time on for (h)</th>
						<th>Start Charge Level</th>
						<th>End Charge Level</th>
						<th>Average Load (mA)</th>
						<th>Average Temperature</th>
					</tr>
				</thead>
				<?php
					$result = mysql_query("SELECT * FROM loaddata WHERE batteryID='".$batteryID."'");
					while ($row = mysql_fetch_array($result)) { ?>
				<tr>
					<?php $time = strtotime($row['timeLoadOn'])?>
					<td><?php echo date('d-m-y H:i',$time)?></td>

					<?php $time = strtotime($row['timeLoadOff'])?>
					<td><?php echo date('d-m-y H:i',$time)?></td>

					<td><?php echo number_format($row['timeOn']/60,2)?></td>
					<td><?php echo number_format($row['startChargeLevel'],2)?></td>
					<td><?php echo number_format($row['endChargeLevel'],2)?></td>
					<?php $load = $row['averageLoad']*1000 ?>
					<td><?php echo number_format($load,2)?></td>
					<td><?php echo number_format($row['temperature'],2)?>

				</tr>
				<?php } ?>
			</table>
		</div>
		<div>
			<br/>
		</div>
			
			<?php }
				}
			?></div>
		
		<div>
			<br/>
		</div>
		<div class="grid_4 prefix_1">
			<h3>All Batteries</h3>
		</div>
		<div class="grid_3 prefix_4">
			<form method="post">
				<input id="batteryID" hidden="" name="batID" />
				<button id="submit" type="submit"><span>Load battery data</span>
				</button>
			</form>
		</div>
		<div class="grid_12">
			<p>Select a battery in the table below and hit 'load data' to view detailed 
			information and trends. Use search box to filter batteries, click column 
			heads to sort.</p>
		</div>
		<div class="grid_12">
			<table id="batteryData">
				<thead>
					<tr>
						<th>Battery ID</th>
						<th>Location</th>
						<th>#</th>
						<th>Battery Type</th>
						<th>#Cycles</th>
						<th>Pred. Cycles</th>
						<th>SOH (%)</th>
						<th>Initial Cap. (Ah)</th>
						<th>Avail. Cap. (Ah)</th>
						<th>Last Charged</th>
						<th>Charge time (h)</th>
						<th>With Cust.</th>
						<th>Disabled</th>
					</tr>
				</thead>
				<?php
							$result = mysql_query("SELECT * FROM batteries");
							while ($row = mysql_fetch_array($result)) { ?>
				<tr>
					<td><?php echo $row['batteryID']?></td>
					<td><?php echo $row['location']?></td>
					<td><?php echo $row['number']?></td>
					<td><?php echo $row['type']?></td>
					<td><?php echo $row['numberOfCycles']?></td>
					<td><?php echo $row['recommendedCycles']?></td>
					<td><?php echo number_format($row['stateOfHealth'],2)?></td>
					<td><?php echo number_format($row['initialCapacity'],2)?>
					</td>
					<td><?php echo number_format($row['availableCapacity'],2)?>
					</td>
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
					<?php if($row['disabled'] == 1){
										$dis = "Yes";
									}else{
										$dis = "No";
									}
									?>
					<td><?php echo $dis?></td>

				</tr>
				<?php } ?>
			</table>
				<div>
					<br/><br/>
					</div>
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
