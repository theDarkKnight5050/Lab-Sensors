import processing.serial.*;
import javax.swing.JOptionPane;

Serial myPort;
int xPos = 1;
float inByte = 0;
int lowerBound;
int upperBound;
int time;

void setup(){
   size(400, 300);
   myPort = new Serial(this, Serial.list()[1], 9600);
   myPort.bufferUntil('\n');
   
   while(!(upperBound > lowerBound)){
     try{    
       lowerBound = Integer.parseInt(JOptionPane.showInputDialog("Lower Bound"));
       upperBound = Integer.parseInt(JOptionPane.showInputDialog("Upper Bound"));
     }
     catch(Exception e){
       if(lowerBound == JOptionPane.CANCEL_OPTION || upperBound == JOptionPane.CANCEL_OPTION)
         System.exit(0);
       JOptionPane.showMessageDialog(null, "Try Again", "Alert", JOptionPane.ERROR_MESSAGE);
     }
     try{
       time = Integer.parseInt(JOptionPane.showInputDialog("Length of cycle (in seconds)"));
     }
     catch(Exception e){
       if(time == JOptionPane.CANCEL_OPTION)
         System.exit(0);
     }
   }
   background(0);
   
}

void draw(){
   stroke(127, 34, 255);
   line(xPos, height, xPos, height - inByte);
   
   if(xPos >= width){
      xPos = 0;
      background(0);
   }
   else{
      xPos++; 
   }
   delay(10000);
}

void serialEvent(Serial myPort){
   String inString = myPort.readStringUntil('\n');
   
   if(inString != null){
      int index = inString.indexOf(" ");
      inString = inString.substring(index + 1);
      index = inString.indexOf("*");
      inString = inString.substring(0, index);
      inByte = float(inString);
      println(inByte);
      inByte = map(inByte, lowerBound, upperBound, 0, height);
   }
}