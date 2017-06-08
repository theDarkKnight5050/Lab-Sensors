import processing.serial.*;
import javax.swing.JOptionPane;
import org.gicentre.utils.stat.*;

Serial myPort;

ArrayList<Float> xData = new ArrayList<Float>();

XYChart tempLineChart;
ArrayList<Float> tempData = new ArrayList<Float>();

XYChart humidityLineChart;
ArrayList<Float> humidityData = new ArrayList<Float>();

int tempLowerBound = 0;
int tempUpperBound = 0;

int time;
int scope;
int currTime;

void setup() {
  size(500, 200);
    
  myPort = new Serial(this, Serial.list()[1], 9600);
  myPort.bufferUntil('%');
  
  textFont(createFont("Arial", 10), 10);
  tempLineChart = new XYChart(this);
  tempLineChart.showXAxis(true);
  tempLineChart.showYAxis(true);
  humidityLineChart = new XYChart(this);
  humidityLineChart.showXAxis(false);
  humidityLineChart.showYAxis(true);

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
  
  try {
      time = Integer.parseInt(JOptionPane.showInputDialog("Length between measurements (in seconds)"));
      scope = Integer.parseInt(JOptionPane.showInputDialog("Scope"));
  }
  catch(Exception e) {
      if (time == JOptionPane.CANCEL_OPTION)
        System.exit(0);
  }
  
  tempLineChart.setMinY(tempLowerBound);
  tempLineChart.setMaxY(tempUpperBound);
  tempLineChart.setYFormat("#.## *C");
  tempLineChart.setXFormat("# s");
  tempLineChart.setMinX(0);
  tempLineChart.setMaxX(scope);
  
  humidityLineChart.setMinY(0);
  humidityLineChart.setMaxY(100);
  humidityLineChart.setYFormat("#.## %"); 
  
  tempLineChart.setPointColour(color(180, 50, 50, 100));
  tempLineChart.setPointSize(5);
  tempLineChart.setLineWidth(2);
  
  humidityLineChart.setPointColour(color(120, 210, 240));
  humidityLineChart.setPointSize(5);
  humidityLineChart.setLineWidth(2);
  
  background(255);
}

void draw() {  
  textSize(9);
  update();
  
  fill(120);
  textSize(20);
  text("Temperature and Humidity Data", 70, 30);
}

void update()  {
  if(xData.size() == 0 || time > scope){
    xData = new ArrayList<Float>();
    tempData = new ArrayList<Float>();
    xData = new ArrayList<Float>();
    humidityData = new ArrayList<Float>();
  }
  
  tempLineChart.setData(toArray(xData), toArray(tempData));
  tempLineChart.updateLayout();
  tempLineChart.draw(15, 15, width - 30, height - 30);
  
  humidityLineChart.setData(toArray(xData), toArray(humidityData));
  humidityLineChart.updateLayout();
  humidityLineChart.draw(15, 15, width - 30, height - 30);
}

float[] toArray(ArrayList<Float> floatList)  {
   int i = 0;
   float[] floatArray = new float[floatList.size()];
   for(Float f : floatList)  
     floatArray[i++] = (f != null ? f : Float.NaN);
   return floatArray;
}

void serialEvent(Serial myPort) {  
  String inString = myPort.readStringUntil('%'); 
  int index = inString.indexOf('\n'); 
  
  tempData.add(Float.parseFloat(inString.substring(0, index)));
  xData.add((float)currTime);
  
  humidityData.add(Float.parseFloat(inString.substring(index + 1)));
  xData.add((float)currTime);
  
  delay(1000 * time);
  currTime += time;
}