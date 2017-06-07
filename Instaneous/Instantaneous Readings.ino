//number of analog values taken before each measurement is calculated
int NUMAVERAGE = 5;

class TemperatureReader{
  //value of set resistor
  #define SERIESRESISTOR 170000
  //thermistor pin
  #define THERMISTORPIN A0
  //resistor constants
  #define ACOEFFICIENT 0.0009376
  #define BCOEFFICIENT 0.0002208
  #define CCOEFFICIENT 0.0000001276
  //room temperature
  #define ROOMTEMP 298.15
  //thermistor resistance at ROOMTEMP
  #define THERMISTORNORMAL 30000

  public:
     void getTemperature(){
    //thermistor reading as interpreted by board
      float reading;
    
      for(int i = 0; i < NUMAVERAGE; i++){
        reading += analogRead(THERMISTORPIN);
        delay(250);
      }
      reading = reading/NUMAVERAGE;     
      reading = (1023 / reading) - 1;
      reading = SERIESRESISTOR / reading;
    
      float temperature;
      temperature = ACOEFFICIENT + BCOEFFICIENT * log(reading) + CCOEFFICIENT * pow(log(reading), 3);
      temperature = 1.0/temperature - 273.15;
    
      Serial.print("Temperature: ");
      Serial.print(temperature);
      Serial.println("*C");
     }
};
  

class HumidityReader{
  //voltage through humdity sensor
  #define INPUTVOLTAGE 3.3
  //proportionality constant from humidity to voltage
  #define RHtoVCONSTANT 48
  //humdity pin
  #define HUMIDITYPIN A1
  //number of values to average over 1 second
  #define MINOUTPUTVOLTAGE 0.5
  #define MAXOUTPUTVOLTAGE 3.3
  public:
    void getHumidity(){
      //humidity reading as interperted by the board
      float reading;
    
      for(int i = 0; i < NUMAVERAGE; i++){
        reading = analogRead(HUMIDITYPIN);
        reading = reading/1023 * MAXOUTPUTVOLTAGE;
    
        delay(250);
      }
      reading = reading * RHtoVCONSTANT - 24; 
        
      Serial.print("Humidity: ");
      Serial.print(reading);
      Serial.println("%");
    }
};

TemperatureReader *temp;
HumidityReader *hum;
void setup() {
  Serial.begin(9600);
}

void loop() {
  temp->getTemperature();
  delay(2000);
  hum->getHumidity();
  delay(2000);
}


