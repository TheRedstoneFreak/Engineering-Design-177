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
bool noBtnPressed = true;

int Apples = 30;
int Asparagus = 30;
int Avocadoes = 30;
int Beans = 5;
int Berries = 3;
int Broccoli = 6;
int Carrots = 80;
int Capsicum = 12;
int Cauliflower = 12;
int Celery = 25;
int Corn = 3;
int Citrus = 16;
int Cucumber = 11;
int Eggplant = 11;
int Lettuce = 11;
int Kiwi = 7;
int Mushrooms = 11;
int Onions = 80;
int Peaches = 3;
int Pears = 14;
int Peas = 6;
int Strawberries = 3;
int Tomatoes = 6;




int Compartment_1_date = 0;
int Compartment_2_date = 0;
String Compartment_1 = "Empty";
String Compartment_2 = "Empty";

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
      noBtnPressed = true;
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
  unsigned long original_time = millis(); //Start time since arduino is on
  
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

  check_timers();

   
   
    if (Compartment_1_date <= get_current_time()) {
      while (noBtnPressed) {
      lcd.setCursor(0,0);
      lcd.print((*iter).first); 
      lcd.setCursor(0,1);
      lcd.print("Out of date >");
      delay(500);
      }
       compartment.erase((*iter).first)
   }
      if (Compartment_1_date - 86 400 000 <= get_current_time()) { //1 dag
      while (noBtnPressed) {
      lcd.setCursor(0,0);
      lcd.print((*iter).first); 
      lcd.setCursor(0,1);
      lcd.print("1 day left >");
      delay(500);
      }
   
   }
   
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
  if (selection_list > 8 || selection_list < 1) { //Aanpassen naar hoeveel cases er zijn
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
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 30 * 86400000;
        Compartment_1 = "Apple";
        Compartment_1_date = start_time + time_left;
        
      break;
        
     case 2:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("<  Avocado  >");
      delay(500);
      if(btnSelectPressed) {
        //add_fruit(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 3 * 86400000;
        Compartment_1 = "Avocado";
        Compartment_1_date = start_time + time_left;
      }
      break;
        
      case 3:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("<   Berries    >");
      delay(500);
      if(btnSelectPressed) {
        //add_fruit(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 3 * 86400000;
        Compartment_1 = "Berries";
        Compartment_1_date = start_time + time_left;
      }
      break;
        
      case 4:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("<    Citrus    >");
      delay(500);
      if(btnSelectPressed) {
        //add_fruit(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 16 * 86400000;
        Compartment_1 = "Citrus";
        Compartment_1_date = start_time + time_left;
      }
      break;
        
      case 5:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("<     Kiwi     >");
      delay(500);
      if(btnSelectPressed) {
        //add_fruit(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 7 * 86400000;
        Compartment_1 = "Kiwi";
        Compartment_1_date = start_time + time_left;
      }
      break;
        
      case 6:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("<   Peaches    >");
      delay(500);
      if(btnSelectPressed) {
        //add_fruit(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 3 * 86400000;
        Compartment_1 = "Peaches";
        Compartment_1_date = start_time + time_left;
      }
      break;
        
      case 7:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("<    Pears     >");
      delay(500);
      if(btnSelectPressed) {
        //add_fruit(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 14 * 86400000;
        Compartment_1 = "Pears";
        Compartment_1_date = start_time + time_left;
      }
      break;
        
      case 8:
      lcd.setCursor(0,0);
      lcd.print("Select fruit");
      lcd.setCursor(0,1);
      lcd.print("< Strawberries >");
      delay(500);
      if(btnSelectPressed) {
        //add_fruit(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 3 * 86400000;
        Compartment_1 = "Strawberries";
        Compartment_1_date = start_time + time_left;
      }
      break;
        

    default: selection_list = 1;
      break;
  }
}
//Vegetable menu add

