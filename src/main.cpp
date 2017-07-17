/*
 * RGB Leds Controler
 *
 * Created: 17.7.2017
 * Author: BajaCali
 *
 */ 
 
#define SERIAL_BAUDRATE 115200

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


void WiFi_setup();

void setup() {
    Serial.begin(SERIAL_BAUDRATE);

    WiFi_setup();

}

void loop(){
    
}

void WiFi_setup(){
	WiFi.begin(ssid, password);	
    oldhandler = esp_event_loop_set_cb( hndl, nullptr );
    // delay(1000);
    Serial.print("Connecting");
    int stat = WiFi.status();
    printf("\nStatus pred whilem: %d",stat);
	while (stat != WL_CONNECTED){
        printf("\nStatus: %d",stat);
		if (stat != WL_DISCONNECTED && stat != WL_CONNECTED){
			WiFi.begin(ssid, password);
			Serial.println("Reconnecting");
		}
		//Serial.print(".");
		delay(500);
        stat = WiFi.status();
    }
    printf("\nStatus po whilu: %d",stat);
	Serial.print("\nConnected!\nIP address: ");
	Serial.print(WiFi.localIP());
}