<!DOCTYPE html>
<html lang="en">

<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<title>SQL Chart Test</title>
<script src="http://ajax.googleapis.com/ajax/libs/jquery/1.8.2/jquery.min.js" type="text/javascript"></script>

<?php
	include("config.php");
	$sql="SELECT time,irradiance FROM irradianceData";
	$result=mysql_query($sql);
	//$row=mysql_fetch_array($result);
	
	while ($row = mysql_fetch_array($result)) {
	   //extract $row;
	   $row['time'] *= 1000; // convert from Unix timestamp to JavaScript time
	  // Print "<br>".$row['time'];
	   $data[] = $row;
	}
	Print $data[1,'time'];
?>

<script type="text/javascript">
$(function () {
    var chart;
    $(document).ready(function() {
    // Apply the grey theme
Highcharts.setOptions({
   colors: ["#DDDF0D", "#7798BF", "#55BF3B", "#DF5353", "#aaeeee", "#ff0066", "#eeaaee", 
      "#55BF3B", "#DF5353", "#7798BF", "#aaeeee"],
   chart: {
      backgroundColor: {
         linearGradient: [0, 0, 0, 400],
         stops: [
            [0, 'rgb(96, 96, 96)'],
            [1, 'rgb(25, 25, 25)']
         ]
      },
      borderWidth: 0,
      borderRadius: 0,
      plotBackgroundColor: null,
      plotShadow: false,
      plotBorderWidth: 0
   },
   title: {
      style: { 
         color: '#FFF',
         font: '16px Lucida Grande, Lucida Sans Unicode, Verdana, Arial, Helvetica, sans-serif'
      }
   },
   subtitle: {
      style: { 
         color: '#DDD',
         font: '12px Lucida Grande, Lucida Sans Unicode, Verdana, Arial, Helvetica, sans-serif'
      }
   },
   xAxis: {
      gridLineWidth: 0,
      lineColor: '#999',
      tickColor: '#999',
      labels: {
         style: {
            color: '#999',
            fontWeight: 'bold'
         }
      },
      title: {
         style: {
            color: '#AAA',
            font: 'bold 12px Lucida Grande, Lucida Sans Unicode, Verdana, Arial, Helvetica, sans-serif'
         }            
      }
   },
   yAxis: {
      alternateGridColor: null,
      minorTickInterval: null,
      gridLineColor: 'rgba(255, 255, 255, .1)',
      lineWidth: 0,
      tickWidth: 0,
      labels: {
         style: {
            color: '#999',
            fontWeight: 'bold'
         }
      },
      title: {
         style: {
            color: '#AAA',
            font: 'bold 12px Lucida Grande, Lucida Sans Unicode, Verdana, Arial, Helvetica, sans-serif'
         }            
      }
   },
   legend: {
      itemStyle: {
         color: '#CCC'
      },
      itemHoverStyle: {
         color: '#FFF'
      },
      itemHiddenStyle: {
         color: '#333'
      }
   },
   credits: {
      style: {
         right: '50px'
      }
   },
   labels: {
      style: {
         color: '#CCC'
      }
   },
   tooltip: {
      backgroundColor: {
         linearGradient: [0, 0, 0, 50],
         stops: [
            [0, 'rgba(96, 96, 96, .8)'],
            [1, 'rgba(16, 16, 16, .8)']
         ]
      },
      borderWidth: 0,
      style: {
         color: '#FFF'
      }
   },
   
   
   plotOptions: {
      line: {
         dataLabels: {
            color: '#CCC'
         },
         marker: {
            lineColor: '#333'
         }
      },
      spline: {
         marker: {
            lineColor: '#333'
         }
      },
      scatter: {
         marker: {
            lineColor: '#333'
         }
      }
   },
   
   toolbar: {
      itemStyle: {
         color: '#CCC'
      }
   }
});
    
        chart = new Highcharts.Chart({
            chart: {
                renderTo: 'irradiance',
                type: 'line',
                marginRight: 130,
                marginBottom: 25
            }, credits: {
            enabled: false
        },

            title: {
                text: 'Daily Irradiance',
                x: -20 //center
            },
            subtitle: {
                text: 'Source: Sambel Kunda',
                x: -20
            },
            xAxis: {
                
            },
            yAxis: {
                title: {
                    text: 'Irradiance (W/m2)'
                },
                plotLines: [{
                    value: 0,
                    width: 1,
                    color: '#808080'
                }]
            },
            tooltip: {
                formatter: function() {
                        return '<b>'+ this.series.name +'</b><br/>'+
                        this.x +': '+ this.y +'W/m2';
                }
            },
            legend: {
                layout: 'vertical',
                align: 'right',
                verticalAlign: 'top',
                x: -10,
                y: 100,
                borderWidth: 0
            },
            series: [{
                data: [<?php echo join($data, ',') ?>]            
                }]
        });
    });
    
});
</script>

</head>

<body>
<script src="http://code.highcharts.com/highcharts.js"></script>
<script src="http://code.highcharts.com/modules/exporting.js"></script>
<script src="/../js/themes/gray.js"></script>

<div id="irradiance" style="width: 940px; height: 400px; margin: 0 auto">
</div>


</body>

</html>
