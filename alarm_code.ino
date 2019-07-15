#include <IRremote.h>
#include <math.h>

//Ultrasonic sensor pins
const int trigPin = 9;
const int echoPin = 10;
//Distance Ultrasonic sensor is looking for (in cm)
const int target_d = 5;

//Variables for the ultrasonic sensor
long duration;
int cm;

//Variables and constants for the buzzer
int alarm_toggle = 0;

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
    if (irrecv.decode(&results)){
      if (results.value == 0xFF6897){
        alarm_toggle = 1;
        Serial.println("Alarm ready");
      }
    }
    if (alarm_toggle == 1){
      if (abs(get_distance() - target_d) > 1){
        Serial.println("BEEP BEEP!");
      }
    }
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
  delay(500);  
}

long ms_to_cm(long ms){
  return ms*0.034/2;
}

int get_distance(){
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

  return cm;
}
