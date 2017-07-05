/**
 * Plots humidity using a humdity sensor
 * 
 * @name Ahmed Abdalla
 * @mentor Jill Burnham
 * @date 6-6-2016
 */
//proportionality constant from humidity to voltage
#define RHtoVCONSTANT 46
//humdity pin
#define HUMIDITYPIN A1
#define MAXOUTPUTVOLTAGE 5.0
//number of values to average over 1 second
int NUMAVERAGE = 5;

void setup() {
  Serial.begin(9600);
  Serial.println("Initializing...");
}

void loop() {
  //humidity reading as interperted by the board
  float reading;

  for(int i = 0; i < NUMAVERAGE; i++){
    reading += analogRead(HUMIDITYPIN);
    delay(1000);
  }
  reading = reading/NUMAVERAGE;
  reading = reading * MAXOUTPUTVOLTAGE/1023;
  
  Serial.print("Analog Reading: ");
  Serial.println(reading);
    
  reading = reading * RHtoVCONSTANT - 23; 
    
  Serial.print("Humidity: ");
  Serial.print(reading);
  Serial.println("%");
}
