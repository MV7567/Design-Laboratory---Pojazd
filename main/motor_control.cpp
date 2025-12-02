#include <Arduino.h>
#include "motor_control.h"

//configure pins as outputs
void setupMotors(){
  pinMode(ENA, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);
}
//both motors forward
void moveForward(int speed){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}
//both motors in reverse
void moveBackward(int speed) {
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void turnLeft(int speed){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH); //stop left motor

  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW); //run rigth motor forward

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void turnRight(int speed){
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW); //stop right motor

  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH); //run left motor forward

  analogWrite(ENA, speed);
  analogWrite(ENB, speed);
}

void stopMotors(){
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, LOW);
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, LOW);

  analogWrite(ENA, 0);
  analogWrite(ENB, 0);
}






