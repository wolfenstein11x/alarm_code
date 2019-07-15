#include <IRremote.h>

//Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;

//Variables for the ultrasonic sensor
long duration;
int cm;

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
  //Set trig to output and echo to input
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  //Enable the IR receiver
  irrecv.enableIRIn();
  //Set LED pins as outputs
  pinMode(bluePin, OUTPUT);
}

void loop() {
  if (togglestate == 1){
    get_distance();
   }
  
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

long ms_to_cm(long ms){
  return ms*0.034/2;
}

void get_distance(){
   //clear the trig pin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  //set the trigPin on HIGH for 10 microseconds
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  //read the echoPin, return the sound wave travel time in ms
  duration = pulseIn(echoPin, HIGH);

  //calculate the distance
  cm = ms_to_cm(duration);

  Serial.print("Distance: ");
  Serial.println(cm);
}
