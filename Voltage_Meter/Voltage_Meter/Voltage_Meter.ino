double voltage;
double current;
boolean on;


/**
 * C = Control
 * V = Voltage
 * I = Current
 * R = Resistance
 * _ = with
 */
int CV_V = 3;
int CV_R = 5;
int CI_V = 6;
int CI_R = 9;
int ON = 10;

String inString;

void setup() {
  Serial.begin(9600);
  Serial.println("Input voltage from 0-17.5V");

  pinMode(CV_V, OUTPUT);
  pinMode(CI_V, OUTPUT);
  pinMode(ON, OUTPUT);
}

void loop() {
  if(Serial.available() > 0){
    inString = Serial.read();
    String check = inString.substring(0, 8);
    
    switch(hash(inString)){
      case hash("Voltage") : 
        updateVoltage(inString); 
        break;
      case hash("Current") : 
        updateCurrent(inString); 
        break;
      case hash("On/Off:") : 
        updateOn(inString); 
        break;
      default : 
        Serial.print("Invalid Serial Input");
    }
  }

  Serial.print("Voltage: ");
  Serial.println(voltage);
  
  Serial.print("Current: ");
  Serial.println(current);
  
  Serial.print("On/Off: ");
  Serial.println(on);

  delay(1000);
}

void updateVoltage(String in){
  String in = in.substring(9);
  voltage = std::stod(in); 
  analogWrite(CV_V, map(voltage, 0, 18, 0, 255));
}

void updateCurrent(String in){
  String in = in.substring(9);
  current = std::stod(in);
  analogWrite(CI_V, map(current, 0, 1, 0, 255));
}

void updateOn(String in){
  String in = in.substring(8);
  
  if(in == "ON"){
    on = true;
    analogWrite(ON, HIGH);
  }
  else{
    if(in = "OFF"){
      on = false;
      analogWrite(ON, LOW);
    }
    else{
      Serial.print("Invalid On/Off Input");
    }
  }
}

int hash (String word)   
{       int sum = 0;
        for (int k = 0; k < word.length(); k++)
            sum = sum + int(word[k]);
        return  sum % SIZE; 
}
