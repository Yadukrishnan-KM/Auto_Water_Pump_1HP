float ultrasonicRead(){
  float depth[3];
  float duration, finalDepth ;
  bool trueDepthFlag;
  long previousMillis = millis();
  long currentMillis = 0;
  long timeout = 10000;

  trueDepthFlag = false;                                                  // to ensure it will go through the while loop atleast once
  digitalWrite(ultrasonicPwrPin, HIGH);                                   // to turn on the ultrasonic sensor module
  delay(100);                                                             // to settlw down the module
  while(!trueDepthFlag){                                                  // to find the true value by measuring multiple times
   delay(100);
                                                                          //Serial.println("inside while loop");
   for (int i = 0; i <= 2; i++) {                                         // to meausre 3 times sequencly
                                                                          //Serial.println("inside for loop");
     digitalWrite(ultrasonicTrigPin, HIGH);                                // measurements
     delayMicroseconds(2);
     digitalWrite(ultrasonicTrigPin, LOW);
     delayMicroseconds(15);
     digitalWrite(ultrasonicTrigPin, HIGH);
     duration = pulseIn(ultrasonicechoPin, HIGH);
     depth[i] = (duration*.0343)/2;
     delay(100);                                                          // important delay do not remove other wise faluty reading
    }
   finalDepth = (depth[0]+depth[1]+depth[2])/3;                           // find average of 3 values
                                                                          Serial.print("Inside ultrasonic read while loop final depth is :");
                                                                          Serial.println(finalDepth);
                                                                          Serial.print(" depth0 is :");
                                                                          Serial.println(depth[0]);
                                                                          Serial.print(" depth1 is :");
                                                                          Serial.println(depth[1]);
                                                                          Serial.print(" depth2 is :");
                                                                          Serial.println(depth[2]);
   if (finalDepth <= (depth[1]-(depth[1]*depthTolerance)) || finalDepth >= (depth[1]+(depth[1]*depthTolerance)) ) {             // to find the final value is true or not
     trueDepthFlag = false;                                               // ensure while loop again
                                                                          //Serial.println("final depth is false");
     }
   else {
    if (finalDepth >= 300) trueDepthFlag = false;
    else trueDepthFlag = true;                                                // exit while loop
                                                                          Serial.println("inside else");
    }
     currentMillis = millis();
     if((currentMillis - previousMillis) >= timeout) trueDepthFlag = true;    // for avoiding infine running of while loop, timeout is 10sec

  }
  digitalWrite(ultrasonicPwrPin, LOW);
                                                                            Serial.print("ultrasonic read successful final depth is :");
                                                                            Serial.println(finalDepth);
  return finalDepth;                                  // turn off ultrasonic sensor module
                                                                          //Serial.print("depth: ");
                                                                          //Serial.println(finalDepth);
}