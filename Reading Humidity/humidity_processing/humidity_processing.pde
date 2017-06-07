import processing.serial.*;
Serial port;

String humidity = "";
PFont font;

void setup(){
    String portName = Serial.list()[1];
    port = new Serial(this, portName, 9600);
    size (400, 100);
    
    port.bufferUntil('\n');
    font = loadFont("ColonnaMT-48.vlw");
    textFont(font);
}

void draw(){
    background(0, 0, 0);
    fill(0, 100, 150);
    text(humidity, 10, 50);
}

void serialEvent(Serial port){
      humidity = port.readStringUntil('\n');
}