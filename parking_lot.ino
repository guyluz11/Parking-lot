
#include <Metro.h>

Metro firstSection = Metro(500);
Metro secondSection = Metro(500);



unsigned long lastMiliFirstSection = 0;
unsigned long lastMiliSecondSection = 0;

const long interval = 1000;  //  Delaty time to close the gate after opening





int infraPinOne = 0 ; // analog pin, infra read led reader  pin number
int gatePinOne = 1; // analog pin, if gate pin eqels 0 the gate is close and if 1 the gate is open
int motorOneU = 2;  //  digital pin of the motor 
int motorOneD = 3;  // digital pin of the motor
int gateOneIsOpenOrClose = 0;  // no pin,  0 is closed gate 1 is open gate

int infraPinTwo = 2 ; // analog pin, infra read led reader  pin number
int gatePinTwo = 3; // analog pin, if gate pin eqels 0 the gate is close and if 1 the gate is open
int motorTwoU = 4;  //  digital pin of the motor 
int motorTwoD = 5;  // digital pin of the motor
int gateTwoIsOpenOrClose = 0;  // no pin,  0 is closed gate 1 is open gate



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
  
  if(firstSection.check()){
    if(isObjectInTheSensor(infraPinOne)){  // enters if thare is object in the sensor and the gate is not open
      openTheGate(gatePinOne, gateOneIsOpenOrClose, lastMiliFirstSection, motorOneU);  //open the gate
    }
    else{
      closeTheGate(gatePinOne, infraPinOne, gateOneIsOpenOrClose, lastMiliFirstSection, motorOneU, motorOneD);
    } 
  }


  if(secondSection.check()){
    if(isObjectInTheSensor(infraPinTwo)){  // enters if thare is object in the sensor and the gate is not open
      openTheGate(gatePinTwo, gateTwoIsOpenOrClose, lastMiliSecondSection, motorTwoU);  //open the gate
    }
    else{ 
    //thar isnot car the gate could be closed
      //  timer for closing gate 
      closeTheGate(gatePinTwo, infraPinTwo, gateTwoIsOpenOrClose, lastMiliSecondSection, motorTwoD, motorTwoU);
    }
  }

  
  
  //map(analogRead(infPin), 0, 5, 0, 1);
  
  Serial.println("");
  
 
  Serial.println("");
  
}










void openTheGate(int gatePin, int gateIsOpenOrClose, long lastMili, int motorU){ //  open the gate untill the swich is on

  if (!gateIsOpenOrClose) {  // if the gate is open do not open it more
    while(true){
      digitalWrite(motorU, HIGH); 
      if(!switchF(gatePin)){  //  if the swich is open 
        digitalWrite(motorU, LOW);
        gateIsOpenOrClose = 1;
        Serial.println("the gate is now open and can rest in peac");
        while(true){
          if(millis()-lastMili >= interval){
            return; // stop opening of the gate
          }
        }
      }
    }
  }
  else{
    Serial.println("gate is open alredy");
  }
}

void closeTheGate(int gatePin, int infraPin, int gateIsOpenOrClose, long lastMili, int motorD, int motorU){
  if(gateIsOpenOrClose) {  //  if the gate close do not close it more
    while(true){
      if(isObjectInTheSensor(infraPin)){
        digitalWrite(motorD, LOW);
        gateIsOpenOrClose = 0;
        openTheGate(gatePin, gateIsOpenOrClose, lastMili, motorU);
        return;
      }
      digitalWrite(motorD, HIGH);
      if(!switchF(gatePin)){  //  if the swich is open 
        digitalWrite(motorD, LOW);
        gateIsOpenOrClose = 0;
        Serial.println("the gates of havan are now close");
        return; // stop opening of the gate
      }
    }
  }
  else{
    Serial.println("gate is close alredy so stop traying boy");
  }
  //ufter timer is stop close the gate unless thare is object infront of the sensor
}

int isObjectInTheSensor(int infraPin){
  return analogRead(infraPin) > 700;
}

int switchF(int gatePin){    //  return 0 if the gate is prased and 1 if the gate is not preasd
  //Serial.println(" switchF info " + (String) analogRead(gatePin));  
  return analogRead(gatePin) > 900;
}
