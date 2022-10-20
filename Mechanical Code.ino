#include <LiquidCrystal.h>
#include <Stepper.h>
#include <DFR_LCD_Keypad.h>
// Om de knoppen te meten
bool btnUpPressed = false;
bool btnDownPressed = false;
bool btnRightPressed = false;
bool btnLeftPressed = false;
bool btnSelectPressed = false;

// Tijd in ms wanneer hij voor het laatst is geopend
int lastOpened = 0;
int lastClosed = 0;

enum Buttons { 
  UP, 
  DOWN, 
  RIGHT, 
  LEFT, 
  SELECT, 
  NONE 
};
Buttons Current_Button = NONE;

// Begin Buttoncheck, vgm zodat het niet raar vastloopt -----------------------------------------------------------------------------------------------------------------------------------------------
void ButtonCheck(uint16_t adc_value) {
    // The ISR will trigger when button is pressed and when it is let-go
    if (adc_value >= DFR_LCD_KEYPAD_KEY_NONE_ADC_LOW && adc_value <= DFR_LCD_KEYPAD_KEY_NONE_ADC_HIGH) 
    { 
      Current_Button = NONE; 
    }
    if (adc_value >= 0 && adc_value <= 20) 
    { 
      Current_Button = RIGHT; 
      btnRightPressed = true;
    }
    if (adc_value >= 600 && adc_value <= 650)  //354 or 355
    { 
      Current_Button = LEFT;
      btnLeftPressed = true;
    }
    if (adc_value >= 200 && adc_value <= 250) // 119 or 120
    { 
      Current_Button = UP;
      btnUpPressed = true;
    }
    if (adc_value >= 400 && adc_value <= 450) //250 or 251
    { 
      Current_Button = DOWN;
      btnDownPressed = true;
    }
    // not working
    if (adc_value >= 800 && adc_value <= 850) 
    { 
      Current_Button = SELECT;
      btnSelectPressed = true;
    }
}
// Einde Buttoncheck -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

ISR(PCINT1_vect) {
   ButtonCheck(analogRead(0));
}

// Pins van de motor
#define A 3
#define B 11
#define C 12
#define D 13

// Pin van de sensor
int sensorPin = 2;
// Zet de pirstate op LOW, aannemend dat er geen beweging is gedetecteerd wanneer de PIR start.
int pirState = LOW;
// Een variabele voor de pinstatus van de PIR.
int sensorVal = 0;

void setup() {
  setupMotor();
  setupSensor();
  setupScreenAndButtons();
}

void loop() {
  if cabShouldOpen() {
    if openCabinet(){
      mechanicalError();
    }
  }
  if cabShouldClose(){
    if closeCabinet(){
      mechanicalError();
    }
  }
  if menuShouldOpen(){
    openMenu();
  }
  if menuShouldClose(){
    closeMenu();
  }

  // Heb deze eruit gecomment want die kloppen net niet meer nu we niet weten of er een error is
  //opens the cabinet when needed.
  //if frideJustOpened() {
  //  if cabShouldOpen() {
  //  if !openCabinet() {
  //    if testMechanicalError() {
  //      mechanicalError();
  //    }
  //  }
  //}

  //closes the cabinet when needed
  //if cabShouldClose() {
  //  if !closeCabinet() {
  //    if testMechanicalError() {
  //      mechanicalError();
  //    }
  //  }
  //}

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
  //const int voltRight = 60;
  //const int voltUp = 250;
  //const int voltDown = 450;
  //const int voltLeft = 650;
  //const int voltSelect = 850;
  
  //Variables for the logic of opening and closing the cabinet.
  bool menuOpen = false;
  bool isOpen = false;
  bool cabClosed = true;
  bool cabOpen = false;
  bool closingCondition = false;
  int mechanicalErrorDelay = 5000; //in ms
}
void stepOpen(){
  stepper1.step(2048);
}
void stepClose(){
  stepper1.step(-2048);
}

//Function to set up the sensor.
void setupSensor() {
  pinMode(sensorPin, INPUT); //Hiermee kan de sensor inputten
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
  LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);
  lcd.begin(16, 2); //16x2 display
  lcd.setCursor(0,0);
}


/*
The following functions determine if a mechanical action should be taken.
*/

//Function to detect sensor
bool sensorDetection(){
  sensorVal = digitalRead(sensorPin);
  if (sensorVal == HIGH){
    return true;
  } else {
    return false;
  }
}

//Function to check if the fridge door has just opened.
bool fridgeJustOpened() {

}




//Function to check if there is a fruit that is almost expired.
bool cabShouldOpen() {
  OpeningCondition = (sensorDetection() && !isOpen);
  return OpeningCondition
}

//Function to check if the button to close the cabinet has been pressed.
bool cabShouldClose() {
  closingCondition = (btnDownPressed && !menuOpen && isOpen); //aanpasbaar
  return closingCondition;
}

//Function to check if the cabinet is moving.
bool cabIsMoving() {

}


/*
The following functions undertake mechanical action.
*/

//Function to open the cabinet.
bool openCabinet() {
  isOpen = true;
  stepOpen();
  lastOpened = millis();
//if it didn't succeed:
  return false;
}

//Function to close the cabinet.
bool closeCabinet() {
  stepClose();
  lastClosed = millis();
  isOpen = false;
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
