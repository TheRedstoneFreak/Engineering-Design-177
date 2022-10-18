// Demo of a Keypad LCD Shield
// Common design sold by DFRobot, various vendors on eBay etc

#include <LiquidCrystal.h>
#include <DFR_LCD_Keypad.h>

#define JUMPING_GAME 1
#define PLAYING_MUSIC 2
#define SETTING_PASSWORD 3

LiquidCrystal lcd(8,9,4,5,6,7); 
DFR_LCD_Keypad keypad(A0, &lcd);

//Initializing variables
int led=13;
int last_key, key;
int selection_list;
int final_selection;
int final_jumping_selection;
int current_list = 0;

bool accessGame = true;
bool accessMenu = true;
bool finalChoice =  false;

bool btnUpPressed = false;
bool btnDownPressed = false;
bool btnRightPressed = false;
bool btnLeftPressed = false;
bool btnSelectPressed = false;

enum Buttons { 
  UP, 
  DOWN, 
  RIGHT, 
  LEFT, 
  SELECT, 
  NONE 
};
Buttons Current_Button = NONE;

ISR(PCINT1_vect) {
   ButtonCheck(analogRead(0));
}


// Begin setup en loop -----------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void setup(){
  Serial.begin(9600);
  lcd.begin(16,2);
  lcd.setCursor(0,0);
  lcd.print("HELLO ^-^!");
  pinMode(led, OUTPUT);
  delay(1000);
  lcd.clear();
  cli();
  
  // Setup Pin Change Interrupt for Buttons
  PCICR =0x02;                  // Enable 'PCIE1' bit of PCICR Pin Change Interrupt the PCINT1 interrupt
  PCMSK1 = 0b00000001;          // Pin Change Interrupt Mask ( NA, RESET, A5, A4, A3, A2, A1, A0 ) - Activate A0 
  sei(); 
}


void loop()
{
  if(accessMenu) { // Wanneer accesMenu true is ga je naar main_menu
    do {
      main_menu();
    } while(!finalChoice);
    finalChoice = false;
    accessMenu = false;
  }
  switch (final_selection) {
    case 1: //Current list
      if(accessGame == true) {
        accessMenu = true;
        accessGame = false;
      }
      current_list_menu();
      break;
    case 2: // Add to list
      if(accessGame == true) {
        accessGame = false;
      }
      add_menu();
      break;
      case 3: //Food data
      if(accessGame == true) {
        accessMenu = true;
        accessGame = false;
      }
      food_data();
      break;
  }
}

//Eind setup en loop -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

//Het eerste menu aka main menu --------------------------------------------------------------------------------------------------------------------------------------------------------------------
void main_menu() {
  if (selection_list > 4 || selection_list < 1) {
    selection_list == 1;
  }
  if (btnRightPressed) {
    selection_list++;
    btnRightPressed = false;
  }
  if (btnLeftPressed) {
    selection_list--;
    btnLeftPressed = false;
  }
  lcd.clear();
  switch (selection_list) {// Hier de opties voor de main menu
    //Selection_list = 1 Kijken naar huidige producten
    case 1: 
      lcd.setCursor(0,0);
      lcd.print("Main menu"); 
      lcd.setCursor(0,1);
      lcd.print("< Current list >");
      delay(500);
      if(btnSelectPressed) {
        final_selection = 1;
        btnUpPressed = false;
        finalChoice = true;
      } 
      break;
    // Selection_list = 2 Toevoegen product
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Main menu");
      lcd.setCursor(0,1);
      lcd.print("<   Add new    >");
      delay(500);
      if(btnUpPressed) {
        final_selection = 2;
        btnUpPressed = false;
        finalChoice = true;
      }
      break;

      case 3:
      lcd.setCursor(0,0);
      lcd.print("Main menu");
      lcd.setCursor(0,1);
      lcd.print("<   Food data    >");
      delay(500);
      if(btnUpPressed) {
        final_selection = 2;
        btnUpPressed = false;
        finalChoice = true;
      }
      break;
      
    default: selection_list = 1;
      break;
  }
}

