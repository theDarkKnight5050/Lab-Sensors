import processing.serial.*;
Serial port;

String temp = "";
String data = "";
PFont font;

void setup(){
    String portName = Serial.list()[1];
    port = new Serial(this, portName, 9600);
    size (463, 100);
    
    port.bufferUntil('C');
    font = loadFont("ColonnaMT-48.vlw");
    textFont(font);
}

void draw(){
    background(0, 0, 0);
    fill(0, 100, 150);
    text(temp, 10, 50);
}

void serialEvent(Serial port){
      data = port.readStringUntil('C');
      int index = data.indexOf("Temperature");
      temp = data.substring(index);
}