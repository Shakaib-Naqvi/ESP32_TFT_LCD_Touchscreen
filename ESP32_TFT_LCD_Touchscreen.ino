#include <SPI.h>
#include <Adafruit_GFX.h>
#include <Adafruit_ILI9341.h>  // or ST7735 depending on your display
#include <XPT2046_Touchscreen.h>

// TFT Pins
#define TFT_CS   15
#define TFT_DC   2
#define TFT_RST  4

// Touchscreen Pins
#define TOUCH_CS 21
#define TOUCH_IRQ 22  // optional

#define ILI9341_TFTWIDTH 240  ///< ILI9341 max TFT width
#define ILI9341_TFTHEIGHT 320 ///< ILI9341 max TFT height

// Create TFT and Touchscreen objects (using VSPI)
Adafruit_ILI9341 tft = Adafruit_ILI9341(TFT_CS, TFT_DC, TFT_RST);
XPT2046_Touchscreen ts(TOUCH_CS, TOUCH_IRQ);  // IRQ optional



// Button coordinates
#define BUTTON_WIDTH 100
#define BUTTON_HEIGHT 40
#define RED_BTN_X 30
#define GREEN_BTN_X 190
#define BTN_Y 180

void drawMainUI() {
  // tft.fillScreen(ILI9341_BLACK);
  
  tft.setCursor(30, 20);
  tft.setTextColor(ILI9341_BLACK);
  tft.setTextSize(2);
  tft.println("Design Made By Shakaib");

  tft.setTextSize(2);
  tft.setCursor(40, 60);
  tft.println("Touchscreen UI Demo");

  // Draw buttons
  tft.fillRect(RED_BTN_X, BTN_Y, BUTTON_WIDTH, BUTTON_HEIGHT, ILI9341_RED);
  tft.fillRect(GREEN_BTN_X, BTN_Y, BUTTON_WIDTH, BUTTON_HEIGHT, ILI9341_GREEN);

  tft.setTextColor(ILI9341_WHITE);
  tft.setCursor(RED_BTN_X + 20, BTN_Y + 10);
  tft.println("RED");

  tft.setCursor(GREEN_BTN_X + 10, BTN_Y + 10);
  tft.println("GREEN");
}


void setup() {
  Serial.begin(115200);
  delay(500);

  SPI.begin(18, 19, 23);  // SCK, MISO, MOSI — explicitly define for VSPI

  // Initialize Touchscreen
  ts.begin();
  ts.setRotation(3);  // adjust if needed based on your screen orientation

  // Initialize TFT
  tft.begin();
  tft.setRotation(1);  // adjust if needed based on your screen orientation
  tft.fillScreen(ILI9341_WHITE);
  drawMainUI();

  Serial.println("Touch test starting...");
}

void loop() {
  if (ts.touched()) {
    TS_Point p = ts.getPoint();

    int x = map(p.x, 140, 3710, 0, 320);
    int y = map(p.y, 220, 3770, 0, 240);

    if (y > BTN_Y && y < (BTN_Y + BUTTON_HEIGHT)) {
      if (x > RED_BTN_X && x < (RED_BTN_X + BUTTON_WIDTH)) {
        tft.fillScreen(ILI9341_RED);
        delay(300);
        drawMainUI();
      }
      if (x > GREEN_BTN_X && x < (GREEN_BTN_X + BUTTON_WIDTH)) {
        tft.fillScreen(ILI9341_GREEN);
        delay(300);
        drawMainUI();
      }
    }
  }
}
