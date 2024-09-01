#include "kxnTask_DCmotor_Khanh.h"
kxnTask_DCmotor dcmotor;


void setup() {
  Serial.begin(9600);
  dcmotor.setup(5, 7, 4,70,10);
  // dcmotor.write(40);
  // dcmotor.write_for(35, 5000);
}
void loop() {
  // Serial.println(map(analogRead(A1),0,674,-100,100));
  // dcmotor.write(map(analogRead(A1),0,674,-100,100));
  kxnTaskManager.run(millis());
}

