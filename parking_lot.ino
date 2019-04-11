// initial variables
int delayV = 6000; // No pin, set the delay between opening and closing a gate
int maxCars = 9; // No pin, set the maximum number of cars in the parking lot
int enterCar = 0; // No pin, Set the initial number of cars in the parking lot

//  Set seven segments digital pins
int upMLed = 8; //A
int upRLed = 7; //B
int downRLed = 6; //C
int downMLed = 5; //D
int downLLed = 4; //E
int upLLed = 3; //F
int midleMLed = 2; //G


// First section, set variables for the entrance motor.
int infraPinOne = 0 ; // Analog pin, Proximity sensor for entrance (Infra-Red)
int gatePinOne = 1; // Analog pin, the micro switches at the open and closed states of the entrance gate. (0 when fully open or closed,1 otherwise)
int motorOneU = 12;  // Digital pin, if set to 1 the entrance gate motor opens.
int motorOneD = 13;   // Digital pin, if set to 1 the entrance gate motor closes.
bool gateOneIsOpenOrClose = false;  // No pin,  0 is when entrance gate is fully closed and 1 when open.


// Set the fucntions to false initially for the first motor
bool toEnterOne1 = false; // No pin, remember to enter first phase in the next iteration.
bool toEnterOne2 = false; // No pin, remember to enter second phase in the next iteration.
bool closeNowOne = false; // No pin, start the closing sequence in the next iteration.
unsigned long lastMiliOne = 0; // No pin, remember the time fraction it took the arduino to run the code and compare it to the delay needed.
int littleBitMorCloseOne = 0; //Makes the motor run for a small time sequence to allow the arm to leave the first switch before checking the second switch.
int littleBitMorOpenOne = 0; //Makes the motor run for a small time sequence to allow the arm to leave the first switch before checking the second switch.


// First section, set variables for the exit motor.
int infraPinTwo = 2 ; // Analog pin, Proximity sensor for exit (Infra-Red)
int gatePinTwo = 3; // Analog pin, the micro switches at the open and closed states of the exit gate. (0 when fully open or closed,1 otherwise)
int motorTwoU = 10;  // Digital pin, if set to 1 the exit gate motor opens.
int motorTwoD = 11;  // Digital pin, if set to 1 the exit gate motor closes.
bool gateTwoIsOpenOrClose = false;  // No pin, remember the time fraction it took the arduino to run the code and compare it to the delay needed.



// Set the fucntions to false initially for the first motor
bool toEnterTwo1 = false; // No pin, remember to enter first phase in the next iteration.
bool toEnterTwo2 = false; // No pin, remember to enter second phase in the next iteration.
bool closeNowTwo = false; // No pin, start the closing sequence in the next iteration.
unsigned long lastMiliTwo = 0;  // No pin, remember the time fraction it took the arduino to run the code and compare it to the delay needed.
int littleBitMorCloseTwo = 0; //Makes the motor run for a small time sequence to allow the arm to leave the first switch before checking the second switch.
int littleBitMorOpenTwo = 0; //Makes the motor run for a small time sequence to allow the arm to leave the first switch before checking the second switch.




 


void setup() {  //on startup
  Serial.begin(9600); 
  pinMode(infraPinOne, INPUT); //Set infraPinOne as input
  pinMode(gatePinOne, INPUT); //Set gatePinOne as input
  pinMode(motorOneU, OUTPUT); //Set motorOneU as output
  pinMode(motorOneD, OUTPUT); //Set motorOneD as output

  
   
  pinMode(infraPinTwo, INPUT);  //Set infraPinTwo as input
  pinMode(gatePinTwo, INPUT);   //Set gatePinTwo as input
  pinMode(motorTwoU, OUTPUT);   //Set motorTwoU as output
  pinMode(motorTwoD, OUTPUT);   //Set motorTwoD as output
 


  // Assign Seven Segment pins as output
  pinMode(upMLed, OUTPUT);
  pinMode(upRLed, OUTPUT);
  pinMode(upLLed, OUTPUT);
  pinMode(midleMLed, OUTPUT);
  pinMode(downRLed, OUTPUT);
  pinMode(downLLed, OUTPUT);
  pinMode(downMLed, OUTPUT);

  sevenSegmentNumber(maxCars-enterCar); //Set initial number in the seven segments as the maximum number of cars minus the current number of cars

  
}



