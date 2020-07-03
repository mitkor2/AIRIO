/**
 * ---------------------------------------
 * This demo was created using amCharts 4.
 *
 * For more information visit:
 * https://www.amcharts.com/
 *
 * Documentation is available at:
 * https://www.amcharts.com/docs/v4/
 * ---------------------------------------
 */

// Themes begin
am4core.useTheme(am4themes_kelly);
// Themes end

// create chart
var chart = am4core.create("chartdiv", am4charts.GaugeChart);
chart.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart.innerRadius = -25;

var axis = chart.xAxes.push(new am4charts.ValueAxis());
axis.min = 0;
axis.max = 100;
axis.strictMinMax = true;
axis.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();
var range0 = axis.axisRanges.create();
range0.value = 0;
range0.endValue = 50;
range0.axisFill.fillOpacity = 1;
range0.axisFill.fill = colorSet.getIndex(0);
range0.axisFill.zIndex = - 1;

var range1 = axis.axisRanges.create();
range1.value = 50;
range1.endValue = 80;
range1.axisFill.fillOpacity = 1;
range1.axisFill.fill = colorSet.getIndex(2);
range1.axisFill.zIndex = -1;

var range2 = axis.axisRanges.create();
range2.value = 80;
range2.endValue = 100;
range2.axisFill.fillOpacity = 1;
range2.axisFill.fill = colorSet.getIndex(4);
range2.axisFill.zIndex = -1;

var hand = chart.hands.push(new am4charts.ClockHand());

// using chart.setTimeout method as the timeout will be disposed together with a chart
chart.setTimeout(Value_PM1_0, 2000);

function Value_PM1_0() {
    hand.showValue(55, 1000, am4core.ease.cubicOut);
    chart.setTimeout(Value_PM1_0, 2000);
}




/* --- new ---- */
var chart1 = am4core.create("chartdiv1", am4charts.GaugeChart);
chart1.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart1.innerRadius = -25;

var axis1 = chart1.xAxes.push(new am4charts.ValueAxis());
axis1.min = 0;
axis1.max = 100;
axis1.strictMinMax = true;
axis1.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis1.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart1_range0 = axis1.axisRanges.create();
chart1_range0.value = 0;
chart1_range0.endValue = 50;
chart1_range0.axisFill.fillOpacity = 1;
chart1_range0.axisFill.fill = colorSet.getIndex(0);
chart1_range0.axisFill.zIndex = - 1;

var chart1_range1 = axis1.axisRanges.create();
chart1_range1.value = 50;
chart1_range1.endValue = 80;
chart1_range1.axisFill.fillOpacity = 1;
chart1_range1.axisFill.fill = colorSet.getIndex(2);
chart1_range1.axisFill.zIndex = -1;

var chart1_range2 = axis1.axisRanges.create();
chart1_range2.value = 80;
chart1_range2.endValue = 100;
chart1_range2.axisFill.fillOpacity = 1;
chart1_range2.axisFill.fill = colorSet.getIndex(4);
chart1_range2.axisFill.zIndex = -1;

var hand1 = chart1.hands.push(new am4charts.ClockHand());

// using chart1.setTimeout method as the timeout will be disposed together with a chart1
chart1.setTimeout(Value_PM2_5, 2000);

function Value_PM2_5() {
    hand1.showValue(55, 1000, am4core.ease.cubicOut);
    chart1.setTimeout(Value_PM2_5, 2000);
}


