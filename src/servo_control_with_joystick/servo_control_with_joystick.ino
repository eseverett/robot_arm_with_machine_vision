#include <Servo.h>
#include <LiquidCrystal.h>

Servo servo;
int pos = 0; 
const int servo_signal_pin = 9;
const int x_axis_pin = A0;
const int switchPin = 6;
int lastButtonState = HIGH; // Changed to HIGH for INPUT_PULLUP
unsigned long lastDebounceTime = 0;
unsigned long debounceDelay = 50;
bool buttonPressed = false;

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void setup() {
  servo.attach(servo_signal_pin);
  pinMode(switchPin, INPUT_PULLUP); 
  Serial.begin(9600);
  lcd.begin(16, 2);
  lcd.print("- Starting -");
  delay(2000);  // Delay to read the start message
  lcd.clear();
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

  static int lastPos = -1; // Store last position to minimize LCD updates
  if (lastPos != pos) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("Pos: ");
    lcd.print(pos);
    lcd.setCursor(0, 1);
    lastPos = pos;
  }

  delay(10); 
}

void move_servo() {
  int x_value = analogRead(x_axis_pin);
  pos = (int)x_value / 5.667;
  servo.write(pos);
}

void button_click() {
  // testing sweep
  for (int tempPos = 0; tempPos <= 180; tempPos += 1) {
    servo.write(tempPos);
    delay(15);
  }
  for (int tempPos = 180; tempPos >= 0; tempPos -= 1) {
    servo.write(tempPos);
    delay(15);
  }
}
