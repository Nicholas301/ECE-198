#include <Stepper.h>
#define STEPS_PER_REV 200

const int motorPins[] = {A0, A1, A2, A3}; 
const int motionSensorPin = A5; 

Stepper myMotor(STEPS_PER_REV, motorPins[0], motorPins[1], motorPins[2], motorPins[3]);

bool motionDetected = false; // Flag to indicate motion detection

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(motorPins[i], OUTPUT);
  }
  pinMode(motionSensorPin, INPUT);
  Serial.begin(9600);
}

void loop() {
  // Check the motion sensor
  if (analogRead(motionSensorPin) > 300) {
    motionDetected = true; // Set the flag if motion is detected (adjust threshold as needed)
  }

  if (motionDetected) {
    // Rotate the motor 180 degrees in one direction (clockwise for example)
    for(int i = 0; i < 11; i++){
      myMotor.setSpeed(120); // Set the speed (steps per second)
      int stepsToMove = STEPS_PER_REV / 2; // 180 degrees is half a revolution
      myMotor.step(stepsToMove); // Rotate 180 degrees

      delay(50);

      // Stop the motor
      myMotor.setSpeed(0);
    }
    
    motionDetected = false; // Reset the motion detection flag
  }
}