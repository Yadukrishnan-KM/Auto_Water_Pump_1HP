#define ultrasonicechoPin 11 // attach pin D2 Arduino to pin Echo of JSN-SR04T
#define ultrasonicTrigPin 10 //attach pin D3 Arduino to pin Trig of JSN-SR04T
#define ultrasonicPwrPin 9
float depthTolerance = .10;

// defines variables
long duration; // variable for the duration of sound wave travel
int depth; // variable for the distance measurement

void setup() {
  pinMode(ultrasonicTrigPin, OUTPUT); // Sets the trigPin as an OUTPUT
  pinMode(ultrasonicechoPin, INPUT); // Sets the echoPin as an INPUT
  Serial.begin(9600); // // Serial Communication is starting with 9600 of baud rate speed
  Serial.println("Ultrasonic Sensor HC-SR04 Test"); // print some text in Serial Monitor
  Serial.println("with Arduino UNO R3");
}
void loop() {

  digitalWrite(ultrasonicTrigPin, LOW);                                // measurements
     delayMicroseconds(2);
     digitalWrite(ultrasonicTrigPin, HIGH);
     delayMicroseconds(20);
     digitalWrite(ultrasonicTrigPin, LOW);
     duration = pulseIn(ultrasonicechoPin, HIGH);
     depth = (duration*.0343)/2;
     delay(100);    
                                                                                 Serial.print("ultrasonic read successful final depth is :");
                                                                            Serial.println(depth);   
}


