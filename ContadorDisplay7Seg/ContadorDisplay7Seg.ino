// Control of Display7Seg
const byte LENGHT = 10;
const byte mapDisplay[] = { 2, 3, 4, 5, 6, 7, 8, 9 };
// Button to start counter

void showNumber(byte b);
void showDisplay(int ledsDisplay[]);

void setup() {  
  for(int i = 0; i < LENGHT; i++) {
    pinMode(mapDisplay[i], OUTPUT); 
  }
}

void loop() {
  for(byte time = 0; time < 10; time++) {
    showNumber(time);
    delay(1000);
  }
}

/**
  Show the given number, use a map to show on the display 7 segs
*/
void showNumber(byte b) {
  int ledsDisplay[] = { LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW, LOW };
  switch(b) {
    case 0:
      ledsDisplay[0] = HIGH;
      ledsDisplay[1] = HIGH;
      ledsDisplay[2] = HIGH;
      ledsDisplay[3] = HIGH;
      ledsDisplay[4] = HIGH;
      ledsDisplay[5] = HIGH;
      break;
    case 1:
      ledsDisplay[1] = HIGH;
      ledsDisplay[2] = HIGH;
      break;
    case 2:
      ledsDisplay[0] = HIGH;
      ledsDisplay[1] = HIGH;
      ledsDisplay[3] = HIGH;
      ledsDisplay[4] = HIGH;
      ledsDisplay[6] = HIGH;
      break;
    case 3:
      ledsDisplay[0] = HIGH;
      ledsDisplay[1] = HIGH;
      ledsDisplay[2] = HIGH;
      ledsDisplay[3] = HIGH;
      ledsDisplay[6] = HIGH;
      break;
    case 4:
      ledsDisplay[1] = HIGH;
      ledsDisplay[2] = HIGH;
      ledsDisplay[5] = HIGH;
      ledsDisplay[6] = HIGH;
      break;
    case 5:
      ledsDisplay[0] = HIGH;
      ledsDisplay[2] = HIGH;
      ledsDisplay[3] = HIGH;
      ledsDisplay[5] = HIGH;
      ledsDisplay[6] = HIGH;
      break;
    case 6:
      ledsDisplay[0] = HIGH;
      ledsDisplay[2] = HIGH;
      ledsDisplay[3] = HIGH;
      ledsDisplay[4] = HIGH;
      ledsDisplay[5] = HIGH;
      ledsDisplay[6] = HIGH;
      break;
    case 7:
      ledsDisplay[0] = HIGH;
      ledsDisplay[1] = HIGH;
      ledsDisplay[2] = HIGH;
      break;
    case 8:
      ledsDisplay[0] = HIGH;
      ledsDisplay[1] = HIGH;
      ledsDisplay[2] = HIGH;
      ledsDisplay[3] = HIGH;
      ledsDisplay[4] = HIGH;
      ledsDisplay[5] = HIGH;
      ledsDisplay[6] = HIGH;
      break;
    case 9:
      ledsDisplay[0] = HIGH;
      ledsDisplay[1] = HIGH;
      ledsDisplay[2] = HIGH;
      ledsDisplay[3] = HIGH;
      ledsDisplay[5] = HIGH;
      ledsDisplay[6] = HIGH;
      break;
  }
  showDisplay(ledsDisplay);
}

/**
  Show the given map on the display 7 segs
*/
void showDisplay(int ledsDisplay[]) {
  for(int i = 0; i < LENGHT; i++) {
    digitalWrite(mapDisplay[i], ledsDisplay[i]);
  }
}
