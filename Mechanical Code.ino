#include <LiquidCrystal.h>
#include <Stepper.h>

void setup() {
  setupMotor();
  setupSensor();
  setupScreenAndButtons();
  Serial.begin(9600); //voor als je zooi naar je laptop wil sturen
}

void loop() {
  //opens the cabinet when needed.
  if frideJustOpened() {
    if cabShouldOpen() {
    if !openCabinet() {
      if testMechanicalError() {
        mechanicalError();
      }
    }
  }

  //closes the cabinet when needed
  if cabShouldClose() {
    if !closeCabinet() {
      if testMechanicalError() {
        mechanicalError();
      }
    }
  }

  //The rest should contain functions to controll the display, database and time.

}


/*
The following fuctions setup different part of the machine.
*/

//Function to set up the motor.
void setupMotor() {
  //initialiseer stepper motor
  Stepper stepper1 = Stepper(STEPSREV, A, C, B, D); //Let op de volgorde
  int delaytime = 3; // 3 ms, wordt niet gebruikt atm
  #define NUMBER_OF_STEPS_PER_REV 512

  pinMode(A,OUTPUT);
  pinMode(B,OUTPUT);
  pinMode(C,OUTPUT);
  pinMode(D,OUTPUT); // voor de motor
  stepper1.setSpeed(4); //4 rpm
  
  //although the tutorials had some values, they were wrong so I had to look at it myself
  //these values are between the consecutive voltages so you need to use <
  //example: if you press down the volt sent will be ~420 but in your code 
  //you need to check if your volt is less than voltdown but greater than voltup
  //experimentally obtained, might differ in final product:
  const int voltRight = 60;
  const int voltUp = 250;
  const int voltDown = 450;
  const int voltLeft = 650;
  const int voltSelect = 850;
  //Next two functions are useless
  void write(int a,int b,int c,int d){ //van een website maar snap niet wat ie doet en is niet nodig vgm
  digitalWrite(A,a);
  digitalWrite(B,b);
  digitalWrite(C,c);
  digitalWrite(D,d);

  //Variables for the logic of opening and closing the cabinet.
  bool cabClosed = true;
  bool cabOpen = false;
  int mechanicalErrorDelay = 5000; //in ms
}

//Function to set up the sensor.
void setupSensor() {
  pinMode(inputPin, INPUT); //Hiermee kan de sensor inputten
}

//Function to set up the screen and buttons.
void setupScreenAndButtons() {
  // LCD pins
  const int pin_RS = 8; //weet niet wat RS,EN en BL betekenent maar hij doet het
  const int pin_EN = 9;
  const int pin_d4 = 4;
  const int pin_d5 = 5;
  const int pin_d6 = 6;
  const int pin_d7 = 7;
  const int pin_BL = 10;
  // Configureer de INPUT pin van de PIR.
  int inputPin = 2;
  // Zet de pirstate op LOW, aannemend dat er geen beweging is gedetecteerd 
  wanneer de PIR start.
  int pirState = LOW;
  // Een variabele voor de pinstatus van de PIR.
  int val = 0;
  LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
  lcd.begin(16, 2); //16x2 display
  lcd.setCursor(0,0);
}


/*
The following functions determine if a mechanical action should be taken.
*/

//Function to check if the fridge door has just opened.
bool fridgeJustOpened() {

}
//Function to check if there is a fruit that is almost expired.
bool cabShouldOpen() {

}

//Function to check if the button to close the cabinet has been pressed.
bool cabShouldClose() {

}

//Function to check if the cabinet is moving.
bool cabIsMoving() {

}


/*
The following functions undertake mechanical action.
*/

//Function to open the cabinet.
bool openCabinet() {
//if it didn't succeed:
  return false;
}

//Function to close the cabinet.
bool closeCabinet() {
//if it didn't succeed:
  return false;
}

//Function to try to close the cabinet every few seconds
void mechanicalError() {
  int tryCounter = 0;
  while tryCounter < 3 {
    delay(mechanicalErrorDelay);
    if cabIsMoving() {
      continue;
    }
    cabClosed = closeCabinet();
    tryCounter++;
    if cabClosed {
      return false
    }
  }
  return true
}
