/*
Het is allemaal heel warrig omdat het allemaal is gekopieerd
maakt niet heel veel uit want gaat toch nog niet om de code
maar je kan dit wel gebruiken om bepaalde functies/syntax te snappen
*/
#include <LiquidCrystal.h>
#include <Stepper.h>
//LCD pin to Arduino
const int pin_RS = 8; //weet niet wat RS,EN en BL betekenent maar hij doet t
const int pin_EN = 9; 
const int pin_d4 = 4; 
const int pin_d5 = 5; 
const int pin_d6 = 6; 
const int pin_d7 = 7; 
const int pin_BL = 10; 
// Configureer de INPUT pin van de PIR.
int inputPin = 2;
// Zet de pirstate op LOW, aannemend dat er geen beweging is gedetecteerd wanneer de PIR start.
int pirState = LOW;
// Een variabele voor de pinstatus van de PIR.
int val = 0;

// Motor pins
#define A 3
#define B 11
#define C 12
#define D 13
#define STEPSREV 4096

Stepper stepper1 = Stepper(STEPSREV, A, C, B, D); //Let op de volgorde
int delaytime = 3; // 3 ms, wordt niet gebruikt atm
 
#define NUMBER_OF_STEPS_PER_REV 512

LiquidCrystal lcd( pin_RS,  pin_EN,  pin_d4,  pin_d5,  pin_d6,  pin_d7);

void setup() {
 lcd.begin(16, 2); //16x2 display
 lcd.setCursor(0,0);
 pinMode(inputPin, INPUT); //Hiermee kan de sensor inputten
 
 Serial.begin(9600); //voor als je zooi naar je laptop wil sturen
 pinMode(A,OUTPUT);
 pinMode(B,OUTPUT);
 pinMode(C,OUTPUT);
 pinMode(D,OUTPUT); // voor de motor

 stepper1.setSpeed(4); //4 rpm
}

//although the tutorials had some values, they were wrong so I had to look at it myself
//these values are between the consecutive voltages so you need to use <
//example: if you press down the volt sent will be ~420 but in your code you need to check if your volt is less than voltdown but greater than voltup
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
}

void onestep(){ 
//letterlijk magie, snap niet hoe dit de motor aan de praat krijgt
// sowieso bestaat er gewoon een library voor een motor draaien die ik hier ook gebruik
// als we dit zouden kunnen gebruiken zouden de ledjes miss niet aan hoeven? Maar dit is eigenlijk allemaal gelul want ik snap niks van deze code
int delaytime;
delaytime = 3;
write(1,0,0,0);
delay(delaytime);
write(1,1,0,0);
delay(delaytime);
write(0,1,0,0);
delay(delaytime);
write(0,1,1,0);
delay(delaytime);
write(0,0,1,0);
delay(delaytime);
write(0,0,1,1);
delay(delaytime);
write(0,0,0,1);
delay(delaytime);
write(1,0,0,1);
delay(delaytime);
}


void bigstep(){
  stepper1.step(2048);

}

void loop() {
 int x;
 x = analogRead (0); //button input
 lcd.setCursor(0,0); //eerste letter eerste rij
 lcd.print(x);
 lcd.setCursor(0,1); //eerste letter tweede rij
 //if (x < 60) {
 //  lcd.print ("Right ");
 //}
 //else if (x < 250) {
 //  lcd.print ("Up    ");
 //}
 //else if (x < 450){
 //  lcd.print ("Down  ");
 //}
 //else if (x < 650){
 //  lcd.print ("Left  ");
 //}
 //else if (x < 850){
 //  lcd.print ("Select");
 //}
     // Uitlezen van de PIR pin, is deze hoog of laag?
    val = digitalRead(inputPin);
    // Als de PIR pin beweging detecteert.
    if (val == HIGH) {
        // Zet de LED aan.
        //digitalWrite(ledPin, HIGH);
        if (pirState == LOW) { //de code van de website doet dit i guess om niet op hol te slaan als hij constant beweging meet
            //De PIR is AAN.
            lcd.print("Beweging");
            // We reageren alleen op de verandering aan de OUT pin, niet de PIR status.
            pirState = HIGH;
            bigstep();
          
        }
    } else { //dus geen beweging gedetecteerd
        // Zet de LED uit.
        //digitalWrite(ledPin, LOW);
        if (pirState == HIGH){
            // De PIR is UIT.
            lcd.print("No more ");
            // We reageren alleen op de verandering aan de OUT pin, niet de PIR status.
            pirState = LOW;
        }
    }
} 