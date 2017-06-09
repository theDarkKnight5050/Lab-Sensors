import processing.serial.*; //<>// //<>//
import javax.swing.JOptionPane;
import org.gicentre.utils.stat.*;

/**
 Graphs arduino temperature and humidity data as double line graph
 
 @name Ahmed Abdalla
 @mentor Jill Burnham
 @date 6-9-2017
 */

//COM3 with incoming arduino data
Serial myPort;

//keeps track of time
ArrayList<Float> xData = new ArrayList<Float>();

//Creates temperature line chart and arraylist
XYChart tempLineChart;
ArrayList<Float> tempData = new ArrayList<Float>();

//Creates humidity line chart and arraylist
XYChart humidityLineChart;
ArrayList<Float> humidityData = new ArrayList<Float>();

//bounds for temperature scale
int tempLowerBound = 0;
int tempUpperBound = 0;

//keep track of time increment, max time, and current time
int time;
int scope;
int currTime;

//data received from port
String inString;
int index;
//int i = 0;

/**
 Sets up initial graphs with correct axes data, scale, etc...
 */
void setup() {
  //screen size
  size(1000, 400);

  //sets the port and tells it how to cut up data (using %)
  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.bufferUntil('%');

  //creates charts and sets axes
  textFont(createFont("Arial", 10), 10);
  tempLineChart = new XYChart(this);
  tempLineChart.showXAxis(true);
  tempLineChart.showYAxis(true);
  humidityLineChart = new XYChart(this);
  humidityLineChart.showXAxis(false);
  humidityLineChart.showYAxis(true);

  //forces users to use sensical temperature bounds
  while (!(tempUpperBound > tempLowerBound)) {
    try {    
      tempLowerBound = Integer.parseInt(JOptionPane.showInputDialog("Temperature Lower Bound"));
      tempUpperBound = Integer.parseInt(JOptionPane.showInputDialog("Temperature Upper Bound"));
    }
    catch(Exception e) {
      if (tempLowerBound == JOptionPane.CANCEL_OPTION || tempUpperBound == JOptionPane.CANCEL_OPTION)
        System.exit(0);
      JOptionPane.showMessageDialog(null, "Try Again", "Alert", JOptionPane.ERROR_MESSAGE);
    }
  }

  //forces users to use sensical time increments and max times
  try {
    time = Integer.parseInt(JOptionPane.showInputDialog("Length between measurements (in seconds)"));
    scope = Integer.parseInt(JOptionPane.showInputDialog("Scope"));
  }
  catch(Exception e) {
    if (time == JOptionPane.CANCEL_OPTION)
      System.exit(0);
  }

  //formatting for temperature line chart
  tempLineChart.setMinY(tempLowerBound);
  tempLineChart.setMaxY(tempUpperBound);
  tempLineChart.setYFormat("#.## *C");
  tempLineChart.setXFormat("# s");
  tempLineChart.setMinX(0);
  tempLineChart.setMaxX(scope);
  tempLineChart.setPointColour(color(180, 50, 50, 100));
  tempLineChart.setPointSize(1);
  tempLineChart.setLineWidth(1);

  //formatting for humidity line chart
  humidityLineChart.setMinY(0);
  humidityLineChart.setMaxY(100);
  humidityLineChart.setYFormat("");
  humidityLineChart.setYAxisAt(scope);
  humidityLineChart.setMinX(0);
  humidityLineChart.setMaxX(scope);  
  humidityLineChart.setPointColour(color(120, 210, 240));
  humidityLineChart.setPointSize(1);
  humidityLineChart.setLineWidth(1);

  background(255);
}

void draw() {  
  textSize(9);
  update();

  fill(120);
  textSize(20);
  text("Temperature and Humidity Data", 70, 30);
    
  //println(xData.get(i));
  //println(tempData.get(i));
  //println(humidityData.get(i++));
}

/**
 Updates the graph using serialEvent() data
 */
void update() {
  //adds new data points to each arraylist
  tempData.add(Float.parseFloat(inString.substring(0, index)));  
  humidityData.add(Float.parseFloat(inString.substring(index + 2, inString.length() - 3)));
  xData.add((float)currTime);

  //checks if current time is greater than max time in order to reset graph
  if (xData.size() == 0 || currTime > scope) {
    xData = new ArrayList<Float>();
    tempData = new ArrayList<Float>();
    humidityData = new ArrayList<Float>();
    
    currTime = 0;
  }

  //sets and draws temperature data
  tempLineChart.setData(toArray(xData), toArray(tempData));
  tempLineChart.updateLayout();
  tempLineChart.draw(15, 15, width - 30, height - 30);

  //sets and draws humidity data
  humidityLineChart.setData(toArray(xData), toArray(humidityData));
  humidityLineChart.updateLayout();
  humidityLineChart.draw(8, 15, width - 30, height - 30);
}

/**
 Stores data from arduino
 */
void serialEvent(Serial myPort) {  
  //safely handles initialization exception
  try {
    inString = myPort.readStringUntil('%'); 
    index = inString.indexOf('*');     
    System.out.println(inString);
    
    delay(1000 * time);
    currTime += time;
    println(currTime);
  }
  catch(Exception e) {
    e.printStackTrace();
  }
}

/**
 converts ArrayList<Float> into float[] not Object[] because float can't be cast to object
 */
float[] toArray(ArrayList<Float> floatList) {
  int i = 0;
  float[] floatArray = new float[floatList.size()];
  for (Float f : floatList)  
    floatArray[i++] = (f != null ? f : Float.NaN);
  return floatArray;
}