// Einde main menu -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------

// Begin add menu -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void add_menu() {
  if (selection_list > 2 || selection_list < 1) {
    selection_list == 1;
  }
  if (btnRightPressed) {
    selection_list++;
    btnRightPressed = false;
  }
  if (btnLeftPressed) {
    selection_list--;
    btnLeftPressed = false;
  }
  lcd.clear();
  switch (selection_list) { //Hier de opties voor het menu
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Select product:");
      lcd.setCursor(0,1);
      lcd.print("<   Fruit     >");
      delay(500);
      if(btnSelectPressed) {
        fruit_menu();
        btnSelectPressed = false;
        finalChoice = true;
      } 
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Select product:");
      lcd.setCursor(0,1);
      lcd.print("<  Vegetable   >");
      delay(500);
      if(btnSelectPressed) {
        vegetable_menu();
        btnSelectPressed = false;
        finalChoice = true;
      }
      break; 

    default: selection_list = 1;
      break;
  }
}


//Fruit menu

void fruit_menu() {
  if (selection_list > 2 || selection_list < 1) { //Aanpassen naar hoeveel cases er zijn
    selection_list == 1;
  }
  if (btnRightPressed) {
    selection_list++;
    btnRightPressed = false;
  }
  if (btnLeftPressed) {
    selection_list--;
    btnLeftPressed = false;
  }
  lcd.clear();
  switch (selection_list) { //Hier de opties voor het menu
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("<   Apple     >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_fruit(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
      } 
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("<  Banana   >");
      delay(500);
      if(btnSelectPressed) {
        //add_fruit(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
      }
      break; 

    default: selection_list = 1;
      break;
  }
}
//Vegetable menu add

void vegetable_menu() {
  if (selection_list > 2 || selection_list < 1) { //Aanpassen naar hoeveel cases er zijn
    selection_list == 1;
  }
  if (btnRightPressed) {
    selection_list++;
    btnRightPressed = false;
  }
  if (btnLeftPressed) {
    selection_list--;
    btnLeftPressed = false;
  }
  lcd.clear();
  switch (selection_list) { //Hier de opties voor het menu
    case 1:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<   Broccoli   >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_vegetable(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
      } 
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("< Cauliflower  >");
      delay(500);
      if(btnSelectPressed) {
        //add_vegetable(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
      }
      break; 

    default: selection_list = 1;
      break;
  }
}



// Einde add menu -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------


// Current list menu-------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void current_list_menu(){
if (current_list == 0) {
    lcd.setCursor(0,0);
    lcd.print("There are no"); //12 char
    lcd.setCursor(0,1);
    lcd.print("products in list"); //16 char
} else {
    if (selection_list > current_list || selection_list < 1) {
        selection_list == 1;
      }
      if (btnRightPressed) {
        selection_list++;
        btnRightPressed = false;
      }
      if (btnLeftPressed) {
        selection_list--;
        btnLeftPressed = false;
      }
      lcd.clear();
      switch (selection_list) { //Hier de opties voor het menu
        case 1:
          lcd.setCursor(0,0);
          lcd.print("Current list");
          lcd.setCursor(0,1);
          //char print_name = current_product_name(selection_list)     WERKT NOG NIET, heb data nodig om te kijken hoe verder
          //lcd.print(print_name);
          delay(500);
          if(btnSelectPressed) {
            current_product(selection_list);
            btnSelectPressed = false;
            finalChoice = true;
          } 
          break;
      }
}
}

void current_product_name(int selection_list){ //get name product
  //get name
  //return name 
}

void current_product(int selectionlist) { // opens current product from list
  //gets product
  //shows info of product
}

// Data van food inzien -------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
void food_data() {
  
}


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
