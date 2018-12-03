#include <Servo.h>

//Pin connections
const int Infra_pin = 2;        // Digital pin for IR sensor
const int mq_pin = A0;      // Analog pin for MQ135 gas sensor
const int induct_pin = 3; // Digital pin for inductive proximity sensor
const int dc_ACW = 4;        // Digital pin for DC motor driver anti-clockwise
const int dc_CW = 5;        // Digital pin for DC motor driver clockwise 
const int servo_pin1 = 6;          // Digital pin for first servo motor
const int servo_pin2 = 7;          // Digital pin for second servo motor
const int detection = 300;     // Gas sensor threshold value

Servo servo1;
Servo servo2;

void setup() {
  Serial.begin(9600);

  pinMode(Infra_pin, INPUT);
  pinMode(mq_pin, INPUT);
  pinMode(induct_pin, INPUT);
  pinMode(dc_ACW, OUTPUT);
  pinMode(dc_CW, OUTPUT);

  servo1.attach(servo_pin1);
  servo2.attach(servo_pin2);

  servo1.write(0);
  servo2.write(0);
}

void loop() {
  int irValue = digitalRead(Infra_pin);

  // This functionality is responsible in carrying opening and closing mechanism of the dustbin
  if (irValue == HIGH) {

    digitalWrite(dc_ACW, HIGH);
    digitalWrite(dc_CW, LOW);
    delay(3000);
    digitalWrite(dc_CW,HIGH);
    digitalWrite(dc_ACW,LOW);
  } else {

    digitalWrite(dc_ACW, LOW);
    digitalWrite(dc_CW, LOW);
  }

  int gasValue = analogRead(mq_pin);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasValue);

  // Controls servo motor based on gas sensor value which ensures if the waste is organic decaying or not
  if (gasValue < detection) {
  
    servo1.write(120);
    delay(1000);

    int induct_val = digitalRead(induct_pin);

    // Controls second servo motor based on inductive sensor value. It is responsible for metal and non metal segregation
    if (induct_val == LOW) {
      servo2.write(120);
      delay(1000); 
    }
  } else {

    servo1.write(0);
  }

  delay(500);
}
