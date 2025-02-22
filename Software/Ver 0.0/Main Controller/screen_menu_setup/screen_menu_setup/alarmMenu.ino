void alarmMenu(){
     switch(alarmSelectionCaseNo){
     case 1: 
     lcd.setCursor(6,1); lcd.print("OFF  ");
     break;
     case 2:
      lcd.setCursor(5,1); lcd.print("6");
     break;
     case 3:
      lcd.setCursor(5,1); lcd.print("8");
     break;
     case 4:
      lcd.setCursor(5,1); lcd.print("12");
     break;
     case 5:
      lcd.setCursor(5,1); lcd.print("24");
     break;
     default:
     pumpScheduleTimeSetting = 1; // to back to default if any error
     break;
   }
}