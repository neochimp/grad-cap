#include <Wire.h>
#include <Adafruit_Protomatter.h>

#define HEIGHT 64
#define WIDTH 64
#define MAX_FPS 45
//MUST BE BETWEEN 0 AND 1
#define BRIGHTNESS 0.3

#if defined(_VARIANT_MATRIXPORTAL_M4_) // MatrixPortal M4
uint8_t rgbPins[]  = {7, 8, 9, 10, 11, 12};
uint8_t addrPins[] = {17, 18, 19, 20, 21};
uint8_t clockPin   = 14;
uint8_t latchPin   = 15;
uint8_t oePin      = 16;
#else // MatrixPortal ESP32-S3
uint8_t rgbPins[]  = {42, 41, 40, 38, 39, 37};
uint8_t addrPins[] = {45, 36, 48, 35, 21};
uint8_t clockPin   = 2;
uint8_t latchPin   = 47;
uint8_t oePin      = 14;
#endif

#if HEIGHT == 16
#define NUM_ADDR_PINS 3
#elif HEIGHT == 32
#define NUM_ADDR_PINS 4
#elif HEIGHT == 64
#define NUM_ADDR_PINS 5
#endif

uint32_t prevTime = 0; // Used for frames-per-second throttle

Adafruit_Protomatter matrix(
  WIDTH, 4, 1, rgbPins, NUM_ADDR_PINS, addrPins,
  clockPin, latchPin, oePin, true);


void setup() {
  Serial.begin(115200);
  ProtomatterStatus status = matrix.begin();
  Serial.printf("Protomatter begin() status: %d\n", status);
}

void loop() {
  matrix.fillScreen(0x0); //clear previous data

  matrix.show(); // Copy data to matrix buffers
}

#define COLOR_DIMMED(R, G, B) matrix.color565(R*BRIGHTNESS, G*BRIGHTNESS, B*BRIGHTNESS)
uint16_t colorFromChar(char c) {
  switch (c) {
    case 'r': return COLOR_DIMMED(255, 0, 0);
    case 'w': return COLOR_DIMMED(255, 255, 255);
    case 'b': return COLOR_DIMMED(0, 0, 255);
    case 'y': return COLOR_DIMMED(245, 237, 0);
    default:  return 0;
  }
}
