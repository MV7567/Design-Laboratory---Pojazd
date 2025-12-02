#include <Arduino.h>
#include "motor_control.h"
#include "ble_control.h"

int speedValue = 150;

void setup() {
  Serial.begin(9600);
  setupMotors();
  setupBLE();

  Serial.println("System ready.");
}

void loop(){
  BLE.poll();
  delay(1);

  String cmd = checkBLE();

  if (cmd != "") { //only act on new commands
    cmd.trim();

    if (cmd == "F") {
      Serial.println("Moving Forward");
      moveForward(speedValue);
    }
    else if (cmd == "B") {
      Serial.println("Moving Backward");
      moveBackward(speedValue);
    }
    else if (cmd == "L"){
      Serial.println("Turning left");
      turnLeft(speedValue);
    }
    else if (cmd == "R") {
      Serial.println("Turning right");
      turnRight(speedValue);
    }
    else if (cmd == "S") {
      Serial.println("Stop");
      stopMotors();
    }
    else {
      Serial.println("Unknown command: ");
      Serial.println(cmd);
    }
  }
  //delay(5); //ble stability??
}