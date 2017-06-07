import processing.serial.*;
Serial port;

//temperature value from Serial
String temp = "";
//complete string from Serial
String data = "";
//humididty value from Serial
String humidity = "";
//which value to update
boolean onTemp = true;
//graphic font
PFont font;

void setup(){
    //get processing to listen to the right port
    String portName = Serial.list()[1];
    port = new Serial(this, portName, 9600);
    
    size (450, 125);
    port.bufferUntil('\n');
    font = loadFont("ColonnaMT-48.vlw");
    textFont(font);
}

void draw(){
    background(0, 0, 0);
    fill(0, 100, 150);
    text(temp, 10, 50);
    fill(150, 100, 0);
    text(humidity, 10, 100);
}

void serialEvent(Serial port){
      data = port.readStringUntil('\n');
      if(onTemp)
         temp = data; 
      else
         humidity = data;
      onTemp = !onTemp;
}