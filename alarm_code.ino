#include <IRremote.h>

//IR sensor pin
const int RECV_PIN = 4;

//Define IR receiver and Results objects
IRrecv irrecv(RECV_PIN);
decode_results results;

//const int ledPin = 6;

void setup() {
  //Serial monitor at 9600 baud
  Serial.begin(9600);
  //Enable the IR receiver
  irrecv.enableIRIn();
  
  //pinMode(ledPin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)){
    // Print Code in HEX
    Serial.println(results.value, HEX);
    irrecv.resume();
  }
}
