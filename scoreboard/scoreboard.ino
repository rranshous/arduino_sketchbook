// This #include statement was automatically added by the Particle IDE.
//#include "HttpClient/HttpClient.h"

int button_blue  = D6;
int button_red   = D1;
int button_reset = D2;

int led = D7;

// debounce variables
int inPin = 7;         // the number of the input pin

int counter = 0;       // how many times we have seen new value
int reading;           // the current value read from the input pin
int current_state = LOW;    // the debounced input value

// the following variable is a long because the time, measured in milliseconds,
// will quickly become a bigger number than can be stored in an int.
long now = 0;         // the last time the output pin was sampled

int debounce_count = 10; // number of millis/samples to consider before declaring a debounced input


HttpClient http;

// Headers currently need to be set at init, useful for API keys etc.
//http_header_t headers[] = {
  //  { "Content-Type", "application/json" },
  //  { "Accept" , "application/json" },
//  { "Accept" , "*/*"},
//  { NULL, NULL } // NOTE: Always terminate headers will NULL
//};


http_request_t request;
http_response_t response;

void setup() {
  //pinMode(button_red,   INPUT_PULLDOWN);
  pinMode(button_blue,  INPUT);
  //pinMode(button_reset, INPUT_PULLDOWN);

  pinMode(led, OUTPUT);
  delay(1000);
  debug("Setup complete");
  digitalWrite(led, HIGH);
  delay(1000);
  digitalWrite(led, LOW);
}

void loop() {
  
  
  //request.hostname = "http://10.103.69.181";
  //request.port = 5000;
  
  //Particle.publish("blue " + val_blue);
  
  // If we have gone on to the next millisecond
  if(millis() != now)
  {
    reading = digitalRead(button_blue);
    //debug("reading");

    if(reading == current_state && counter > 0)
    {
        debug("same reading, positive counter");
      counter--;
    }
    if(reading != current_state)
    {
       counter++; 
       debug("different reading");
    }
    // If the Input has shown the same value for long enough let's switch it
    if(counter >= debounce_count)
    {
        debug("counter >= debounce count");
      counter = 0;
      current_state = reading;
      digitalWrite(led, HIGH);
    }
    now = millis();
  }

}



void debug(String message) {
    Serial.write(message);
//    Spark.publish("DEBUG", message);

}
