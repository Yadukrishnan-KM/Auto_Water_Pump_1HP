//************************************************ homescreen updation codes *************************************************************
/*void homeScreen(){

   //refreshing with all the required data which save in eeprom when it is in home screen, default screen
   pumpOperationModeSetting = EEPROM.read(1);
   pumpScheduleTimeSetting = EEPROM.read(2);
   lowVoltCutoffSetting = EEPROM.read(3);
   pumpAoffTimerSetting = EEPROM.read(4);
   dryrunCutoffSetting = EEPROM.read(5);
   brightValueSetting = EEPROM.read(6);
   brightValue = EEPROM.read(7);

   lcd.clear();
   
   lcd.setCursor(0,0); lcd.print("** LEVEL"); lcd.setCursor(9,0); lcd.print(waterLvl); lcd.setCursor(12,0); lcd.print("% **"); // main lavel indication
   if(!voltPresent) {lcd.setCursor(0,1); lcd.write(0);}                                  // ac present and good symbol
   if(!voltPresent && lowVolt) {lcd.setCursor(1,1); lcd.write(1);}                       // some issue symbol
   if(motorPinStatusFlag) {lcd.setCursor(3,1); lcd.write(2);}                            // pump running and good symbol
   if(motorPinStatusFlag && dryRun) {lcd.setCursor(4,1); lcd.write(1);}                  // some issue symbol
   if(pumpScheduleTimeSetting != 1) {lcd.setCursor(6,1); lcd.write(6);}                  // timer enable symbol
   //lcd.setCursor(8,1); lcd.write(3);                                                     // alarm present symbol
   if(pumpOperationModeSetting) {lcd.setCursor(10,1); lcd.write(7);}                     // auto operation symbol
   if(batV >= 3900) lcd.setCursor(12,1); lcd.write(4);                                   // battery good symbol
   //lcd.setCursor(13,1); lcd.write(1);                                                    // some issue symbol
   if(!transmitterError) {lcd.setCursor(14,1); lcd.write(5);}                            // transmitter good symbol
   if(batLow || !solarCharg) {lcd.setCursor(15,1); lcd.write(1);}                        // some issue symbol
   }*/