void vegetable_menu() {
  if (selection_list > 14 || selection_list < 1) { //Aanpassen naar hoeveel cases er zijn
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
      lcd.print("<  Asparagus   >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_vegetable(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 4 * 86400000;
        Compartment_2 = "Asparagus";
        Compartment_2_date = start_time + time_left;
      } 
      break;
    case 2:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<    Beans     >");
      delay(500);
      if(btnSelectPressed) {
        //add_vegetable(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 5 * 86400000;
        Compartment_2 = "Beans";
        Compartment_2_date = start_time + time_left;
      }
      break; 
      
     case 3:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<   Broccoli   >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_vegetable(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 6 * 86400000;
        Compartment_2 = "Broccoli";
        Compartment_2_date = start_time + time_left;
      } 
      break;
    case 4:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<   Carrots    >");
      delay(500);
      if(btnSelectPressed) {
        //add_vegetable(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 30 * 86400000;
        Compartment_2 = "Carrots";
        Compartment_2_date = start_time + time_left;
      }
      break;
        
      case 5:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<   Capsicum   >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_vegetable(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 12 * 86400000;
        Compartment_2 = "Capsicum";
        Compartment_2_date = start_time + time_left;
      } 
      break;
    case 6:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("< Cauliflower  >");
      delay(500);
      if(btnSelectPressed) {
        //add_vegetable(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 12 * 86400000;
        Compartment_2 = "Cauliflower";
        Compartment_2_date = start_time + time_left;v
        
      }
      break;
        
     case 7:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<    Celery    >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_vegetable(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 25 * 86400000;
        Compartment_2 = "Celery";
        Compartment_2_date = start_time + time_left;
         
      } 
      break;
    case 8:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<     Corn     >");
      delay(500);
      if(btnSelectPressed) {
        //add_vegetable(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 3 * 86400000;
        Compartment_2 = "Corn";
        Compartment_2_date = start_time + time_left;
      }
      break;

        case 9:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<   Cucumber   >");
      delay(500);
      if(btnSelectPressed) {
        //add_vegetable(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 11 * 86400000;
        Compartment_2 = "Cucumber";
        Compartment_2_date = start_time + time_left;
      }
      break; 
      
     case 10:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<   Eggplant   >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_vegetable(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 11 * 86400000;
        Compartment_2 = "Eggplant";
        Compartment_2_date = start_time + time_left;
        
      } 
      break;
    case 11:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<   Lettuce    >");
      delay(500);
      if(btnSelectPressed) {
        //add_vegetable(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 11 * 86400000;
        Compartment_2 = "Lettuce";
        Compartment_2_date = start_time + time_left;
      }
      break;
        
      case 12:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<  Mushrooms   >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_vegetable(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 11 * 86400000;
        Compartment_2 = "Mushrooms";
        Compartment_2_date = start_time + time_left;
      } 
      break;
    case 13:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<     Peas     >");
      delay(500);
      if(btnSelectPressed) {
        //add_vegetable(selection_list)
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 6 * 86400000;
        Compartment_2 = "Peas";
        Compartment_2_date = start_time + time_left;
      }
      break;
        
     case 14:
      lcd.setCursor(0,0);
      lcd.print("Select vegetable");
      lcd.setCursor(0,1);
      lcd.print("<   Tomatoes   >");
      delay(500);
      if(btnSelectPressed) { // hier de actie komen om toe te voegen aan list
        //add_vegetable(selection_list);
        btnSelectPressed = false;
        finalChoice = true;
        unsigned long current_time = millis();
        unsigned long start_time = get_current_time();
        unsigned long time_left = 6 * 86400000;
        Compartment_2 = "Tomatoes";
        Compartment_2_date = start_time + time_left;

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
   for (iter = food.begin(); iter != food.end(); iter++)
   {
     cout << ">" <<(*iter).first << "\n";
     cout << " " << (*iter).second << " days \n";
    
   }
    cout << food.begin()->first;
    return 0;

    }
  
}


void get_current_time() {
  unsigned long current_time = millis()
  return current_time  
}

void check_timers() {
  // ga de current list af
  // Check of de tijd voorbij is dmv starttijd + looptijd = current_time
  
void start_timer(product) { //dit moet bij product komen maar kan dan met get_current time
 unsigned long start_time = millis();
 return start_time;
}

void check_timer() {
  if (timer_done == true) {
     //Hier wat er gebeurt wanneer de timer voorbij is
  }
} 

bool timer_done() { // Returns true als de tijd voorbij is
   //Moet nog iets komen waardoor ik een totale tijd van een product kan krijgen (product in bool)
  unsigned long start_time = start_timer();
  //unsigned long total_time = 
  unsigned long current_time = get_current_time();
  time_in_fridge = start_time - current_time;
  if (time_in_fridge >= total_time) {
     return true
     } else {
     return false
     }
}

void get_current_time() {
  unsigned long current_time = millis();
  return current_time    
  
}

