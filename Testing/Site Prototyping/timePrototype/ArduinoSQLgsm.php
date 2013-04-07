<!DOCTYPE html>
<html lang="en">

<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<title>SQL Chart Test</title>

<script type="text/javascript" src="js/jquery-1.9.1.min.js" ></script>
<script type="text/javascript" src="js/highcharts.js" ></script>
<script type="text/javascript" src="js/themes/gray.js"></script>
<script type="text/javascript">
$(function () {
    var chart;
    $(document).ready(function() {
        $.getJSON("dataJSON.php", function(json) {
        
            chart = new Highcharts.Chart({
                chart: {
                    renderTo: 'time',
                    type: 'line',
                    marginRight: 130,
                    marginBottom: 25
                },
                title: {
                    text: 'Time',
                    x: -20 //center
                },
                subtitle: {
                    text: 'Source: Arduino millis() function',
                    x: -20
                },
                xAxis: {
                    //categories: ['12am', '1am', '2am', '3am', '4am', '5am', '6am',
					//'7am', '8am', '9am', '10am', '11am','12pm','1pm','2pm','3pm','4pm'
					//,'5pm','6pm','7pm','8pm','9pm','10pm','11pm']
                },
                yAxis: {
					min:0,
                    title: {
                        text: 'Time (s)'
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
                            this.x +': '+ this.y + ' s';
                    }
                },
                legend: {
                    layout: 'vertical',
                    align: 'right',
                    verticalAlign: 'top',
                    x: -5,
                    y: 100,
                    borderWidth: 0
                },
                series: json
            });
        });
    
    });
    
});
        </script>
</head>

<body>

<div id="time" style="width: 940px; height: 400px; margin: 0 auto">
</div>


</body>

</html>