#define RED_PIN 8
#define YELLOW_PIN 9
#define GREEN_PIN 10
#define LIGHT_PIN 0

float sensor;

void setup() {
  Serial.begin(9600);

  pinMode(RED_PIN, OUTPUT);
  pinMode(YELLOW_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  
  digitalWrite(RED_PIN, LOW);
  digitalWrite(YELLOW_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  
  // to Serial delay fix
  while(!Serial) ;
}

void loop() {
  //Serial.println("Iniciado");
  if(Serial.available()) {
    char command = Serial.read();
    
    switch(command) {
      case 'R':
        Serial.println("Red LED on");
        digitalWrite(RED_PIN, HIGH);
        delay(2000);
        digitalWrite(RED_PIN, LOW);
        break;
      case 'Y':
        Serial.println("Yellow LED on");
        digitalWrite(YELLOW_PIN, HIGH);
        delay(2000);
        digitalWrite(YELLOW_PIN, LOW);
        break;
      case 'G':
        Serial.println("Green LED on");
        digitalWrite(GREEN_PIN, HIGH);
        delay(2000);
        digitalWrite(GREEN_PIN, LOW);
        break;
      case 'L':
        sensor = analogRead(LIGHT_PIN);
        Serial.println(sensor);
        break;
      default:
        Serial.println("command not found");
        break;      
    }
  }
  delay(1000);
}
