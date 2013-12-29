/**
  @author Wesley Egberto
  @data 28/12/2013
  Interagir com o Arduino atraves da linguagem C
*/

#include <LiquidCrystal.h>

#define RED_PIN 8
#define YELLOW_PIN 9
#define GREEN_PIN 10
#define LIGHT_PIN 0

LiquidCrystal lcd(2, 3, 4, 5, 6, 7);

float sensor;
char buffer[16];
int i;
int row;

void showMessageLcd(String message, int col, int row, boolean clearLcd);

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2);
  
  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  
  // to Serial delay fix
  while(!Serial) ;
  lcd.setCursor(0, 0);
  lcd.print("Welcome");
  delay(100);
}

void loop() {
  showMessageLcd("Waiting command", 0, 0, true);
  if(Serial.available()) {
    char command = Serial.read();
    
    switch(command) {
      case 'R':
        Serial.println("Red LED on");
        digitalWrite(RED_PIN, HIGH);
        showMessageLcd("Red LED is on", 0, 1, true);
        delay(2000);
        digitalWrite(RED_PIN, LOW);
        break;
      case 'Y':
        Serial.println("Yellow LED on");
        digitalWrite(YELLOW_PIN, HIGH);
        showMessageLcd("Yellow LED is on", 0, 1, true);
        delay(2000);
        digitalWrite(YELLOW_PIN, LOW);
        break;
      case 'G':
        Serial.println("Green LED on");
        digitalWrite(GREEN_PIN, HIGH);
        showMessageLcd("Green LED is on", 0, 1, true);
        delay(2000);
        digitalWrite(GREEN_PIN, LOW);
        break;
      case 'L':
        sensor = analogRead(LIGHT_PIN);
        showMessageLcd("Luminosity", 0, 0, true);
        dtostrf(sensor, 2, 2, buffer);
        showMessageLcd(buffer, 0, 1, false);
        Serial.println(sensor);
        break;
      case 'S':
        showMessageLcd("Show message", 0, 0, true);
        i = row = 0;
        while(Serial.available()) {
          Serial.readBytesUntil('\n', buffer, 16);
          lcd.clear();
          showMessageLcd(buffer, 0, row++, false);
          delay(1000);
          if(row == 1) row = 0;
        }
        Serial.println("Showed");
        break;
      default:
        Serial.println("command not found");
        break;      
    }
  }
  delay(1000);
}

void showMessageLcd(String message, int col, int row, boolean clearLcd) {
  if(clearLcd) {
    lcd.clear();
  }
  lcd.setCursor(col, row);
  lcd.print(message);
}
