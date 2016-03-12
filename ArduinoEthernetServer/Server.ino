/**
  @author Wesley Egberto
  Test the ethernet module ECNC28J60
*/

#include <SPI.h>
#include <Ethernet.h>

// define MAC and IP
byte MAC[] = { 0x78, 0x69, 0xEF, 0x4E, 0x93, 0x48 };
//static const byte IP[] = { 192, 168, 0, 115 };
IPAddress IP(192, 168, 0, 115);

EthernetServer server(80);
EthernetClient client;

void setup() {
  // start serial and wait for serial port to connect 
  Serial.begin(9600);
  while(!Serial);
  // start the connection and the server
  Ethernet.begin(MAC);
  server.begin();
  Serial.print("Server is at ");
  Serial.println(Ethernet.localIP());
}


void loop() {
  client = server.available();
  if(client) {
    Serial.println("new client");
    boolean currentLineIsBlank = true; // an http request ends with a blank line
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        if (c == '\n' && currentLineIsBlank) { // when receive a newline and the line is blanck means the http request has ended and we can replay
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println("Refresh: 5");
          client.println();
          client.println("<!DOCTYPE HTML><html><body><h1>You've connected on Arduino!</h1></body></html>");
          break;
        }
        if(c == '\n') {
          currentLineIsBlank = true; // you're starting a new line
        } else if(c != '\r') {
          currentLineIsBlank = false; // you've gotten a character on the current line
        }
      }
    }
    delay(1); // give the web browser time to receive the data
    client.stop();
    Serial.println("client disconnected");
  }
}
