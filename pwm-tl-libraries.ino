#include "LightControl.h"

#include <string.h>
#define LIB_DOMAIN "traffic-room.herokuapp.com"

TCPClient client;
int switchPin = D6;
int led = D7;

String littleColor;
String largeColor;

// littleRedPin   : D0;
// littleGreenPin : D1;
// littleBluePin  : A0;

// largeRedPin    : A4;
// largeGreenPin  : A5;
// largeBluePin   : A6;

LightControl controller(D0, D1, A0, A4, A5, A6);
bool bePartying = false;

void setup() {
  pinMode(switchPin, INPUT);
  pinMode(led, OUTPUT);
  digitalWrite(led, LOW);

  Spark.function("little", little);
  Spark.function("large", large);
  Spark.function("party", party);
  Spark.function("off", off);

  controller.initialize();

  blinkLED(5, 100);

//   client.connect(LIB_DOMAIN, 80);
//   client.println("GET /softreset HTTP/1.0");
//   client.println("Host: " LIB_DOMAIN);
//   client.println("Content-Length: 0");
//   client.println();

  blinkLED(2, 1000);
}

void loop() {
  if (digitalRead(switchPin) == HIGH) {
    if (bePartying) {
      controller.party();
    }
    else {
      controller.display("little", littleColor);
      controller.display("large", largeColor);
    }
  }
  else {
    off("");
  }
}

int little(String newColor) {
  bePartying = false;
  littleColor = newColor;
  return 1;
}

int large(String newColor) {
  bePartying = false;
  largeColor = newColor;
  return 1;
}

int party(String _) {
  bePartying = true;
  return 1;
}

int off(String _) {
  bePartying = false;
  littleColor = "off";
  largeColor = "off";
  return 1;
}

void blinkLED(int count, int interval) {
  for(int i = 0; i < count; i++) {
    digitalWrite(led, HIGH);
    delay(interval);
    digitalWrite(led, LOW);
    delay(interval);
  }
}
