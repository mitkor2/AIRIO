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

/* --- new ---- */
var chart2 = am4core.create("chartdiv2", am4charts.GaugeChart);
chart2.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart2.innerRadius = -25;

var axis2 = chart2.xAxes.push(new am4charts.ValueAxis());
axis2.min = 0;
axis2.max = 100;
axis2.strictMinMax = true;
axis2.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis2.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart2_range0 = axis2.axisRanges.create();
chart2_range0.value = 0;
chart2_range0.endValue = 50;
chart2_range0.axisFill.fillOpacity = 1;
chart2_range0.axisFill.fill = colorSet.getIndex(0);
chart2_range0.axisFill.zIndex = - 1;

var chart2_range1 = axis2.axisRanges.create();
chart2_range1.value = 50;
chart2_range1.endValue = 80;
chart2_range1.axisFill.fillOpacity = 1;
chart2_range1.axisFill.fill = colorSet.getIndex(2);
chart2_range1.axisFill.zIndex = -1;

var chart2_range2 = axis2.axisRanges.create();
chart2_range2.value = 80;
chart2_range2.endValue = 100;
chart2_range2.axisFill.fillOpacity = 1;
chart2_range2.axisFill.fill = colorSet.getIndex(4);
chart2_range2.axisFill.zIndex = -1;

var hand2 = chart2.hands.push(new am4charts.ClockHand());

// using chart2.setTimeout method as the timeout will be disposed together with a chart2
chart2.setTimeout(Value_PM4_0, 2000);
/* --- new ---- */
var chart3 = am4core.create("chartdiv3", am4charts.GaugeChart);
chart3.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart3.innerRadius = -25;

var axis3 = chart3.xAxes.push(new am4charts.ValueAxis());
axis3.min = 0;
axis3.max = 100;
axis3.strictMinMax = true;
axis3.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis3.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart3_range0 = axis3.axisRanges.create();
chart3_range0.value = 0;
chart3_range0.endValue = 50;
chart3_range0.axisFill.fillOpacity = 1;
chart3_range0.axisFill.fill = colorSet.getIndex(0);
chart3_range0.axisFill.zIndex = - 1;

var chart3_range1 = axis3.axisRanges.create();
chart3_range1.value = 50;
chart3_range1.endValue = 80;
chart3_range1.axisFill.fillOpacity = 1;
chart3_range1.axisFill.fill = colorSet.getIndex(2);
chart3_range1.axisFill.zIndex = -1;

var chart3_range2 = axis3.axisRanges.create();
chart3_range2.value = 80;
chart3_range2.endValue = 100;
chart3_range2.axisFill.fillOpacity = 1;
chart3_range2.axisFill.fill = colorSet.getIndex(4);
chart3_range2.axisFill.zIndex = -1;

var hand3 = chart3.hands.push(new am4charts.ClockHand());

// using chart3.setTimeout method as the timeout will be disposed together with a chart3
chart3.setTimeout(Value_PM10, 2000);
/* --- new ---- */
var chart4 = am4core.create("chartdiv4", am4charts.GaugeChart);
chart4.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart4.innerRadius = -25;

var axis4 = chart4.xAxes.push(new am4charts.ValueAxis());
axis4.min = 0;
axis4.max = 100;
axis4.strictMinMax = true;
axis4.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis4.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart4_range0 = axis4.axisRanges.create();
chart4_range0.value = 0;
chart4_range0.endValue = 50;
chart4_range0.axisFill.fillOpacity = 1;
chart4_range0.axisFill.fill = colorSet.getIndex(0);
chart4_range0.axisFill.zIndex = - 1;

var chart4_range1 = axis4.axisRanges.create();
chart4_range1.value = 50;
chart4_range1.endValue = 80;
chart4_range1.axisFill.fillOpacity = 1;
chart4_range1.axisFill.fill = colorSet.getIndex(2);
chart4_range1.axisFill.zIndex = -1;

var chart4_range2 = axis4.axisRanges.create();
chart4_range2.value = 80;
chart4_range2.endValue = 100;
chart4_range2.axisFill.fillOpacity = 1;
chart4_range2.axisFill.fill = colorSet.getIndex(4);
chart4_range2.axisFill.zIndex = -1;

var hand4 = chart4.hands.push(new am4charts.ClockHand());

// using chart4.setTimeout method as the timeout will be disposed together with a chart4
chart4.setTimeout(Value_TEMP, 2000);
/* --- new ---- */
var chart5 = am4core.create("chartdiv5", am4charts.GaugeChart);
chart5.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart5.innerRadius = -25;

var axis5 = chart5.xAxes.push(new am4charts.ValueAxis());
axis5.min = 0;
axis5.max = 100;
axis5.strictMinMax = true;
axis5.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis5.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart5_range0 = axis5.axisRanges.create();
chart5_range0.value = 0;
chart5_range0.endValue = 50;
chart5_range0.axisFill.fillOpacity = 1;
chart5_range0.axisFill.fill = colorSet.getIndex(0);
chart5_range0.axisFill.zIndex = - 1;

