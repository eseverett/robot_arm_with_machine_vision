#include <Servo.h>

Servo servo;

int pos = 0; // global position variable
const int servo_signal_pin = 9; // pulse signal source pin

const int x_axis_pin = A0;
const int y_axis_pin = A1;
int x_value = 0;
int y_value = 0;
const int switchPin = 6; 
int button_pressed = 0;

void setup() {
  // put your setup code here, to run once:
  servo.attach(servo_signal_pin);

  pinMode(switchPin, INPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
  move_servo();

  if (digitalRead(switchPin)) {
    button_click();
  }

  Serial.println(pos);
  delay(100);
}

void move_servo() {
  x_value = analogRead(x_axis_pin);
  pos = (int) x_value / 5.667;
  servo.write(pos);
}

void button_click() {
  for (pos = 0; pos <= 180; pos += 1) { 

    servo.write(pos);              

    delay(15);                       

  }

  for (pos = 180; pos >= 0; pos -= 1) { 

    servo.write(pos);              

    delay(15);                       

  }
}

