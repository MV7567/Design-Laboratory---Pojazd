#ifndef BLE_CONTROL_H
#define BLE_CONTROL_H

#include <ArduinoBLE.h>

//init ble & start advertising
void setupBLE();

//check for ble connection and new command
//return "" if nothing new
String checkBLE();

#endif
