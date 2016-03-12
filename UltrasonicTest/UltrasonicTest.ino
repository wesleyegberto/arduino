/*
  @author Wesley Egberto de Brito
  Projeto para testar o sensor ultrasonico
*/
#include <Ultrasonic.h>

#define REDLED 10

Ultrasonic ultrasonic(8, 9); // Trigger 8 and Echo 9

float dist, time;

void setup() {
  pinMode(REDLED, OUTPUT);
  
  Serial.begin(9600);
  
  while(!Serial);
}

void loop() {
  time = ultrasonic.timing();
  dist = ultrasonic.convert(time, Ultrasonic::CM);
  
  if(dist < 10) {
    digitalWrite(REDLED, HIGH);
  } else {
    digitalWrite(REDLED, LOW);
  }
  
  delay(100);
}
