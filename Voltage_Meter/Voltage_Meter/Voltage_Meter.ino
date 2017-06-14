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

double inDouble;
int check;
int digit;
boolean decimal;

double data;

void setup()  {
  Serial.begin(9600);

  //establishContact();

  pinMode(CV_V, OUTPUT);
  pinMode(CI_V, OUTPUT);
  pinMode(ON, OUTPUT);
}

void loop() {
  if(Serial.available())  {
    inDouble = Serial.read();
    
    while(!(inDouble = 10)){
      if(inDouble > 64)
        check = inDouble;
      if(48 <= inDouble <= 57){
        inDouble = inDouble - 48;
        if(decimal)
          data = inDouble * pow(10, digit * (-1)) + data;
        else{
          if(digit == 0)
            data = inDouble + data;
          else
            data = inDouble * 10 + data;
        }
      }
      if(inDouble == 46)
        decimal = true;
    }
    
    decimal = false;
    
    Serial.print("Received: ");
    Serial.println(data);
    
    switch(check)  {
      case 86 : 
        updateVoltage(data); 
        break;
      case 67 : 
        updateCurrent(data); 
        break;
      case 79 : 
        updateOn(data); 
        break;
      default : 
        Serial.println("Invalid Serial Input");
    }
  }

  delay(1000);
}

void updateVoltage(double data) {
  voltage = data;
  analogWrite(CV_V, map(voltage, 0, 18, 0, 255));
  
  Serial.print("Voltage: ");
  Serial.println(voltage);
}

void updateCurrent(double data) {
  current = data;
  analogWrite(CI_V, map(current, 0, 1, 0, 255));
  
  Serial.print("Current: ");
  Serial.println(current);
}

void updateOn(double data)  {
  if(data == 0)  {
    on = false;
    analogWrite(ON, LOW);
  }
  else  {
    if(data == 1){
      on = true;
      analogWrite(ON, HIGH);
    }
    else  {
      Serial.print("Invalid On/Off Input");
    }
  }

  Serial.print("On/Off: ");
  Serial.println(on);
}

void establishContact() {
  while(Serial.available() <= 0)  {
    Serial.println("A");
    delay(300);
  }
}
