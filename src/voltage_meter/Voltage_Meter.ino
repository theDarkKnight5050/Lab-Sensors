/**
   C = Control
   V = Voltage
   I = Current
   R = Resistance
   _ = with
*/
int CV_V = 3;
int CV_R = 5;
int CI_V = 6;
int CI_R = 9;
int ON = 10;

String inString;
String data = "";
char check = 'N';

void setup()  {
  Serial.begin(9600);

  establishContact();

  pinMode(CV_V, OUTPUT);
  pinMode(CI_V, OUTPUT);
  pinMode(ON, OUTPUT);
}

void loop() {
  while (Serial.available())  {
    if (Serial.available() > 0) {
      char c = Serial.read();
      inString += c;
    }
  }
  
  if (inString.length() > 0) {
    check = inString[0];
    data = inString.substring(1);

    switch (check)  {
      case 'V' :
        updateVoltage(atof(data.c_str()));
        reset();
        break;
      case 'C' :
        updateCurrent(atof(data.c_str()));
        reset();
        break;
      case 'O' :
        updateOn(data);
        reset();
        break;
      case 'N' :
        Serial.println("Waiting");        
        break;
      default :
        Serial.println("Invalid Serial Input");
        reset();
        break;
    }
  }
  
  delay(1000);
}

void establishContact() {
  while (Serial.available() <= 0)  {
    Serial.println("A");
    delay(1000);
  }
}

void reset(){
  check = 'N';
  data = "";
  inString = "";
}

void updateVoltage(double data) {
  data = map(data, 0, 17.5, 0, 255);
  analogWrite(CV_V, data);

  Serial.print("Voltage: ");
  Serial.println(data);
}

void updateCurrent(double data) {
  analogWrite(CI_V, data * 255/0.5);

  Serial.print("Current: ");
  Serial.println(data);
}

void updateOn(String data)  {
  data = data.substring(0, data.length() - 1);
  if (data.equals("true"))  {
    analogWrite(ON, HIGH);
  }
  else  {
    if (data.equals("false")) {
      analogWrite(ON, LOW);
    }
    else  {
      Serial.println("Invalid On/Off Input");
    }
  }

  Serial.print("On/Off: ");
  Serial.println(data);
}
