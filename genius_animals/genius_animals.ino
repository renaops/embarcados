#include <Adafruit_GFX.h>
#include <Adafruit_NeoMatrix.h>
#include <Adafruit_NeoPixel.h>
#ifndef PSTR
 #define PSTR
#endif

#define PIN 6

Adafruit_NeoMatrix matrix = Adafruit_NeoMatrix(8, 8, PIN,
  NEO_MATRIX_TOP     + NEO_MATRIX_RIGHT +
  NEO_MATRIX_COLUMNS + NEO_MATRIX_PROGRESSIVE,
  NEO_GRB            + NEO_KHZ800);

const uint16_t colors[] = {
  matrix.Color(255, 0, 0), matrix.Color(0, 255, 0), matrix.Color(0, 0, 255) };

void setup() {
  Serial.begin(9600);

  matrix.begin();
  matrix.setTextWrap(false);
  matrix.setBrightness(40);
  matrix.setTextColor(colors[0]);
}

void blinkRGB() {
  matrix.fillScreen(matrix.Color(29, 255, 108));
  matrix.show();
  delay(100);
}
void yellowLed() {
  matrix.fillScreen(matrix.Color(255, 255, 0)); // Yellow
  matrix.show();
  delay(100);
}

void redLed() {
  matrix.fillScreen(matrix.Color(255, 0, 0)); // Red
  matrix.show();
  delay(100);
}

void blueLed() {
  matrix.fillScreen(matrix.Color(0, 0, 255)); // Blue
  matrix.show();
  delay(100);
}

void greenLed() {
  matrix.fillScreen(matrix.Color(0, 255, 0)); // Green
  matrix.show();
  delay(100);
}

int input;

void loop() {
  while (!Serial.available()) {};

  input = Serial.readString().toInt();

  if (input == 0) {
    blueLed();
  } else if (input == 1) {
    yellowLed();
  } else if (input == 2) {
    redLed();
  } else if (input == 3) {
    greenLed();
  } else {
    blinkRGB();
  }

  Serial.print(input);
}
