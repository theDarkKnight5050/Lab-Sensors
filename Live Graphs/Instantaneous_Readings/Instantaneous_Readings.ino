/**
 * Gathers and reports temperature and humidity data
 * 
 * @name Ahmed Abdalla
 * @mentor Jill Burnham
 * @date 6-9-2017
 */

//number of analog values taken before each measurement is calculated
int NUMAVERAGE = 5;

/**
 * YSI 44008 Thermistor
 */
class TemperatureReader{
  /**
   * For some reason SERIESRESISTOR is changing with input voltage.
   * Get a new resistor from home or something.
   */
  //value of set resistor at 5V
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
        delay(100);
      }
      reading = reading/NUMAVERAGE;     
      reading = (1023 / reading) - 1;
      reading = SERIESRESISTOR / reading;
    
      float temperature;
      temperature = ACOEFFICIENT + BCOEFFICIENT * log(reading) + CCOEFFICIENT * pow(log(reading), 3);
      temperature = 1.0/temperature - 273.15;
    
      Serial.print(temperature);
      Serial.println("*C");
     }
};
  

/**
 * HIH-5030/5031 humidity sensor
 */
 class HumidityReader{
  //proportionality constant from humidity to voltage
  #define RHtoVCONSTANT 48
  //humdity pin
  #define HUMIDITYPIN A1
  //max voltage of power source
  #define MAXOUTPUTVOLTAGE 3.3
  public:
    void getHumidity(){
      //humidity reading as interperted by the board
      float reading;
    
      for(int i = 0; i < NUMAVERAGE; i++){
        reading = analogRead(HUMIDITYPIN);
        reading = reading/1023 * MAXOUTPUTVOLTAGE;
    
        delay(100);
      }
      reading = reading * RHtoVCONSTANT - 24; 
        
      Serial.print(reading);
      Serial.println('%');
    }
};

TemperatureReader *temp;
HumidityReader *hum;
void setup() {
  Serial.begin(9600);
}

void loop() {
  temp->getTemperature();
  hum->getHumidity();
}


