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
