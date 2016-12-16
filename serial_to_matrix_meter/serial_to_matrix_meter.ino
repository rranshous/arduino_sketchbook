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
float lastPercent = 0;
int matrixHeight = 0;

void setup() {
  // initialize serial:
  Serial.begin(9600);
  // reserve 200 bytes for the inputString:
  inputString.reserve(200);
  matrix.begin(ADA_HT1632_COMMON_16NMOS);
  matrix.clearScreen(); 
  matrixHeight = matrix.height();
  delay(500);
  Serial.println("starting");
}

void loop() {
  
  
  // print the string when a newline arrives:
  if (stringComplete) {
    Serial.println(inputString);
    
    // we will get a number which is fill %
    // we want to fill the matrix to that %
    float percent = inputString.toInt();
    drawFill(percent);
    
    clearInput();
  }
  
}

void clearInput() {
  // clear the string:
  inputString = "";
  stringComplete = false;
}

void drawFill(float percent) {
  matrix.clearScreen();
  float top = (percent / 100) * matrix.width();
  matrix.fillRect(0, 0, top, matrix.height(), 1);
  matrix.writeScreen();
  lastPercent = percent;
}

//  matrix.drawLine(9, 12, 13, 12, 0);

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
    
    // if the incoming character is a newline, set a flag
    // so the main loop can do something about it:
    if (inChar == '\n') {
      stringComplete = true;
    } else {
      // add it to the inputString:
      inputString += inChar;
    }
  }
}
