#include "Adafruit_GFX.h"
#include "Adafruit_HT1632.h"

#define HT_DATA 2
#define HT_WR   3
#define HT_CS   4
#define HT_CS2  5

// use this line for single matrix
Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS);
// use this line for two matrices!
//Adafruit_HT1632LEDMatrix matrix = Adafruit_HT1632LEDMatrix(HT_DATA, HT_WR, HT_CS, HT_CS2);

String inputString = "";         // a string to hold incoming data
boolean stringComplete = false;  // whether the string is complete

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix.clearScreen(); 
  delay(500);
  Serial.println("starting");
}

void loop() {
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    if (inputString == "smile\n") {
      drawSmiley();
    } else if (inputString == "frown\n") {
      drawFrowny();
    } else if (inputString == "heart\n") {
      drawHeart();
    } else {
      show(inputString);
    }
    
    // clear the string:
    inputString = "";
    stringComplete = false;
  }
}

void show(String text) {
  matrix.clearScreen(); 
  // draw some text!
  matrix.setTextSize(1);    // siwze 1 == 8 pixels high
  matrix.setTextColor(1);   // 'lit' LEDs
  matrix.setTextWrap(true);

  matrix.setCursor(0, 0);   // start at top left, with one pixel of spacing
  matrix.println(text);
  matrix.writeScreen();
}

void drawSmiley() {
  Serial.println("drawing smiley");
  matrix.clearScreen();
  drawSmileBase();
  drawSmile();
  matrix.writeScreen();
}

void drawFrowny() {
  Serial.println("drawing frowny");
  matrix.clearScreen();
  drawSmileBase();
  drawFrown();
  matrix.writeScreen();
}

void drawSmile() {
  matrix.drawLine(9, 12, 13, 12, 0);
  matrix.drawLine(9, 11, 13, 11, 0);
  matrix.drawPixel(7, 10, 0);
  matrix.drawPixel(8, 11, 0);
  matrix.drawPixel(14, 11, 0);
  matrix.drawPixel(15, 10, 0);  
}

void drawFrown() {
  matrix.drawLine(10, 9, 12, 9, 0);
  matrix.drawPixel(9, 10, 0);
  matrix.drawPixel(8, 11, 0);
  matrix.drawPixel(13, 10, 0);
  matrix.drawPixel(14, 11, 0);
}

void drawSmileBase() {
  matrix.fillCircle(11, 7, 7, 1);
  matrix.fillCircle(8, 5, 1, 0);
  matrix.fillCircle(14, 5, 1, 0);
  //matrix.drawPixel(12, 8, 0);
}

void drawHeart() {
  // wasteful, i know
  matrix.drawPixel(6, 0, 1); matrix.drawPixel(7, 0, 1); matrix.drawPixel(8, 0, 1); matrix.drawPixel(9, 0, 1); matrix.drawPixel(14, 0, 1); matrix.drawPixel(15, 0, 1); matrix.drawPixel(16, 0, 1); matrix.drawPixel(17, 0, 1); matrix.drawPixel(5, 1, 1); matrix.drawPixel(6, 1, 1); matrix.drawPixel(7, 1, 1); matrix.drawPixel(8, 1, 1); matrix.drawPixel(9, 1, 1); matrix.drawPixel(10, 1, 1); matrix.drawPixel(13, 1, 1); matrix.drawPixel(14, 1, 1); matrix.drawPixel(15, 1, 1); matrix.drawPixel(16, 1, 1); matrix.drawPixel(17, 1, 1); matrix.drawPixel(18, 1, 1); matrix.drawPixel(4, 2, 1); matrix.drawPixel(5, 2, 1); matrix.drawPixel(6, 2, 1); matrix.drawPixel(9, 2, 1); matrix.drawPixel(10, 2, 1); matrix.drawPixel(11, 2, 1); matrix.drawPixel(12, 2, 1); matrix.drawPixel(13, 2, 1); matrix.drawPixel(14, 2, 1); matrix.drawPixel(17, 2, 1); matrix.drawPixel(18, 2, 1); matrix.drawPixel(19, 2, 1); matrix.drawPixel(4, 3, 1); matrix.drawPixel(5, 3, 1); matrix.drawPixel(11, 3, 1); matrix.drawPixel(12, 3, 1); matrix.drawPixel(18, 3, 1); matrix.drawPixel(19, 3, 1); matrix.drawPixel(4, 4, 1); matrix.drawPixel(5, 4, 1); matrix.drawPixel(11, 4, 1); matrix.drawPixel(12, 4, 1); matrix.drawPixel(18, 4, 1); matrix.drawPixel(19, 4, 1); matrix.drawPixel(4, 5, 1); matrix.drawPixel(5, 5, 1); matrix.drawPixel(18, 5, 1); matrix.drawPixel(19, 5, 1); matrix.drawPixel(4, 6, 1); matrix.drawPixel(5, 6, 1); matrix.drawPixel(18, 6, 1); matrix.drawPixel(19, 6, 1); matrix.drawPixel(4, 7, 1); matrix.drawPixel(5, 7, 1); matrix.drawPixel(18, 7, 1); matrix.drawPixel(19, 7, 1); matrix.drawPixel(4, 8, 1); matrix.drawPixel(5, 8, 1); matrix.drawPixel(6, 8, 1); matrix.drawPixel(17, 8, 1); matrix.drawPixel(18, 8, 1); matrix.drawPixel(19, 8, 1); matrix.drawPixel(5, 9, 1); matrix.drawPixel(6, 9, 1); matrix.drawPixel(7, 9, 1); matrix.drawPixel(16, 9, 1); matrix.drawPixel(17, 9, 1); matrix.drawPixel(18, 9, 1); matrix.drawPixel(6, 10, 1); matrix.drawPixel(7, 10, 1); matrix.drawPixel(8, 10, 1); matrix.drawPixel(15, 10, 1); matrix.drawPixel(16, 10, 1); matrix.drawPixel(17, 10, 1); matrix.drawPixel(7, 11, 1); matrix.drawPixel(8, 11, 1); matrix.drawPixel(9, 11, 1); matrix.drawPixel(14, 11, 1); matrix.drawPixel(15, 11, 1); matrix.drawPixel(16, 11, 1); matrix.drawPixel(8, 12, 1); matrix.drawPixel(9, 12, 1); matrix.drawPixel(10, 12, 1); matrix.drawPixel(13, 12, 1); matrix.drawPixel(14, 12, 1); matrix.drawPixel(15, 12, 1); matrix.drawPixel(9, 13, 1); matrix.drawPixel(10, 13, 1); matrix.drawPixel(11, 13, 1); matrix.drawPixel(12, 13, 1); matrix.drawPixel(13, 13, 1); matrix.drawPixel(14, 13, 1); matrix.drawPixel(10, 14, 1); matrix.drawPixel(11, 14, 1); matrix.drawPixel(12, 14, 1); matrix.drawPixel(13, 14, 1); matrix.drawPixel(11, 15, 1); matrix.drawPixel(12, 15, 1);
}

/*
  SerialEvent occurs whenever a new data comes in the
 hardware serial RX.  This routine is run between each
 time loop() runs, so using delay inside loop can delay
 response.  Multiple bytes of data may be available.
 */
void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    }
  }
}
