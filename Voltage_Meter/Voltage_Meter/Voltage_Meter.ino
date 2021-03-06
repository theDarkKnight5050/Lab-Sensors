/*
 * Controls PMC35-1A Regulated DC Power Supply
 * 
 * @name Ahmed Abdalla
 * @mentor Jill Burnham
 * @date 6-16-2017
 */

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

//Incoming information from GUI
String inString;
//Quantitaive (ie: # of volts, # of amps, on/off)
String data = "";
//Qualitative (ie: Voltage, Current, On)
char check = 'N';

/**
 * Establishes connectoin and relevant pins
 */
void setup()  {
  Serial.begin(9600);

  establishContact();

  pinMode(CV_V, OUTPUT);
  pinMode(CI_V, OUTPUT);
  pinMode(ON, OUTPUT);

  //Because OFF has precedence, connecting pins turns OUTPUT OFF
  digitalWrite(ON, HIGH);
}

/**
 * Recieves, parses, and sends data
 */
void loop() {
  //Reads incoming data into inString
  while (Serial.available())  {
    if (Serial.available() > 0) {
      char c = Serial.read();
      inString += c;
    }
  }

  //Decides how to handle information
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
      case 'A' :
        Serial.println("Contact");
        reset();
        break;
      default :
        Serial.println("Invalid Serial Input");
        reset();
        break;
    }
  }
  
  delay(1000);
}

/**
 * Helps discern if contact with GUI has been established
 */
void establishContact() {
  while (Serial.available() <= 0)  {
    Serial.println("A");
    delay(1000);
  }
}


/**
 * Resets variables after Power Supply set.
 * CAUTION: Without this enters infinite loops
 */
void reset(){
  check = 'N';
  data = "";
  inString = "";
}

/**
 * Changes PSU voltage
 */
void updateVoltage(double data) {
  analogWrite(CV_V, LOW);
  analogWrite(CV_V, data * 255/17.5);

  Serial.print("Voltage: ");
  Serial.println(data);
}

/**
 * Changes PSU current
 */
void updateCurrent(double data) {
  analogWrite(CI_V, data * 255/0.5);

  Serial.print("Current: ");
  Serial.println(data);
}

/**
 * Controls PSU OUTPUT status
 */
void updateOn(String data)  {
  //removes line break character
  data = data.substring(0, 4);

  //Because OFF has precedence, disconnecting pins turns OUTPUT ON
  if (data.equals("true"))  {
    digitalWrite(ON, LOW);
    Serial.print("On/Off: ON");
  }
  else  {
    if (data.equals("fals")) {
      digitalWrite(ON, HIGH);
      Serial.print("On/Off: OFF");
    }
    else  {
      Serial.println("Invalid On/Off Input");
    }
  }
}
