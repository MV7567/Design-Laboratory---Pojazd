#include <Arduino.h>
#include "motor_control.h"
#include "ble_control.h"
#include "Arduino_LED_Matrix.h"

ArduinoLEDMatrix matrix;

int speedValue = 150;        // initial speed
const int SPEED_STEP = 25;   // step for +/-

String currentCmd = "";      // latest command from BLE

//timeout
unsigned long lastCommandTime = 0;
const unsigned long COMMAND_TIMEOUT = 200; //ms

// heart
uint8_t heart[8][12] = {
  {0,0,0,1,0,0,0,0,1,0,0,0},
  {0,0,1,1,1,0,0,1,1,1,0,0},
  {0,1,1,1,1,1,1,1,1,1,1,0},
  {0,1,1,1,1,1,1,1,1,1,1,0},
  {0,0,1,1,1,1,1,1,1,1,0,0},
  {0,0,0,1,1,1,1,1,1,0,0,0},
  {0,0,0,0,1,1,1,1,0,0,0,0},
  {0,0,0,0,0,1,1,0,0,0,0,0}
};

void setup() {
  matrix.begin();
  matrix.renderBitmap(heart, 12, 8);

  Serial.begin(9600);
  setupMotors();
  setupBLE();

  Serial.println("System ready.");
}

void loop() {
  BLE.poll();   // keep BLE alive
  delay(1);     // prevent BLE starvation

  // update current command if a new one arrives
  String cmd = checkBLE();
  if (cmd != "") {
    cmd.trim();

    // speed adjustment commands
    if (cmd == "+") {
      speedValue += SPEED_STEP;
      if (speedValue > 255) speedValue = 255;
      Serial.print("Speed increased to: ");
      Serial.println(speedValue);
    } 
    else if (cmd == "-") {
      speedValue -= SPEED_STEP;
      if (speedValue < 0) speedValue = 0;
      Serial.print("Speed decreased to: ");
      Serial.println(speedValue);
    }
    else {
      // movement commands
      currentCmd = cmd;
      lastCommandTime = millis(); //timestamp
    }
  }

  //if last command is too old, stop motors
  if(millis() - lastCommandTime > COMMAND_TIMEOUT){
    stopMotors();
    currentCmd = "";
  } else {
    // execute movement based on currentCmd
    if (currentCmd == "F") moveForward(speedValue);
    else if (currentCmd == "B") moveBackward(speedValue);
    else if (currentCmd == "L") turnLeft(speedValue);
    else if (currentCmd == "R") turnRight(speedValue);
  }
}
