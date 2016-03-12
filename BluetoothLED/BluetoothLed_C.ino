#include <SoftwareSerial.h>

#define PIN_LED 6
#define PIN_LED_EMPTY 7

SoftwareSerial bt(10, 11);

void setup() {
  Serial.begin(9600);
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }
  Serial.println("Configurando");
  
  bt.begin(38400);
  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_LED_EMPTY, OUTPUT);
  
  digitalWrite(PIN_LED, LOW);
  digitalWrite(PIN_LED_EMPTY, LOW);
    
  Serial.println("Ready");
}

void loop() {
  
  if(bt.available() >= 2) {
    Serial.println("Got");
    digitalWrite(PIN_LED_EMPTY, LOW);
    int key = bt.read();
    int value = bt.read();
    
    Serial.print("k:");
    Serial.print(key);
    Serial.print(" v:");
    Serial.println(value);
    
    if(value == 1) {
      digitalWrite(PIN_LED, HIGH);
    } else {
      digitalWrite(PIN_LED, LOW);
    }
  }
  if(Serial.available()) {
    delay(10);
    bt.write(Serial.read()); 
  }
}
