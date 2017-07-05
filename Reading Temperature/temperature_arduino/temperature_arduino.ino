/**
 * Plots temperature using a thermistor
 * 
 * @name Ahmed Abdalla
 * @mentor Jill Burnham
 * @date 6-6-2017
 * 
 * Special thanks to Lady Ada at adafruit
 */

//value of set resistor
#define SERIESRESISTOR 99650
//thermistor pin
#define THERMISTORPIN A0
//resistor constants
#define ACOEFFICIENT 0.0009376ZA
#define BCOEFFICIENT 0.0002208
#define CCOEFFICIENT 0.0000001276
//room temperature
#define ROOMTEMP 298.15
//thermistor resistance at ROOMTEMP
#define THERMISTORNORMAL 30000

int NUMAVERAGE = 5;

void setup() {
  Serial.begin(9600);
  analogReference(EXTERNAL);
  Serial.println("Initializing...");
}

void loop() {
  //thermistor reading as interpreted by board
  float reading;

  for(int i = 0; i < NUMAVERAGE; i++){
    reading += analogRead(THERMISTORPIN);
    delay(500);
  }
  reading = reading/NUMAVERAGE;
  
  Serial.print("Average Analog reading: ");
  Serial.println(reading);
  
  reading = (1023 / reading) - 1;
  reading = SERIESRESISTOR / reading;
  Serial.print("Thermistor resistance: ");
  Serial.println(reading);

  float temperature;
  temperature = ACOEFFICIENT + BCOEFFICIENT * log(reading) + CCOEFFICIENT * pow(log(reading), 3);
  temperature = 1.0/temperature - 273.15;

  Serial.print("Temperature: ");
  Serial.println(temperature);
  Serial.println("*C");
  
  delay(500);
}


