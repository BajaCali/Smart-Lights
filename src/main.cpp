/*
 * RGB Leds Controler
 *
 * Created: 17.7.2017
 * Author: BajaCali
 *
 */ 
 
#define SERIAL_BAUDRATE 115200

#define CONNECTED_LED  13

#include <Arduino.h>
#include <WiFi.h>

#include "credentials.h"

#include <esp_wifi.h>

system_event_cb_t oldhandler;
esp_err_t hndl(void* x, system_event_t* e) 
{
    printf("Event: %d\n",e->event_id);
    fflush(stdout);
    (*oldhandler)(x, e);
}

WiFiServer server(80);

// Client variables 
char linebuf[80];
int charcount=0;

const int led1 =  26;      // the number of the LED pin
const int led2 =  27;      // the number of the LED pin

void WiFi_setup();

void setup() {
    Serial.begin(SERIAL_BAUDRATE);

    pinMode(led1, OUTPUT);
    pinMode(led2, OUTPUT);

    WiFi_setup();
    server.begin();
}

void loop(){
  // listen for incoming clients
  WiFiClient client = server.available();
  if (client) {
    Serial.println("New client");
    memset(linebuf,0,sizeof(linebuf));
    charcount=0;
    // an http request ends with a blank line
    boolean currentLineIsBlank = true;
    while (client.connected()) {
      if (client.available()) {
        char c = client.read();
        Serial.write(c);
        //read char by char HTTP request
        linebuf[charcount]=c;
        if (charcount<sizeof(linebuf)-1) charcount++;
        // if you've gotten to the end of the line (received a newline
        // character) and the line is blank, the http request has ended,
        // so you can send a reply
        if (c == '\n' && currentLineIsBlank) {
          // send a standard http response header
          client.println("HTTP/1.1 200 OK");
          client.println("Content-Type: text/html");
          client.println("Connection: close");  // the connection will be closed after completion of the response
          client.println();
          client.println("<!DOCTYPE HTML><html><head>");
          client.println("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"></head>");
          client.println("<h1>ESP32 - Web Server</h1>");
          client.println("<p>LED #1 <a href=\"on1\"><button>ON</button></a>&nbsp;<a href=\"off1\"><button>OFF</button></a></p>");
          client.println("<p>LED #2 <a href=\"on2\"><button>ON</button></a>&nbsp;<a href=\"off2\"><button>OFF</button></a></p>");
          client.println("</html>");
          break;
        }
        if (c == '\n') {
          // you're starting a new line
          currentLineIsBlank = true;
          if (strstr(linebuf,"GET /on1") > 0){
            Serial.println("LED 1 ON");
            digitalWrite(led1, HIGH);
          }
          else if (strstr(linebuf,"GET /off1") > 0){
            Serial.println("LED 1 OFF");
            digitalWrite(led1, LOW);
          }
          else if (strstr(linebuf,"GET /on2") > 0){
            Serial.println("LED 2 ON");
            digitalWrite(led2, HIGH);
          }
          else if (strstr(linebuf,"GET /off2") > 0){
            Serial.println("LED 2 OFF");
            digitalWrite(led2, LOW);
          }
          // you're starting a new line
          currentLineIsBlank = true;
          memset(linebuf,0,sizeof(linebuf));
          charcount=0;
        } else if (c != '\r') {
          // you've gotten a character on the current line
          currentLineIsBlank = false;
        }
      }
    }
    // give the web browser time to receive the data
    delay(1);

    // close the connection:
    client.stop();
    Serial.println("client disconnected");
  }
    
}

void WiFi_setup(){
    pinMode(CONNECTED_LED, OUTPUT);
    digitalWrite(CONNECTED_LED, 0);
    WiFi.begin(); 
    delay(1000);
	WiFi.begin(ssid, password);	
    oldhandler = esp_event_loop_set_cb( hndl, nullptr );
    Serial.print("Connecting");
    int stat = WiFi.status();
    printf("\nStatus pred whilem: %d",stat);
	while (stat != WL_CONNECTED){
        printf("\nStatus: %d",stat);
		if (stat != WL_DISCONNECTED && stat != WL_CONNECTED){
			WiFi.begin(ssid, password);
			Serial.println("Reconnecting");
		}
		Serial.print(".");
		delay(500);
        stat = WiFi.status();
    }
    digitalWrite(CONNECTED_LED, 1);
    printf("\nStatus po whilu: %d",stat);
	Serial.print("\nConnected!\nIP address: ");
	Serial.print(WiFi.localIP());
}