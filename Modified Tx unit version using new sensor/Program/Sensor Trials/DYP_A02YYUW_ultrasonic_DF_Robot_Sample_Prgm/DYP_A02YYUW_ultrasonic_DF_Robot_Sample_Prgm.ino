/*
  *@File  : DFRobot_Distance_A02.ino 
  *@Brief : This example use A02YYUW ultrasonic sensor to measure distance
  *         With initialization completed, We can get distance value 
  *@Copyright [DFRobot](https://www.dfrobot.com),2016         
  *           GUN Lesser General Pulic License
  *@version V1.0           
  *@data  2019-8-28
*/

#include <SoftwareSerial.h>

SoftwareSerial mySerial(11,10); // RX, TX
unsigned char data[4]={};
float distance;

void setup()
{
 Serial.begin(57600);
 mySerial.begin(9600); 
}

void loop()
{
  unsigned char data[4]={0};
float distance = 0;
    do{
     for(int i=0;i<4;i++)
     {
       data[i]=mySerial.read();
     }
  }while(mySerial.read()==0xff);

  mySerial.flush();

  if(data[0]==0xff)
    {
      int sum;
      sum=(data[0]+data[1]+data[2])&0x00FF;
      if(sum==data[3])
      {
        distance=(data[1]<<8)+data[2];
        if(distance>30)
          {
           Serial.print("distance=");
           Serial.print(distance/10);
           Serial.println("cm");
          }else 
             {
               Serial.println("Below the lower limit");
             }
      }else Serial.println("ERROR");
     }else Serial.println("Sart byte ERROR");
     delay(100);
}