void loop() {
  //Testing lines for the sensors:
 // Serial.println(isObjectInTheSensor(infraPinOne));
 // Serial.println(isObjectInTheSensor(infraPinTwo));

 //Serial.println(switchF(gatePinOne));
 //Serial.println(switchF(gatePinTwo));



  //Run the code for the entrance section:
  allOperationsForSection(infraPinOne, gatePinOne, motorOneU, motorOneD, gateOneIsOpenOrClose, toEnterOne1, toEnterOne2,  closeNowOne, lastMiliOne, 'O', littleBitMorCloseOne, littleBitMorOpenOne); //call the function allOperationsForSection with all the variables of section section two.

  //Run the code for the exit section:
  allOperationsForSection(infraPinTwo, gatePinTwo, motorTwoU, motorTwoD, gateTwoIsOpenOrClose, toEnterTwo1, toEnterTwo2,  closeNowTwo, lastMiliTwo, 'T', littleBitMorCloseTwo, littleBitMorOpenTwo); //call the function allOperationsForSection with all the variables of section section One. 

}

//Function that reads a proximity sensor(you need to change it for your sensor because of lighting conditions and distance), returns 1 if something is in the way
bool isObjectInTheSensor(int infraPin){
     Serial.println(" switchF info " + (String) analogRead(infraPin)); 
    return analogRead(infraPin) > 800;
}

//Function that reads a switch set for the gate and returns 1 if the switches are open and 0 if the switches are closed
bool switchF(int gatePin){    //  return 0 if the gate is prased and 1 if the gate is not preasd 
   Serial.println(" switchF info " + (String) analogRead(gatePin)); 
  return analogRead(gatePin) > 50;
}







// The main function for the Section using the proximity sensor, the switch set, the motor up and down variables, the variables for the phases, the time of the last iteration, the section number (one two) and the open and closing check delays.
void allOperationsForSection(int infraPin, int gatePin, int motorU, int motorD, bool &gateIsOpenOrClose, bool &toEnter1, bool &toEnter2, bool &closeNow, unsigned long &lastMili, char SectionNumber, int &littleBitMorClose, int &littelBitMorOpen){  
  if(toEnter2){ // If the gate is finishing the opening sequence
    if(millis()-lastMili >= delayV){  // Delaty time to close the gate after opening
      Serial.println("Close the gate"); // set all the variables to false and go to the else part which closes the gate
      toEnter2 = false;
      toEnter1 = false;
      closeNow = false;
    }  
  }
  else if(toEnter1){ // If the gate is beginning to open
      Serial.println("The motor is on");
      digitalWrite(motorU, HIGH);   // Start the motor 
      if(littelBitMorOpen >=15){ // If the checking delay passed 15
        if(!switchF(gatePin)){  // If the swich is open 
        littelBitMorOpen = 0;  // Reset littleBitMorOpen
        gateIsOpenOrClose = true; // The gate is open
        Serial.println("The gate is now open");
        digitalWrite(motorU, LOW);  // Stop the motor
        toEnter2 = true; // Start counting time and then close the gate
        lastMili = millis(); // Get the current time of the iteration
        }  
      }
      littelBitMorOpen++;    
  }
  else if (closeNow){ //if the gate is closing
    if(isObjectInTheSensor(infraPin)){  // Check if there is a car in the way of the gate 
      digitalWrite(motorD, LOW); // Stop the motor
      closeNow = false; // Stop the closing sequence
      littleBitMorClose = 0; // Reset littleBitMorClose
      toEnter1 = true; // Start opening the gate so the car won't get crushed
    }
    if(littleBitMorClose >= 15){ // If the checking delay passed 15
      if(!switchF(gatePin)){  // If the switch is closed
        
          digitalWrite(motorD, LOW); // Stop the motor
          gateIsOpenOrClose = false; // The gate is not open anymore
          Serial.println("The gate is now closed");
          closeNow = false; // Stop the closing sequence
          littleBitMorClose = 0; // Reset littleBitMorClose
          if(SectionNumber == 'O'){ // If we are at the entrance
      
            enterCar++; // Add one to enterCar 
            sevenSegmentNumber(maxCars-enterCar); // Display the new number of available parking spots
          }
          else if(SectionNumber  == 'T'){ // Check if we are at the exit section
            if(enterCar > 0){ //Check if there are any cars in the parking lot
              enterCar--; // Remove one from the entered cars
              sevenSegmentNumber(maxCars-enterCar); // Display the new number of parking spots available
            }
          }
      }
    }
    littleBitMorClose++;  //Add one to littleBitMorClose    
  }
   else if(isObjectInTheSensor(infraPin)){  // Check if there is a vehicle in the sensor
    if (!gateIsOpenOrClose) {  // Check if the gate is closed or open
      if(SectionNumber == 'O' && enterCar >= maxCars){ //Check if the section is the entrance and the entered cars passed the maximum number in the lot
        // Don't do anything (Don't open the gate)
      }
      else{
        toEnter1 = true; //if there is slots available or a car wants to get out, open the gate
      }
    }
    else{
      Serial.println("The gate is already open ");
     }
    }
  else{
      if(gateIsOpenOrClose) {  //  Check if the gate is open
        gateIsOpenOrClose = false;
        digitalWrite(motorD, HIGH); //Start closing the gate
        closeNow = true; //Begin the gate closing sequence
      }
      else{
        Serial.println("The gate is already closed.");
      }
    } 
}






