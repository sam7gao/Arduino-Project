#define LED_PIN 8
#define BUTTON_PIN_LED 7

byte lastButtonState_LED;
byte buttonState_LED;
byte ledState_LED = LOW; 
bool buttonPressed_LED = false; 
unsigned long previousMillis_LED = 0;
const long interval_LED = 1000;
const long loopDuration_LED = 500;

#include <Servo.h>

Servo Servo1;
Servo servo2;

#define servoPin_Push 2 
#define buttonPin_Servo 3 
#define servoPin_Pot 9 
#define potPin  A0 

int buttonState_Servo = 0; 
int lastButtonState_Servo = 0; 
bool servoMoving_Servo = false; 
bool buttonStateChanged_Servo = false; 
int servoAngle_Servo = 25; 
int servoIncrement_Servo = 20; 
int servoDelay_Servo = 1000; 

void setup() {
  //LED 
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUTTON_PIN_LED, INPUT);
  lastButtonState_LED = digitalRead(BUTTON_PIN_LED);
  digitalWrite(LED_PIN, LOW); 

  //servo2
  servo2.attach(servoPin_Push);
  pinMode(buttonPin_Servo, INPUT_PULLUP); 
  //servo1
  Servo1.attach(servoPin_Pot);
}

void loop() {
  // LED 
  unsigned long currentMillis_LED = millis();
  buttonState_LED = digitalRead(BUTTON_PIN_LED);
  
  if (buttonState_LED != lastButtonState_LED) {
    lastButtonState_LED = buttonState_LED;
    if (buttonState_LED == LOW) {
      buttonPressed_LED = true; 
    }
  }
  
  if (buttonPressed_LED) {
    if (ledState_LED == LOW && currentMillis_LED - previousMillis_LED >= loopDuration_LED) {
      ledState_LED = HIGH;
      digitalWrite(LED_PIN, HIGH);
      previousMillis_LED = currentMillis_LED;
    }
    
    if (ledState_LED == HIGH && currentMillis_LED - previousMillis_LED >= interval_LED) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      previousMillis_LED = currentMillis_LED;
    }
  }

  // Servo1
  int reading = analogRead(potPin);
  int angle = map(reading, 0, 1023, 0, 180);
  Servo1.write(angle);

  // Servo2
  unsigned long currentMillis_Servo = millis();
  buttonState_Servo = digitalRead(buttonPin_Servo);
  
  if (buttonState_Servo != lastButtonState_Servo) {
    buttonStateChanged_Servo = true; 
  }


  //20 deg loop
  if (!servoMoving_Servo) {
    servoAngle_Servo += servoIncrement_Servo;
    if (servoAngle_Servo >= 25 || servoAngle_Servo <= 0) {
      servoIncrement_Servo *= -1;
    }
    servo2.write(servoAngle_Servo);
    delay(servoDelay_Servo);
  }
}