var chart5_range1 = axis5.axisRanges.create();
chart5_range1.value = 50;
chart5_range1.endValue = 80;
chart5_range1.axisFill.fillOpacity = 1;
chart5_range1.axisFill.fill = colorSet.getIndex(2);
chart5_range1.axisFill.zIndex = -1;

var chart5_range2 = axis5.axisRanges.create();
chart5_range2.value = 80;
chart5_range2.endValue = 100;
chart5_range2.axisFill.fillOpacity = 1;
chart5_range2.axisFill.fill = colorSet.getIndex(4);
chart5_range2.axisFill.zIndex = -1;

var hand5 = chart5.hands.push(new am4charts.ClockHand());

// using chart5.setTimeout method as the timeout will be disposed together with a chart5
chart5.setTimeout(Value_HUM, 2000);
/* --- new ---- */
var chart6 = am4core.create("chartdiv6", am4charts.GaugeChart);
chart6.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart6.innerRadius = -25;

var axis6 = chart6.xAxes.push(new am4charts.ValueAxis());
axis6.min = 0;
axis6.max = 100;
axis6.strictMinMax = true;
axis6.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis6.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart6_range0 = axis6.axisRanges.create();
chart6_range0.value = 0;
chart6_range0.endValue = 50;
chart6_range0.axisFill.fillOpacity = 1;
chart6_range0.axisFill.fill = colorSet.getIndex(0);
chart6_range0.axisFill.zIndex = - 1;

var chart6_range1 = axis6.axisRanges.create();
chart6_range1.value = 50;
chart6_range1.endValue = 80;
chart6_range1.axisFill.fillOpacity = 1;
chart6_range1.axisFill.fill = colorSet.getIndex(2);
chart6_range1.axisFill.zIndex = -1;

var chart6_range2 = axis6.axisRanges.create();
chart6_range2.value = 80;
chart6_range2.endValue = 100;
chart6_range2.axisFill.fillOpacity = 1;
chart6_range2.axisFill.fill = colorSet.getIndex(4);
chart6_range2.axisFill.zIndex = -1;

var hand6 = chart6.hands.push(new am4charts.ClockHand());

// using chart6.setTimeout method as the timeout will be disposed together with a chart6
chart6.setTimeout(Value_O3, 2000);
/* --- new ---- */
var chart7 = am4core.create("chartdiv7", am4charts.GaugeChart);
chart7.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart7.innerRadius = -25;

var axis7 = chart7.xAxes.push(new am4charts.ValueAxis());
axis7.min = 0;
axis7.max = 100;
axis7.strictMinMax = true;
axis7.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis7.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart7_range0 = axis7.axisRanges.create();
chart7_range0.value = 0;
chart7_range0.endValue = 50;
chart7_range0.axisFill.fillOpacity = 1;
chart7_range0.axisFill.fill = colorSet.getIndex(0);
chart7_range0.axisFill.zIndex = - 1;

var chart7_range1 = axis7.axisRanges.create();
chart7_range1.value = 50;
chart7_range1.endValue = 80;
chart7_range1.axisFill.fillOpacity = 1;
chart7_range1.axisFill.fill = colorSet.getIndex(2);
chart7_range1.axisFill.zIndex = -1;

var chart7_range2 = axis7.axisRanges.create();
chart7_range2.value = 80;
chart7_range2.endValue = 100;
chart7_range2.axisFill.fillOpacity = 1;
chart7_range2.axisFill.fill = colorSet.getIndex(4);
chart7_range2.axisFill.zIndex = -1;

var hand7 = chart7.hands.push(new am4charts.ClockHand());

// using chart7.setTimeout method as the timeout will be disposed together with a chart7
chart7.setTimeout(Value_CO, 2000);

/* --- new ---- */
var chart8 = am4core.create("chartdiv8", am4charts.GaugeChart);
chart8.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart8.innerRadius = -25;

var axis8 = chart8.xAxes.push(new am4charts.ValueAxis());
axis8.min = 0;
axis8.max = 100;
axis8.strictMinMax = true;
axis8.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis8.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart8_range0 = axis8.axisRanges.create();
chart8_range0.value = 0;
chart8_range0.endValue = 50;
chart8_range0.axisFill.fillOpacity = 1;
chart8_range0.axisFill.fill = colorSet.getIndex(0);
chart8_range0.axisFill.zIndex = - 1;

var chart8_range1 = axis8.axisRanges.create();
chart8_range1.value = 50;
chart8_range1.endValue = 80;
chart8_range1.axisFill.fillOpacity = 1;
chart8_range1.axisFill.fill = colorSet.getIndex(2);
chart8_range1.axisFill.zIndex = -1;

var chart8_range2 = axis8.axisRanges.create();
chart8_range2.value = 80;
chart8_range2.endValue = 100;
chart8_range2.axisFill.fillOpacity = 1;
chart8_range2.axisFill.fill = colorSet.getIndex(4);
chart8_range2.axisFill.zIndex = -1;

var hand8 = chart8.hands.push(new am4charts.ClockHand());

