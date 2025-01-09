#include <Arduino.h>

void setup() {
  Serial1.begin(9600);
}
void loop() {
  Serial1.print("on");
  delay(3000);
  Serial1.print("off");
  delay(3000);
}
