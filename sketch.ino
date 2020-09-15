#include <stdbool.h>

const int buttonPin = 2;     // the number of the pushbutton pin
const int greenPin =  13; 
const int yellowPin = 12;
const int redPin = 11;


int trafficLightState = 0; // 0: Green, 1: Transitioning, 2: Red
bool lastButtonStateIsPressed = false;
bool buttonIsPressed = false;

void onlyTurnOn(int pin) {
  switch (pin) {
    case greenPin:
      digitalWrite(greenPin, HIGH);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, LOW);
      break;
     case yellowPin:
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, HIGH);
      digitalWrite(redPin, LOW);
      break;
     case redPin:
      digitalWrite(greenPin, LOW);
      digitalWrite(yellowPin, LOW);
      digitalWrite(redPin, HIGH);
      break;
  }
}

void handleTrafficState() {
  switch (trafficLightState % 3) {
    case 0:
      onlyTurnOn(greenPin);
      break;
    case 2: 
      onlyTurnOn(redPin);
      break;
    default:
      delay(1000);
      onlyTurnOn(yellowPin);
      delay(3000);
      onlyTurnOn(redPin);
      trafficLightState = 2;
      break;
  }
}

void handleButtonPress() {
  buttonIsPressed = digitalRead(buttonPin);
  if (buttonIsPressed && !lastButtonStateIsPressed) {
    trafficLightState++;
  }
  lastButtonStateIsPressed = buttonIsPressed;
}

void setup() {
  // put your setup code here, to run once:
  pinMode(greenPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(redPin, OUTPUT);
  pinMode(buttonPin, INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  handleTrafficState();
  handleButtonPress();
}
