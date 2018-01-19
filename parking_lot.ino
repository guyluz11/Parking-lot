


int infraPinOne = 0 ; // analog pin, infra read led reader  pin number
int gatePinOne = 1; // analog pin, if gate pin eqels 0 the gate is close and if 1 the gate is open
int motorOneU = 12;  //  digital pin of the motor 
int motorOneD = 13;  // digital pin of the motor
bool gateOneIsOpenOrClose = false;  // no pin,  0 is closed gate 1 is open gate

bool toEnterOne1 = false;
bool toEnterOne2 = false;
bool closeNowOne = false;
unsigned long lastMiliOne = 0;



int infraPinTwo = 2 ; // analog pin, infra read led reader  pin number
int gatePinTwo = 3; // analog pin, if gate pin eqels 0 the gate is close and if 1 the gate is open
int motorTwoU = 10;  //  digital pin of the motor 
int motorTwoD = 11;  // digital pin of the motor
bool gateTwoIsOpenOrClose = false;  // no pin,  0 is closed gate 1 is open gate

bool toEnterTwo1 = false;
bool toEnterTwo2 = false;
bool closeNowTwo = false;
unsigned long lastMiliTwo = 0;



void setup() {  
  Serial.begin(9600); 
  pinMode(infraPinOne, INPUT);
  pinMode(gatePinOne, INPUT);
  pinMode(motorOneU, OUTPUT); 
  pinMode(motorOneD, OUTPUT); 

  
   
  pinMode(infraPinTwo, INPUT);
  pinMode(gatePinTwo, INPUT);
  pinMode(motorTwoU, OUTPUT); 
  pinMode(motorTwoD, OUTPUT);

}



void loop() {

  
  allOperationsForSection(infraPinTwo, gatePinTwo, motorTwoU, motorTwoD, gateTwoIsOpenOrClose, toEnterTwo1, toEnterTwo2,  closeNowTwo, lastMiliTwo);

  allOperationsForSection(infraPinOne, gatePinOne, motorOneU, motorOneD, gateOneIsOpenOrClose, toEnterOne1, toEnterOne2,  closeNowOne, lastMiliOne);


}


void allOperationsForSection(int infraPin, int gatePin, int motorU, int motorD, bool &gateIsOpenOrClose, bool &toEnter1, bool &toEnter2, bool &closeNow, unsigned long &lastMili){
  if(toEnter2){
    if(millis()-lastMili >= 6000){  //  Delaty time to close the gate after opening
      Serial.println("close the gate");
      toEnter2 = false;
      toEnter1 = false;
      closeNow = false;
    }  
  }
  else if(toEnter1){ 
      Serial.println("motor onnnnn");
      digitalWrite(motorU, HIGH); 
  
      if(!switchF(gatePin)){  //  if the swich is open 
        gateIsOpenOrClose = true;
        Serial.println("the gate is now open and can rest in peac");
        digitalWrite(motorU, LOW);
        toEnter2 = true;
        lastMili = millis();        
      }
    
  }
  else if (closeNow){
    Serial.println("Are you stack?");
    if(isObjectInTheSensor(infraPin)){
      digitalWrite(motorD, LOW);
      closeNow = false;
      toEnter1 = true;
    }
    if(!switchF(gatePin)){  //  if the swich is open 
      digitalWrite(motorD, LOW);
      gateIsOpenOrClose = false;
      Serial.println("the gates of havan are now close");
      closeNow = false;
    }
          
  }
   else if(isObjectInTheSensor(infraPin)){  // enters if thare is object in the sensor and the gate is not open
          if (!gateIsOpenOrClose) {  // if the gate is open do not open it more
            toEnter1 = true;
          }
          else{
            Serial.println("gate is open alredy");
          }
      }
    else{
      if(gateIsOpenOrClose) {  //  if the gate close do not close it more
        gateIsOpenOrClose = false;
        digitalWrite(motorD, HIGH);
        closeNow = true;
      }
      else{
        Serial.println("gate is close alredy so stop traying boy");
      }
    } 
}




bool isObjectInTheSensor(int infraPin){
   Serial.println(" switchF info " + (String) analogRead(infraPin)); 
  return analogRead(infraPin) > 700;
}


bool switchF(int gatePin){    //  return 0 if the gate is prased and 1 if the gate is not preasd 
  return analogRead(gatePin) > 500;
}
