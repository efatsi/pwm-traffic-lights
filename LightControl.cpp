/*
  LightControl.h - Library for controlling two LED strips with PWM.
  Created by Elias S. Fatsi, August 30, 2014.
  Released into the public domain.
*/

#include "LightControl.h"

LightControl::LightControl(
  int littleRedPin,
  int littleGreenPin,
  int littleBluePin,
  int largeRedPin,
  int largeGreenPin,
  int largeBluePin)
{
  _littleRedPin   = littleRedPin;
  _littleGreenPin = littleGreenPin;
  _littleBluePin  = littleBluePin;
  _largeRedPin    = largeRedPin;
  _largeGreenPin  = largeGreenPin;
  _largeBluePin   = largeBluePin;

  _min            = 0;
  _littleMax      = 40;
  _largeMax       = 200;

  _fadeSpeed = 15;

  pinMode(littleRedPin,   OUTPUT);
  pinMode(littleGreenPin, OUTPUT);
  pinMode(littleBluePin,  OUTPUT);

  pinMode(largeRedPin,   OUTPUT);
  pinMode(largeGreenPin, OUTPUT);
  pinMode(largeBluePin,  OUTPUT);
}


void LightControl::initialize()
{
  analogWrite(_littleRedPin,   OUTPUT);
  analogWrite(_littleGreenPin, OUTPUT);
  analogWrite(_littleBluePin,  OUTPUT);

  analogWrite(_largeRedPin,   OUTPUT);
  analogWrite(_largeGreenPin, OUTPUT);
  analogWrite(_largeBluePin,  OUTPUT);
}

void LightControl::display(String light, String command)
{
  int min = _min;
  int redPin;
  int greenPin;
  int bluePin;
  int max;

  if (light == "little") {
    redPin   = _littleRedPin;
    greenPin = _littleGreenPin;
    bluePin  = _littleBluePin;
    max      = _littleMax;
  }
  else {
    redPin   = _largeRedPin;
    greenPin = _largeGreenPin;
    bluePin  = _largeBluePin;
    max      = _largeMax;
  }

  if (command == "r") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  min);
  }
  else if (command == "g") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  min);
  }
  else if (command == "b") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  max);
  }
  else if (command == "rg") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  min);
  }
  else if (command == "rb") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  max);
  }
  else if (command == "bg") {
    analogWrite(redPin,   min);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  max);
  }
  else if (command == "rgb") {
    analogWrite(redPin,   max);
    analogWrite(greenPin, max);
    analogWrite(bluePin,  max);
  }
  else {
    analogWrite(redPin,   min);
    analogWrite(greenPin, min);
    analogWrite(bluePin,  min);
  }
}

void LightControl::party() {
  int i;

  // start with just red
  analogWrite(_littleRedPin, _littleMax);
  analogWrite(_littleGreenPin, _min);
  analogWrite(_littleBluePin, _min);

  analogWrite(_largeRedPin, _largeMax);
  analogWrite(_largeGreenPin, _min);
  analogWrite(_largeBluePin, _min);

  // red to red/blue
  for (i = 0; i < 100; i++) {
    analogWrite(_littleBluePin, i * _littleMax / 100);
    analogWrite(_largeBluePin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // red/blue to blue
  for (i = 100; i > 0; i--) {
    analogWrite(_littleRedPin, i * _littleMax / 100);
    analogWrite(_largeRedPin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // blue to blue/green
  for (i = 0; i < 100; i++) {
    analogWrite(_littleGreenPin, i * _littleMax / 100);
    analogWrite(_largeGreenPin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // blue/green to green
  for (i = 100; i > 0; i--) {
    analogWrite(_littleBluePin, i * _littleMax / 100);
    analogWrite(_largeBluePin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // green to green/red
  for (i = 0; i < 100; i++) {
    analogWrite(_littleRedPin, i * _littleMax / 100);
    analogWrite(_largeRedPin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
  // green/red to red
  for (i = 100; i > 0; i--) {
    analogWrite(_littleGreenPin, i * _littleMax / 100);
    analogWrite(_largeGreenPin, i * _largeMax / 100);
    delay(_fadeSpeed);
  }
}
