#include <Wire.h>
#include <Adafruit_Protomatter.h>
#include "src/sprites.h"

#define HEIGHT 64
#define WIDTH 64
#define MAX_FPS 20
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

  pinMode(6, INPUT_PULLUP);
  pinMode(7, INPUT_PULLUP);
}

const uint16_t NUM_STATES = 3;
uint16_t state = 0;

const unsigned long COMBO_WINDOW_MS = 500;

bool lastUpReading = HIGH;
bool lastDownReading = HIGH;

bool pendingUp = false;
bool pendingDown = false;

unsigned long pendingUpTime = 0;
unsigned long pendingDownTime = 0;

void loop() {
  // Limit the animation frame rate to MAX_FPS.  Because the subsequent sand
  // calculations are non-deterministic (don't always take the same amount
  // of time, depending on their current states), this helps ensure that
  // things like gravity appear constant in the simulation.
  uint32_t t;
  while(((t = micros()) - prevTime) < (1000000L / MAX_FPS));
  prevTime = t;
  unsigned long now = millis();
 
  matrix.fillScreen(0x0); //clear previous data
  
  bool upReading = digitalRead(6);
  bool downReading = digitalRead(7);

  bool upPressed = lastUpReading == HIGH && upReading == LOW;
  bool downPressed = lastDownReading == HIGH && downReading == LOW;
  
  // New up press
  if (upPressed) {
    pendingUp = true;
    pendingUpTime = now;
  }
  
  // New down press
  if (downPressed) {
    pendingDown = true;
    pendingDownTime = now;
  }
  
  // Combo detected
  if (pendingUp && pendingDown &&
      abs((long)(pendingUpTime - pendingDownTime)) <= COMBO_WINDOW_MS) {
    Serial.println("SPECIAL MODE ACTIVATED");
    if(state == 10){
      state = 0;
    }else{
      state = 10;
    }
  
    pendingUp = false;
    pendingDown = false;
  }
  
  // Up press expired without combo
  if (pendingUp && now - pendingUpTime > COMBO_WINDOW_MS) {
    if(state != 10){
      state = (state + 1) % NUM_STATES;
    }
    pendingUp = false;
  }
  
  // Down press expired without combo
  if (pendingDown && now - pendingDownTime > COMBO_WINDOW_MS) {
    if(state != 10){
      state = (state + NUM_STATES - 1) % NUM_STATES;
    } 
    pendingDown = false;
  }
  
  lastUpReading = upReading;
  lastDownReading = downReading;
  
  Serial.print("Pin 6: ");
  Serial.print(digitalRead(6));
  Serial.print("  Pin 7: ");
  Serial.print(digitalRead(7));
  Serial.print("  State: ");
  Serial.println(state);
  
  switch (state) {
    case 0:
      drawSpriteFill(sdsu);
      break;
    case 1:
      drawSpriteFill(brown);
      break;
    case 2:
      drawSpriteFill(mrgiggles);
      break;
    case 10:
      drawSpriteFill(league);
      break;
  }

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

void drawSpriteFill(const std::vector<std::string> sprite) {
  int scaleY = HEIGHT/sprite.size();
  int scaleX = WIDTH/sprite[0].size();
  for (int y = 0; y < sprite.size(); y++) {
    for (int x = 0; x < sprite[y].size(); x++) {
      uint16_t c = colorFromChar(sprite[y][x]);
      if (c != 0) {
        for (int dy = 0; dy < scaleY; dy++) {
          for (int dx = 0; dx < scaleX; dx++){
            matrix.drawPixel(x * scaleX + dx, y * scaleY + dy, c);
          }
        }
      }
    }
  }
}