// using chart8.setTimeout method as the timeout will be disposed together with a chart8
chart8.setTimeout(Value_SO2, 2000);

/* --- new ---- */
var chart9 = am4core.create("chartdiv9", am4charts.GaugeChart);
chart9.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart9.innerRadius = -25;

var axis9 = chart9.xAxes.push(new am4charts.ValueAxis());
axis9.min = 0;
axis9.max = 100;
axis9.strictMinMax = true;
axis9.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis9.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart9_range0 = axis9.axisRanges.create();
chart9_range0.value = 0;
chart9_range0.endValue = 50;
chart9_range0.axisFill.fillOpacity = 1;
chart9_range0.axisFill.fill = colorSet.getIndex(0);
chart9_range0.axisFill.zIndex = - 1;

var chart9_range1 = axis9.axisRanges.create();
chart9_range1.value = 50;
chart9_range1.endValue = 80;
chart9_range1.axisFill.fillOpacity = 1;
chart9_range1.axisFill.fill = colorSet.getIndex(2);
chart9_range1.axisFill.zIndex = -1;

var chart9_range2 = axis9.axisRanges.create();
chart9_range2.value = 80;
chart9_range2.endValue = 100;
chart9_range2.axisFill.fillOpacity = 1;
chart9_range2.axisFill.fill = colorSet.getIndex(4);
chart9_range2.axisFill.zIndex = -1;

var hand9 = chart9.hands.push(new am4charts.ClockHand());

// using chart9.setTimeout method as the timeout will be disposed together with a chart9
chart9.setTimeout(Value_NO2, 2000);

/* --- new ---- */
var chart10 = am4core.create("chartdiv10", am4charts.GaugeChart);
chart10.hiddenState.properties.opacity = 0; // this makes initial fade in effect

chart10.innerRadius = -25;

var axis10 = chart10.xAxes.push(new am4charts.ValueAxis());
axis10.min = 0;
axis10.max = 100;
axis10.strictMinMax = true;
axis10.renderer.grid.template.stroke = new am4core.InterfaceColorSet().getFor("background");
axis10.renderer.grid.template.strokeOpacity = 0.3;

var colorSet = new am4core.ColorSet();

var chart10_range0 = axis10.axisRanges.create();
chart10_range0.value = 0;
chart10_range0.endValue = 50;
chart10_range0.axisFill.fillOpacity = 1;
chart10_range0.axisFill.fill = colorSet.getIndex(0);
chart10_range0.axisFill.zIndex = - 1;

var chart10_range1 = axis10.axisRanges.create();
chart10_range1.value = 50;
chart10_range1.endValue = 80;
chart10_range1.axisFill.fillOpacity = 1;
chart10_range1.axisFill.fill = colorSet.getIndex(2);
chart10_range1.axisFill.zIndex = -1;

var chart10_range2 = axis10.axisRanges.create();
chart10_range2.value = 80;
chart10_range2.endValue = 100;
chart10_range2.axisFill.fillOpacity = 1;
chart10_range2.axisFill.fill = colorSet.getIndex(4);
chart10_range2.axisFill.zIndex = -1;

var hand10 = chart10.hands.push(new am4charts.ClockHand());

// using chart10.setTimeout method as the timeout will be disposed together with a chart10
chart10.setTimeout(Value_Pres, 2000);

function Value_PM1_0() {
    hand.showValue(55, 1000, am4core.ease.cubicOut);
    chart.setTimeout(Value_PM1_0, 2000);
}
function Value_PM2_5() {
    hand1.showValue(55, 1000, am4core.ease.cubicOut);
    chart1.setTimeout(Value_PM2_5, 2000);
}
function Value_PM4_0() {
    hand2.showValue(30, 1000, am4core.ease.cubicOut);
    chart2.setTimeout(Value_PM4_0, 2000);
}
function Value_PM10() {
    hand3.showValue(55, 1000, am4core.ease.cubicOut);
    chart3.setTimeout(Value_PM10, 2000);
}
function Value_TEMP() {
    hand4.showValue(55, 1000, am4core.ease.cubicOut);
    chart4.setTimeout(Value_TEMP, 2000);
}
function Value_HUM() {
    hand5.showValue(55, 1000, am4core.ease.cubicOut);
    chart5.setTimeout(Value_HUM, 2000);
}
function Value_O3() {
    hand6.showValue(55, 1000, am4core.ease.cubicOut);
    chart6.setTimeout(Value_O3, 2000);
}
function Value_CO() {
    hand7.showValue(55, 1000, am4core.ease.cubicOut);
    chart7.setTimeout(Value_CO, 2000);
}
function Value_SO2() {
    hand8.showValue(55, 1000, am4core.ease.cubicOut);
    chart8.setTimeout(Value_SO2, 2000);
}
function Value_NO2() {
    hand9.showValue(55, 1000, am4core.ease.cubicOut);
    chart9.setTimeout(Value_NO2, 2000);
}
function Value_Pres() {
    hand10.showValue(55, 1000, am4core.ease.cubicOut);
    chart10.setTimeout(Value_Pres, 2000);
}
