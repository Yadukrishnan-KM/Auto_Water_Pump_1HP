#include <LiquidCrystal_I2C.h>
#include  <Wire.h>
#include <EEPROM.h>
void(* resetFunc) (void) = 0;

const byte alarmLightPin = 13;
const byte alarmBuzzerPin = 4;
const byte onLEDPin = A1;
const byte offLEDPin = A0;
const byte inputSwitchPin = A7;
const byte lcdLEDBrightPin = 3;




LiquidCrystal_I2C lcd(0x27,  16, 2);                    //initialization. the parameters are the I2C address,no of rows, no of columns are on your screen

int brightValue = 1023;
int buttonValue = 0;

bool pumpOperationModeSetting = true;           // normally auto
int pumpScheduleTimeSetting = 1;                // normally off 1-off, 2-every 6hr, 3-every 8hr, 4-every 12hr, 5-every 24hr
bool lowVoltCutoffSetting = true;               // normally cutoff enabled
int pumpAoffTimerSetting = 3 ;                  // normally 45min  1-off, 2-30min, 3-45min, 4-60min, 5-90min, 6-120min
bool dryrunCutoffSetting = true;                //dryrun cutoff enabled
int brightValueSetting = 4;                     // brightness vale 1-10%, 2-25% 3-50%, 4-75%, 5-100%

int homeScreenFlag = 0; // 0 - home screen - idle, 1 - menu - right button, 2 - alarm menu - left button
int mainmenuSelectCaseNo = 1;
int alarmSelectionCaseNo = 1;
//flag for entering into each edit section by pressing enter from mainmenu
bool operationModeEditFlag = false;
bool pumpScheduleEditFlag = false;
bool lowVoltCutoffEditFlag = false;
bool pumpAoffTimerEditFlag = false;
bool dryrunCutoffEditFlag = false;
bool brightValueEditFlag = false;
bool factoryResetEditFlag = false;

unsigned long menuTimeoutPreviousMillis = 0;
unsigned long menuTimeoutCurrentMillis = 0;
bool menuTimeoutCounterFlag = false;


// memory for sysmbol
byte powerSymbol[] = {0x02, 0x0C,0x18,0x1F,0x1F,0x06,0x0C,0x10};
byte abnormal[] = {0x0C, 0x0C,0x0C,0x0C,0x0C,0x00,0x0C,0x0C};
byte PumpRunningSymbol[] = {0x1F, 0x1F,0x1F,0x1F,0x1F,0x1F,0x04,0x1F};
byte alarmSymbol[] = {0x01, 0x03,0x07,0x1F,0x1F,0x07,0x03,0x01};
byte batterySymbol[] = {0x0E, 0x0E,0x1F,0x1F,0x1F,0x1F,0x1F,0x1F};
byte transmitterGoodSymbol[] = {0x0E, 0x11,0x04,0x0A,0x00,0x04,0x04,0x04};
byte timerSymbol[] = {0x1F, 0x11,0x0A,0x04,0x04,0x0E,0x1F,0x1F};
byte autoSymbol[] = {0x0E, 0x0A,0x0E,0x0A,0x00,0x1F,0x11,0x1F};
byte leftArrowSymbol[] = {0x07,0x0E,0x1C,0x18,0x18,0x1C,0x0E,0x07};
byte rightArrowSymbol[] = {0x1C,0x0E,0x07,0x03,0x03,0x07,0x0E,0x1C};

void setup() {
 Serial.begin(9600);
 lcd.init();                                            // initialize lcd screen
 lcd.createChar(0, powerSymbol);                        // ac present and good symbol  
 lcd.createChar(1, abnormal);                           // abonrmal symbol is !
 lcd.createChar(2, PumpRunningSymbol);                  // pump running and good symbol 
 lcd.createChar(3, alarmSymbol);                        // alarm symbol
 lcd.createChar(4, batterySymbol);                      // battery symbol
 lcd.createChar(5, transmitterGoodSymbol);              // transmitterGoodSymbol   
 lcd.createChar(6, timerSymbol);                        // timer Symbol 
 lcd.createChar(7, autoSymbol);                         // auto operation Symbol 
 //lcd.backlight();                                        // turn on the backlight using i2c
 analogWrite(lcdLEDBrightPin, brightValue);             // to turn on backlight using PWM
 startUpScreen();                                       // only use in setup for working after reset, the first startup messgae screen with led working checks
}

