<!DOCTYPE html>
<html lang="en">

<head>
<meta content="text/html; charset=utf-8" http-equiv="Content-Type" />
<title>SQL Chart Test</title>

<script type="text/javascript" src="js/jquery-1.9.1.min.js" ></script>
<script type="text/javascript" src="js/highcharts.js" ></script>
<script type="text/javascript" src="js/themes/gray.js"></script>

<script type="text/javascript">
    var chart;
            $(document).ready(function() {
                var options = {
                    chart: {
                        renderTo: 'irradiance',
                        defaultSeriesType: 'line',
                        marginRight: 130,
                        marginBottom: 25
                    },
                    title: {
                        text: 'Irradiance Data',
                        x: -20 //center
                    },
                    subtitle: {
                        text: 'Source: Sambel Kunda',
                        x: -20
                    },
                    xAxis: {
                        type: 'datetime',
                        tickInterval: 3600 * 1000, // one hour
                        tickWidth: 0,
                        gridLineWidth: 1,
                        labels: {
                            align: 'center',
                            x: -3,
                            y: 20,
                            formatter: function() {
                                return Highcharts.dateFormat('%l%p', this.value);
                            }
                        }
                    },
                    yAxis: {
						min:0,
                        title: {
                            text: 'Irradiance'
                        },
                        plotLines: [{
                            value: 0,
                            width: 1,
                            color: '#808080'
                        }]
                    },
                    tooltip: {
                        formatter: function() {
                                return Highcharts.dateFormat('%l%p', this.x) +': <b>'+ this.y + '</b>';
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
                        name: 'Monday'
						
                    }]
                }
                 // Load data asynchronously using jQuery. On success, add the data
                // to the options and initiate the chart.
                // This data is obtained by exporting a GA custom report to TSV.
                // http://api.jquery.com/jQuery.get/
                jQuery.get('data.php', null, function(tsv) {
                    var line = [];
                    irr = [];
                    try {
                        // split the data return into lines and parse them
                        tsv = tsv.split(/\n/g);
                        jQuery.each(tsv, function(i, line) {
                            line = line.split(/\t/);
                            date = Date.parse(line[0] +' UTC');
                            irr.push([
                                date,
                                parseInt(line[1].replace(',', ''), 10)
                            ]);
                        });
                    } catch (e) {  }
                    options.series[0].data = irr;
                    chart = new Highcharts.Chart(options);
                });
            });
</script>
</head>

<body>

<div id="irradiance" style="width: 940px; height: 400px; margin: 0 auto">
</div>


</body>

</html>