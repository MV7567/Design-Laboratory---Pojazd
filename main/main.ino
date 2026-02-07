#include <Arduino.h>
#include "motor_control.h"
#include "ble_control.h"
#include "Arduino_LED_Matrix.h"
#include "LEDmatrix_control.h"
#include "sensor_control.h"

//ArduinoLEDMatrix matrix;

//---------------- SETTINGS ----------------

int speedValue = 150;        // initial speed
const int SPEED_STEP = 25;   // step for +/-

bool holdModeEnabled = false; //false = ones-press mode, true = hold-to-move

//timeout
char activeCmd = 0;
unsigned long lastCmdTime = 0;
const unsigned long CMD_TIMEOUT = 300; //ms

//---------------- SETUP ----------------
void setup() {
  Serial.begin(9600);

  setupLEDMatrix();
  setupMotors();
  setupBLE();
  setupSensor();

}

//---------------- LOOP ----------------
void loop() {
  BLE.poll(); //keep BLE alive
  delay(1); //prevent BLE starvation

  long distance = getDistance();

  // CRITICAL SAFETY CHECK
  if (distance < 15 && activeCmd == 'F') { 
    stopMotors();
    ledShowStop();
    activeCmd = 'S'; // Force stop state
    Serial.println("OBSTACLE DETECTED - EMERGENCY BRAKE");
  }


//update current command
  String cmd = checkBLE();
  if (cmd.length() > 0) {
    char c = cmd.charAt(0);

    // ---------- MODE TOGGLE ----------
    if (c == 'T'){
      holdModeEnabled = !holdModeEnabled;
      stopMotors();
      activeCmd = 0;

      if (holdModeEnabled){
        ledShowHoldMode();
      } else {
        ledShowOnePressMode();
      }
      return;
    }

    //---------- SPEED CONTROL ----------
    if (c == '+') {
      speedValue = min(speedValue + SPEED_STEP, 255);
      ledShowPlus();
    } 
    else if (c == '-') {
      speedValue = max(speedValue - SPEED_STEP, 0);
      ledShowMinus();
    } 
    //---------- MOVEMENT ----------
    else {
      activeCmd = c;
      lastCmdTime = millis();
    }
  }

  //---------- HOLD MODE TIMEOUT ----------
  if(holdModeEnabled && activeCmd != 0){
    if(millis() - lastCmdTime > CMD_TIMEOUT){
      stopMotors();
      activeCmd = 0;
      return;
    }
  }


  //---------- EXECUTE MOVEMENT ----------
  switch (activeCmd) {
    case 'F': 
      moveForward(speedValue);
      ledShowForward(); 
      break;
    
    case 'B': 
      moveBackward(speedValue);
      ledShowBackward(); 
      break;

    case 'L': 
      turnLeft(speedValue);
      ledShowLeft(); 
      break;

    case 'R': 
      turnRight(speedValue);
      ledShowRight(); 
      break;
    
    case 'S': 
      stopMotors();
      ledShowStop();
      break;
  }
}