void loop() {
 analogWrite(lcdLEDBrightPin, brightValue);              // to turn on backlight 
 buttonValue = buttonRead(inputSwitchPin);
 Serial.println(buttonValue);

 //********************************************************************************************* HOME SCREEN **************************************************************************************
 if(homeScreenFlag == 0){                                       // entering into home screen, idle condition
   buttonValue = buttonRead(inputSwitchPin);                    // going to main menu and alarm menu by checking input
   if(buttonValue == 3) homeScreenFlag = 1;
   else if(buttonValue == 4)homeScreenFlag = 2;

   //refreshing with all the required data which save in eeprom when it is in home screen, default screen
   pumpOperationModeSetting = EEPROM.read(1);
   pumpScheduleTimeSetting = EEPROM.read(2);
   lowVoltCutoffSetting = EEPROM.read(3);
   pumpAoffTimerSetting = EEPROM.read(4);
   dryrunCutoffSetting = EEPROM.read(5);
   brightValueSetting = EEPROM.read(6);

   lcd.clear();
   lcd.setCursor(0,0); lcd.print("** LEVEL"); lcd.setCursor(9,0); lcd.print("90"); lcd.setCursor(12,0); lcd.print("% **"); // main lavel indication
   lcd.setCursor(0,1); lcd.write(0);                        // ac present and good symbol
   //lcd.setCursor(1,1); lcd.write(1);                        // some issue symbol
   lcd.setCursor(3,1); lcd.write(2);                        // pump running and good symbol
   //lcd.setCursor(4,1); lcd.write(1);                        // some issue symbol
   //lcd.setCursor(6,1); lcd.write(6);                        // timer enable symbol
   //lcd.setCursor(8,1); lcd.write(3);                        // alarm present symbol
   lcd.setCursor(10,1); lcd.write(7);                       // auto operation symbol
   lcd.setCursor(12,1); lcd.write(4);                       // battery good symbol
   //lcd.setCursor(13,1); lcd.write(1);                       // some issue symbol
   lcd.setCursor(14,1); lcd.write(5);                       // transmitter good symbol
   //lcd.setCursor(15,1); lcd.write(1);                       // some issue symbol
 }
 //********************************************************************************************* MENU SCREEN **************************************************************************************
 else if(homeScreenFlag == 1){                              // entering into menu screen

   buttonValue = buttonRead(inputSwitchPin);                // reading the up/down button press and moving menu up or down
   if(buttonValue == 1) mainmenuSelectCaseNo++;
   if(mainmenuSelectCaseNo == 9) mainmenuSelectCaseNo = 1;
   if(buttonValue == 2) mainmenuSelectCaseNo--;
   if(mainmenuSelectCaseNo == 0) mainmenuSelectCaseNo = 8;
   if(buttonValue != 0) menuTimeoutPreviousMillis = menuTimeoutCurrentMillis; // to restart timeout counter if button is pressed
   mainMenuSwitchCases();                                   // showing corresponding case for main menu with edit option

   // timeout section which return to home screen after timeout

   if(!menuTimeoutCounterFlag){
     menuTimeoutCounterFlag = true;
     menuTimeoutPreviousMillis = millis();
   }
   menuTimeoutCurrentMillis = millis();
   if((menuTimeoutCurrentMillis - menuTimeoutPreviousMillis) >= 6000) {
     homeScreenFlag = 0;                                       // for going to home screen
     menuTimeoutCounterFlag = false;                           // for resettiing the timeout timer
     mainmenuSelectCaseNo = 1;                                 // to restart sub menu from 1
     lcd.createChar(0, powerSymbol);                           // ac present and good symbol adding because max 8 char allowed in lcd memory
     lcd.createChar(1, abnormal);                              // abonrmal symbol is ! adding because max 8 char allowed in lcd memory
     // remove edit option after timeout
     operationModeEditFlag = false;
     pumpScheduleEditFlag = false;
     lowVoltCutoffEditFlag = false;
     pumpAoffTimerEditFlag = false;
     dryrunCutoffEditFlag = false;
     brightValueEditFlag = false;
     factoryResetEditFlag = false;
   }
 }
  //********************************************************************************************* ALARM SCREEN **************************************************************************************
 else if (homeScreenFlag == 2){                                // entering into alarm screen
   lcd.clear();
   lcd.setCursor(0,0); lcd.print("alarm menu");
   buttonValue = buttonRead(inputSwitchPin);
   if(buttonValue == 2) {
     homeScreenFlag = 0;                                       // for going to home screen
     menuTimeoutCounterFlag = false;                           // for resettiing the timeout timer
   }






 // timeout section which return to home screen after timeout

   if(!menuTimeoutCounterFlag){
     menuTimeoutCounterFlag = true;
     menuTimeoutPreviousMillis = millis();
   }
   menuTimeoutCurrentMillis = millis();
   if((menuTimeoutCurrentMillis - menuTimeoutPreviousMillis) >= 6000) {
     homeScreenFlag = 0;
     menuTimeoutCounterFlag = false;
   }       

 }
 else homeScreenFlag = 0;
 

 delay(100);
}
