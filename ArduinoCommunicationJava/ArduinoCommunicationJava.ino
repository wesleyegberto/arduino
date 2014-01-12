#define GREEN_PIN 8
#define YELLOW_PIN 9
#define RED_PIN 10
#define LIGHT_PIN 0

int greenValue = LOW;
int yellowValue = LOW;
int redValue = LOW;
float sensor;

void setup() {
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(RED_PIN, OUTPUT);
  
  Serial.begin(9600);
  
  // to Serial delay fix to Leonardo
  //while(!Serial) ;
}

void loop() {
  if(Serial.available()) {
    char command = Serial.read();
    
    switch(command) {
      case 'R':
        if(Serial.read() == 'H')
          redValue = HIGH;
        else
          redValue = LOW;
        break;
      case 'Y':
        if(Serial.read() == 'H')
          yellowValue = HIGH;
        else
          yellowValue = LOW;
        break;
      case 'G':
        if(Serial.read() == 'H')
          greenValue = HIGH;
        else
          greenValue = LOW;
        break;
      case 'L':
        sensor = analogRead(LIGHT_PIN);
        Serial.println(sensor);
        break;
      default:
        Serial.println("Invalid command");
        break;      
    }
  }
  digitalWrite(GREEN_PIN, greenValue);
  digitalWrite(YELLOW_PIN, yellowValue);
  digitalWrite(RED_PIN, redValue);
  delay(500);
}
