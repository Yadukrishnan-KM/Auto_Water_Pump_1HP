#include <LiquidCrystal.h>

const byte lcdRSPin = 12;
const byte lcdEnablePin = 13;
const byte lcdD4Pin = 11;
const byte lcdD5Pin = 10;
const byte lcdD6Pin = 9;
const byte lcdD7Pin = 8;



// initialize the library by associating any needed LCD interface pin
// with the arduino pin number it is connected to
LiquidCrystal lcd(lcdRSPin, lcdEnablePin, lcdD4Pin, lcdD5Pin, lcdD6Pin, lcdD7Pin);

void setup() {
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  // Print a message to the LCD.
  lcd.print("hello, world!");
}

void loop() {
  // set the cursor to column 0, line 1
  // (note: line 1 is the second row, since counting begins with 0):
  lcd.setCursor(0, 1);
  // print the number of seconds since reset:
  lcd.print(millis() / 1000);
}



/*
const byte interruptPin = 2;
const byte d0Pin = 6;
const byte d1Pin = 5;
const byte d2Pin = 4;
const byte d3Pin = 3;
const byte motorRelayPin = 7;
const byte dryRunPin = A4;
const byte lowVoltPin = A3;
const byte voltPresentPin = A2;
const byte alarmLightPin = 11;
const byte alarmBuzzerPin = 12;
const byte motorONPin = A0;
const byte motorOFFPin = A1;

//volatile byte state = LOW;

volatile bool b[4];
volatile bool d[4];
volatile bool batLow = false;
volatile bool solarCharg = false;

bool dryRunFlag = false;
bool lowVoltFlag = false;
bool voltPresentFlag = false;
bool waterLvlLowFlag = false;
//bool waterLvlHighFlag = false;
bool manualOnFlag = false;
bool manualOffFlag = false;
bool motorStateMemoryFlag = false;
bool motorPinStatusFlag = false;
bool pwrFailFlag = false;
bool error = false;

bool motorStateMemory = false;
bool dryRun = false;
bool lowVolt = false;
bool voltPresent = false;
int waterLvl = 0;

unsigned long previousMills0 = 0;
unsigned long currentMills0 = 0;
unsigned long previousMills1 = 0;
unsigned long currentMills1 = 0;
unsigned long previousMills2 = 0;
unsigned long currentMills2 = 0;
unsigned long previousMills3 = 0;
unsigned long currentMills3 = 0;

int dryrunCounter = 0; 
int lowVoltCounter = 0;
int voltPresentCounter = 0;
int voltPresentCounter1 = 0;

void setup() {
  pinMode(motorONPin, INPUT);
  pinMode(motorOFFPin, INPUT);
  pinMode(d0Pin, INPUT);
  pinMode(d1Pin, INPUT);
  pinMode(d2Pin, INPUT);
  pinMode(d3Pin, INPUT);
  pinMode(dryRunPin, INPUT);
  pinMode(lowVoltPin, INPUT);
  pinMode(voltPresentPin, INPUT);
  pinMode(motorRelayPin, OUTPUT);
  pinMode(alarmLightPin, OUTPUT);
  pinMode(alarmBuzzerPin, OUTPUT);

  pinMode(interruptPin, INPUT);
  attachInterrupt(digitalPinToInterrupt(interruptPin), interupt, RISING);
  Serial.begin(9600);
}

void loop() {
 pwrBordReading();
                                                                                                         Serial.print("flags are dryrun, lowvolt, voltpresent: ");
                                                                                                         Serial.print(dryRunFlag);Serial.print("  ");Serial.print(lowVoltFlag);Serial.print("  ");Serial.println(voltPresentFlag);

// comapring the waterlevel and saving to an variable waterLvl
 if(!d[3] && !d[2] && !d[1] && d[0])  waterLvl = 0;
 else if (!d[3] && !d[2] && d[1] && !d[0])  waterLvl = 1;
 else if (!d[3] && !d[2] && d[1] && d[0])  waterLvl = 2;
 else if (!d[3] && d[2] && !d[1] && !d[0])  waterLvl = 3;
 else if (!d[3] && d[2] && !d[1] && d[0])  waterLvl = 4;
 else if (!d[3] && d[2] && d[1] && !d[0])  waterLvl = 5;
 else if (!d[3] && d[2] && d[1] && d[0])  waterLvl = 6;
 else if (d[3] && !d[2] && !d[1] && !d[0])  waterLvl = 7;
 else if (d[3] && !d[2] && !d[1] && d[0])  waterLvl = 8;
 else if (d[3] && !d[2] && d[1] && !d[0])  waterLvl = 9;

                                                                                                         Serial.print("tank level is ");
                                                                                                         Serial.println(waterLvl);

// reading manual switches saving status to variable manualOnFlag
 bool switchON = digitalRead(motorONPin);
 if (switchON) manualOnFlag = true;
 bool switchOFF = digitalRead(motorOFFPin);
 if (switchOFF){                                                                 // manual off disabling all the motor on flags
   manualOnFlag = false;
   waterLvlLowFlag = false;
 }

 // checking waterlevel for setting and resetting the flags
 if(waterLvl == 1 || waterLvl == 0) waterLvlLowFlag = true;
 else if (waterLvl == 9) {                                                       // tank full disable all the motor on flags
  waterLvlLowFlag = false;
  manualOnFlag = false;
 }

                                                                                                        Serial.print("flags are manualOn, waterLvlLow: ");
                                                                                                        Serial.print(manualOnFlag);Serial.print("  ");Serial.println(waterLvlLowFlag);



// motor on section

if(waterLvlLowFlag || manualOnFlag) motorStateMemory = true;                   // variable for entering the code for turning on pump motor
else motorStateMemory = false;

if (motorStateMemory){                                                         // entering to the pump on codes
  if(!dryRunFlag && !lowVoltFlag && voltPresentFlag){                          // checking all the flags before turning on the motor
      digitalWrite(motorRelayPin, HIGH);
      motorPinStatusFlag = true;
      error = false;
      Serial.println("inside on");
  }
  else{
    digitalWrite(motorRelayPin, LOW);
    motorPinStatusFlag = false;
    error = true;
  }
}
else {
  digitalWrite(motorRelayPin, LOW);
  motorPinStatusFlag = false;
  Serial.print("inside off");
}







  Serial.println("-----------------------------------------------------------------------------------------------------------------------------------------");
 delay(1000);




} */
