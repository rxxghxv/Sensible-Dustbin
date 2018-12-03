
const int gasSensorPin = A0;
const int buzzerPin = 9;     

const int detection = 300; 

void setup() {
  
  Serial.begin(9600);

  pinMode(buzzerPin, OUTPUT);
  
  pinMode(gasSensorPin, INPUT);
}

void loop() {
 
  int gasSensorValue = analogRead(gasSensorPin);

  Serial.print("Gas Sensor Value: ");
  Serial.println(gasSensorValue);

  
  if (gasSensorValue > detection) {
    
    digitalWrite(buzzerPin, HIGH);
  } else {
   
    digitalWrite(buzzerPin, LOW);
  }

  delay(500);
}
