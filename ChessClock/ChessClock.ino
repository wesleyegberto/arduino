/**
  Relogio de Xadrez
  @author: Renato Oliveira, Wesley Egberto
  @data 16/12/2013 a 25/12/2013
*/
#include <Keypad.h>
#include <LiquidCrystal.h>

LiquidCrystal lcd(8, 9, 10, 11, 12, 13);
char keys[4][3] = {
  {'1','2','3'},
  {'4','5','6'},
  {'7','8','9'},
  {'*','0','#'}
};
byte rowPins[4] = {3, 2, 1, 0};
byte colPins[3] = {6, 5, 4};

Keypad keypad = Keypad( makeKeymap(keys), rowPins, colPins, 4, 3 );
// Entrada do interruptor (chave)
byte BUTTON_PIN = 7;
int pos = 0;

bool isStarted = false;
bool isFinished = false;
bool player1Turn = true;

// Times
int minPlayer1 = 0;
int segPlayer1 = 0;
int minPlayer2;
int segPlayer2;
unsigned long time1 = 0;

void printInitial();
void printTime();
void configTime();

void setup(){
  lcd.begin(16, 2);
  
//MENU  
  lcd.setCursor(3, 1);
  lcd.print("Cronometro de Jogos");
  //Rolagem do texto
  for(pos=0; pos<22; pos++) {
    
    lcd.setCursor(pos, 0);
    lcd.print(" Projeto:");
    delay(300);
    lcd.scrollDisplayLeft();
    
  }
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Desenvolvedores:");
  lcd.setCursor(0,1);
  lcd.print("Renato e Wesley");
  delay(3000);
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Time: ");
  pos = 6;
  lcd.setCursor(pos,0);
  lcd.blink();

  pinMode(BUTTON_PIN, INPUT);
}

void loop(){
  if(isStarted) {
    // Leitura da chave
    player1Turn = digitalRead(BUTTON_PIN);
    // Leitura do push button
    
    
    if(player1Turn) {
      if(segPlayer1 == 0 && minPlayer1 == 0) {
        isFinished = true;
        isStarted = false;
      } else {
        if((millis() - time1) >= 1000) {
          if(segPlayer1 == 0) {
            minPlayer1--;
            segPlayer1 = 60;
          }
          segPlayer1--;
          printTime();
          time1 = millis();
        }
      }
    } else {
      if(segPlayer2 == 0 && minPlayer2 == 0) {
        isFinished = true;
        isStarted = false;
      } else {
        if((millis() - time1) >= 1000) {
          if(segPlayer2 == 0) {
            minPlayer2--;
            segPlayer2 = 60;
          }
          segPlayer2--;
          printTime();
          time1 = millis();
        }
      }
    }
  } if(isFinished) {
      lcd.noBlink();
      lcd.setCursor(0, 1);
      lcd.clear();
      delay(500);
      lcd.setCursor(0, 0);
      if(segPlayer1 == 0 && minPlayer1 == 0) {
        lcd.print("Jogador 1 perdeu");
        lcd.setCursor(0, 1);
        lcd.print("Tente novamente!");
        //Efeito de pisca no final
        for(int x = 0; x<10; x++) {
          
          lcd.noDisplay();
          delay(450);
          lcd.display();  
          delay(450);
          }
          
      } else if(segPlayer2 == 0 && minPlayer2 == 0) {
        lcd.print("Jogador 2 perdeu");
        lcd.setCursor(0, 1);
        lcd.print("Tente novamente!");
        //Efeito de pisca no final
          for(int x = 0; x<10; x++) {
                  
          lcd.noDisplay();
          delay(450);
          lcd.display();
          delay(450);  }
      } 
  } else {
    configTime(); 
  }
}

void printInitial() {
  lcd.clear(); 
  lcd.setCursor(0, 0);
  lcd.print("Jogador 1: ");
  if(minPlayer1 < 10) lcd.print("0");
  lcd.print(minPlayer1);
  lcd.print(":");
  if(segPlayer1 < 10) lcd.print("0");
  lcd.print(segPlayer1);
  
  lcd.setCursor(0, 1);
  lcd.print("Jogador 2: ");
  if(minPlayer2 < 10) lcd.print("0");
  lcd.print(minPlayer2);
  lcd.print(":");
  if(segPlayer2 < 10) lcd.print("0");
  lcd.print(segPlayer2);  
  
  time1 = millis();

}

void printTime() {
  if(player1Turn) {
    lcd.setCursor(11, 0);
    if(minPlayer1 < 10) lcd.print("0");
    lcd.print(minPlayer1);
    lcd.print(":");
    if(segPlayer1 < 10) lcd.print("0");
    lcd.print(segPlayer1);
  } else {
    lcd.setCursor(11, 1);
    if(minPlayer2 < 10) lcd.print("0");
    lcd.print(minPlayer2);
    lcd.print(":");
    if(segPlayer2 < 10) lcd.print("0");
    lcd.print(segPlayer2);
  }
}

void configTime() {
 char key = keypad.getKey();
  int n = 0;
  
  if(key != NO_KEY){
    switch(key) {
      case '1':
        n = 1; break;
      case '2':
        n = 2; break;
      case '3':
        n = 3; break;
      case '4':
        n = 4; break;
      case '5':
        n = 5; break;
      case '6':
        n = 6; break;       
      case '7':
        n = 7; break;
      case '8':
        n = 8; break;
      case '9':
        n = 9; break;
    }
    
    if(pos == 6) {
      minPlayer1 = n * 10; 
    } else if(pos == 7) {
      minPlayer1 += n;
    } else if(pos == 9) {
      if (n >= 6) {
        n -= 6;
        minPlayer1++;
      }     
      segPlayer1 = n * 10;
    } else if(pos == 10) {
      segPlayer1 += n;
    }
    
    lcd.setCursor(pos, 0);
    lcd.print(n);
    pos++;
    if(pos == 8) {
      lcd.print(":");
      pos++;
    }
    if(pos == 11) {
      minPlayer2 = minPlayer1;
      segPlayer2 = segPlayer1;
      
      // Aguarda pressionar uma tecla pra continuar
      lcd.clear();
      lcd.setCursor(0, 0);
      lcd.print("Pressione uma");
      lcd.setCursor(0, 1);
      lcd.print("tecla p/ iniciar");
      keypad.waitForKey();
      
      isStarted = true;
      printInitial();
    }
  
  } 
}

