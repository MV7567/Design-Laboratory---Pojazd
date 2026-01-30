#ifndef MOTOR_CONTROL_H
#define MOTOR_CONTROL_H

//Pin assignments for L298N driver

// Motor A (left)
#define ENA 5
#define IN1 6
#define IN2 7

// Motor B (right)
#define IN3 8
#define IN4 9
#define ENB 10

//Functions
void setupMotors();
void moveForward(int speed);
void moveBackward(int speed );
void turnLeft(int speed);
void turnRight(int speed);
void stopMotors();

#endif