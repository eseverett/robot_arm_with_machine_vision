#include <Servo.h>

Servo servo;

int pos = 0; // global position variable
const int servo_signal_pin = 9; // pulse signal source pin
const int x_axis_pin = A0;
const int y_axis_pin = A1;
int x_value = 0;
int y_value = 0;
const int switchPin = 6;
int lastButtonState = LOW; 
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool buttonPressed = false;

void setup() {
  servo.attach(servo_signal_pin);
  pinMode(switchPin, INPUT); 
  Serial.begin(9600);
}

void loop() {
  move_servo();
  int reading = digitalRead(switchPin);

  if (reading != lastButtonState) {
    lastDebounceTime = millis();
  }

  if ((millis() - lastDebounceTime) > debounceDelay) {
    if (reading != buttonPressed) {
      buttonPressed = reading;
      if (buttonPressed == LOW) { // Check for button press (button is active low)
        button_click();
      }
    }
  }
  
  lastButtonState = reading;
  delay(10); 
}

void move_servo() {
  x_value = analogRead(x_axis_pin);
  pos = (int)x_value / 5.667;
  servo.write(pos);
}

void button_click() {
  // testing sweep
  for (pos = 0; pos <= 180; pos += 1) {
    servo.write(pos);
    delay(15);
  }
  for (pos = 180; pos >= 0; pos -= 1) {
    servo.write(pos);
    delay(15);
  }
}
