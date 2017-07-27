# Smart-Lights  

###### Or also something _else_ smart?  

 Allows you to control your lights at home from your coach.

---

## The Goals
- We would like to made a board with ESP32
    - connectivity:
        - 4 conectors for a 230V light, including switchers
        - 1 or 2 I2C ports for something special
        - at least 3 pins for something like NeoPixels, photorezistor, DHT sensor, PIR sensor,  etc.
        - 5V, 3V3 and GND pins
    - funcionality:
        - on setup, you simply edit one file, there will be everything to you could want to change 
        1. Launches a server on your WiFi and says you an IP Address, where the server is.
        2. If you already have one, it will connect to the server and auto add more light(s) or what you have added.
    - size 
        - about 5 dm square  

## What have we done
- Software  
    1.model  
        - ESP32 server, where you can turn two leds on and of  
        - good-looking, easy add more code and easy to modify code  
    2.model  
        - ESP32 server, where you can change mods of NeoPixels  