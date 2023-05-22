#include <Servo.h>

const int flexPin[5] = {A0, A1, A2, A3, A4};

// Change these constants according to your project's design
const float VCC = 5;      // voltage at Ardunio 5V line
const float R_DIV = 10000.0;  // resistor used to create a voltage divider
const float flatResistance = 25000.0; // resistance when flat
const float bendResistance = 60000.0;  // resistance at 90 deg
#include <Servo.h>

Servo myservo[5]; 
void setup() {
  Serial.begin(9600);
  for(int i = 0; i < 5; i++){
    pinMode(flexPin[i], INPUT);  
  }
  

  myservo[0].attach(5);
  myservo[1].attach(6);
  myservo[2].attach(9);
  myservo[3].attach(10);
  myservo[4].attach(11);
}

void loop() {
  for(int i = 0; i < 5; i++){
    int ADCflex = analogRead(flexPin[i]);
    float Vflex = ADCflex * VCC / 1023.0;
    float Rflex = R_DIV * (VCC / Vflex - 1.0);
    Serial.println("Resistance" + String(i) + ": " + String(Rflex) + " ");
    Serial.println(ADCflex);
    float angle = map(Rflex, flatResistance, bendResistance, 0, 90.0);
    Serial.println("Bend: " + String(angle) + " degrees");
    Serial.println(); 
    if(angle > 0){
        myservo[i].write(angle * 2);
    }
    if(angle > 90 and angle < 360){
      myservo[i].write(180);
    }
  }
  delay(2000);
}
