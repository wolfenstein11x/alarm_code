#include <IRremote.h>

//IR sensor pin
const int RECV_PIN = 4;

//Define IR receiver and Results objects
IRrecv irrecv(RECV_PIN);
decode_results results;

const int bluePin = 6;

int togglestate = 0;

void setup() {
  //Serial monitor at 9600 baud
  Serial.begin(9600);
  //Enable the IR receiver
  irrecv.enableIRIn();
  //Set LED pins as outputs
  pinMode(bluePin, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)){
    if (results.value == 0xFF38C7){
      if (togglestate == 0){
        digitalWrite(bluePin, HIGH);
        togglestate = 1;
      }
      else {
        digitalWrite(bluePin, LOW);
        togglestate = 0;
      }
    }
    irrecv.resume(); 
  }  
}
