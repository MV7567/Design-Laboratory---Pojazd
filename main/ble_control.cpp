#include "ble_control.h"
#include <Arduino.h>

BLEService carService("108A"); //random UUID
BLEStringCharacteristic commandCharacteristic("2A57", BLEWrite, 20);

void setupBLE(){
  Serial.begin(9600);
  while (!Serial);

  if (!BLE.begin()){
    Serial.println("Starting BLE failed!");
    while(1);
  }

  BLE.setLocalName("RC_Car");
  BLE.setAdvertisedService(carService);

  carService.addCharacteristic(commandCharacteristic);
  BLE.addService(carService);

  commandCharacteristic.writeValue("STOP");
  BLE.advertise();

  Serial.println("BLE RC Car ready, waiting for connection...");
}

String checkBLE(){
  static BLEDevice central = BLEDevice(); //remember current central device
  static bool connected = false;

  BLEDevice device = BLE.central();

  if (device && !connected){
    Serial.print("Connected to: ");
    Serial.println(device.address());
    connected = true;
  }

  if (!device && connected){
    Serial.println("Disconnected");
    connected = false;
  }

  if(commandCharacteristic.written()){
    String cmd = commandCharacteristic.value();
    Serial.print("Command: ");
    Serial.println(cmd);
    return cmd;
  }
  return ""; //no new command
}