//Cases for turning on the Seven Segment Display:
void sevenSegmentNumber(int number){  
  switch(number){
    case -1:  // On -1, turn off the entire screen.
    digitalWrite(upMLed, LOW);
    digitalWrite(upLLed, LOW);
    digitalWrite(midleMLed, LOW);
    digitalWrite(downRLed, LOW);
    digitalWrite(downMLed, LOW);
    digitalWrite(downLLed, LOW);
    digitalWrite(upRLed, LOW);
    break;
    
    case 0:
    sevenSegmentNumber(-1);
    digitalWrite(upMLed, HIGH);
    digitalWrite(upLLed, HIGH);
    digitalWrite(downLLed, HIGH);
    digitalWrite(downMLed, HIGH);
    digitalWrite(downRLed, HIGH);
    digitalWrite(upRLed, HIGH);
    break;
    
    case 1:
    sevenSegmentNumber(-1);
    digitalWrite(upRLed, HIGH);
    digitalWrite(downRLed, HIGH);
    break;

    case 2:
    sevenSegmentNumber(-1);
    digitalWrite(upMLed, HIGH);
    digitalWrite(upRLed, HIGH);
    digitalWrite(midleMLed, HIGH);
    digitalWrite(downLLed, HIGH);
    digitalWrite(downMLed, HIGH);
    break;
    
    case 3:
    sevenSegmentNumber(-1);
    digitalWrite(upMLed, HIGH);
    digitalWrite(upRLed, HIGH);
    digitalWrite(midleMLed, HIGH);
    digitalWrite(downRLed, HIGH);
    digitalWrite(downMLed, HIGH);
    break;
    
    case 4:
    sevenSegmentNumber(-1);
    digitalWrite(upLLed, HIGH);
    digitalWrite(midleMLed, HIGH);
    digitalWrite(upRLed, HIGH);
    digitalWrite(downRLed, HIGH);
    break;
    
    case 5:
    sevenSegmentNumber(-1);
    digitalWrite(upMLed, HIGH);
    digitalWrite(upLLed, HIGH);
    digitalWrite(midleMLed, HIGH);
    digitalWrite(downRLed, HIGH);
    digitalWrite(downMLed, HIGH);
    break;
    
    case 6:
    sevenSegmentNumber(-1);
    digitalWrite(upMLed, HIGH);
    digitalWrite(upLLed, HIGH);
    digitalWrite(midleMLed, HIGH);
    digitalWrite(downLLed, HIGH);
    digitalWrite(downMLed, HIGH);
    digitalWrite(downRLed, HIGH);
    break;
    
    case 7:
    sevenSegmentNumber(-1);
    digitalWrite(upMLed, HIGH);
    digitalWrite(upRLed, HIGH);
    digitalWrite(downRLed, HIGH);
    break;
    
    case 8:
    sevenSegmentNumber(-1);
    digitalWrite(upMLed, HIGH);
    digitalWrite(upLLed, HIGH);
    digitalWrite(midleMLed, HIGH);
    digitalWrite(downRLed, HIGH);
    digitalWrite(downMLed, HIGH);
    digitalWrite(downLLed, HIGH);
    digitalWrite(upRLed, HIGH);
    break;
    
    case 9:
    sevenSegmentNumber(-1);
    digitalWrite(upMLed, HIGH);
    digitalWrite(upLLed, HIGH);
    digitalWrite(midleMLed, HIGH);
    digitalWrite(upRLed, HIGH);
    digitalWrite(downRLed, HIGH);
    break;    
  }
}





