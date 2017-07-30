/*
 * RGB Leds Controler
 *
 * Created: 17.7.2017
 * Author: BajaCali
 *
 */ 
 
#define SERIAL_BAUDRATE 115200

#define CONNECTED_LED  13
#define RESET_PIN 21

#define _GLIBCXX_USE_C99 1
#include <stdio.h>
#include <stdlib.h>
#include <Arduino.h>
#include <WiFi.h>
#include <string>
#include <iostream> 

#include "credentials.h"
#include "color_circle.h"
#include "pages.h"

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
int charcount = 0;

void reset();
void WiFi_setup();

void setup() {
    Serial.begin(SERIAL_BAUDRATE);
	pinMode(RESET_PIN, OUTPUT);
	digitalWrite(RESET_PIN, HIGH);
    // WiFi.begin(); 
    // delay(1000);
    // Serial.println("WiFi begined");
    Serial.println("Starting...");
    WiFi_setup();
    server.begin();

    color_circle_setup();
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
				if (c == '\n'){
					switcher(current_page, linebuf);
				}
				if (c == '\n' && currentLineIsBlank) {
					// send a standard http response header
					client.print(show_page(current_page));
					break;
				}
				if (c == '\n') {
					// you're starting a new 
					currentLineIsBlank = true;
					currentLineIsBlank = true;
					memset(linebuf,0,sizeof(linebuf));
					charcount=0;
				} 
				else if (c != '\r') {
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
	color_circle_loop();
}

void WiFi_setup(){
	pinMode(CONNECTED_LED, OUTPUT);
	digitalWrite(CONNECTED_LED, 0);
	WiFi.begin(ssid, password);
      oldhandler = esp_event_loop_set_cb(hndl, nullptr);
      Serial.print("Connecting");
      int stat = WiFi.status();
      printf("\nStatus pred whilem: %d",stat);
	  if(stat == 255){
		  Serial.println("Restarting!!!");
		  fflush(stdout);
		  reset();
	  }
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

void reset(){
	digitalWrite(RESET_PIN, LOW);
}