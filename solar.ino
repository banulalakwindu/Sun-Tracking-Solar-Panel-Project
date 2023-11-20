#include <Servo.h>

Servo myservo;
int ldr1 = 14;
int ldr2 = 15;
int val1;
int val2;
int pos = 90;

void setup() {
  myservo.attach(11);
  myservo.write(pos);
  Serial.begin(9600);
}

void loop() {
  val1 = analogRead(ldr1);
  // Serial.print("Val 1 - ");
  Serial.print(val1);
  Serial.print(" ");
  // Serial.print("Val 2 - ");
  val2 = analogRead(ldr2);
  Serial.print(val2);
  Serial.println();

  if (val1 > (val2 + 200)) {
    if (pos < 180)
      pos = pos + 1;
    myservo.write(pos);
    delay(200);
  } else if (val2 > (val1 + 200)) {
    if (pos > 0)
      pos = pos - 1;
    myservo.write(pos);
    delay(200);
  }
}
