#include "kxnTask_DCmotor_Khanh.h"
kxnTask_DCmotor dcmotor;
String inputText, outputText;

void setup() {
  Serial.begin(9600);
  dcmotor.setup(5, 7, 4, 45, 100);
  // dcmotor.write(40);
  // dcmotor.write_for(35, 5000);
}
void loop() {
  checkSerial();
  // Serial.println(map(analogRead(A1),0,674,-100,100));
  // dcmotor.write(map(analogRead(A1),0,674,-100,100));
  kxnTaskManager.run(millis());
}
void checkSerial() {
  if (Serial.available()) {
    inputText = Serial.readStringUntil('\n');
    Serial.println(inputText);
    // outputText = inputText.trim();
    // inputText.trim();
    // outputText=inputText;
    dcmotor.write_for(inputText.toInt(), 5000);
  }
}
