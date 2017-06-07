/**
 * Plots humidity using a humdity sensor
 * 
 * @name Ahmed Abdalla
 * @mentor Jill Burnham
 * @date 6-6-2016
 */
 
//voltage through humdity sensor
#define INPUTVOLTAGE 3.3
//proportionality constant from humidity to voltage
#define RHtoVCONSTANT 48
//humdity pin
#define HUMIDITYPIN A1
#define MINOUTPUTVOLTAGE 0.5
#define MAXOUTPUTVOLTAGE 3.3
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
    reading = analogRead(HUMIDITYPIN);
    reading = reading/1023 * MAXOUTPUTVOLTAGE;

    delay(500);
  }
     
  Serial.print("Analog Reading: ");
  Serial.println(reading);
    
  reading = reading * RHtoVCONSTANT - 24; 
    
  Serial.print("Humidity: ");
  Serial.print(reading);
  Serial.println("%");
}
