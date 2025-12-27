#ifndef LEDMATRIX_CONTROL_H
#define LEDMATRIX_CONTROL_H

#include <Arduino_LED_Matrix.h>

//Initialization
void setupLEDMatrix();

//Movement icons
void ledShowForward();
void ledShowBackward();
void ledShowLeft();
void ledShowRight();
void ledShowStop();

//Mode icons
void ledShowHoldMode();
void ledShowOnePressMode();

//speed icons
void ledShowPlus();
void ledShowMinus();

//heart
void ledShowHeart();

#endif