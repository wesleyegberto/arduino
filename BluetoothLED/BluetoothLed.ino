#include <SoftwareSerial.h>

#define PIN_LED 10
#define PIN_LED_EMPTY 11

SoftwareSerial bt(5, 6);

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
  
  if(bt.available()) {
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
  } else {
    Serial.println("None");
    bt.print(24);
    digitalWrite(PIN_LED_EMPTY, HIGH);
    delay(500);
    digitalWrite(PIN_LED_EMPTY, LOW);
    delay(500); 
  }
}
