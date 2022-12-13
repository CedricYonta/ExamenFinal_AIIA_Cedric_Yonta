#include <Arduino.h>
#include <Adafruit_NeoPixel.h>
#include "WIFIConnector_MKR1000.h"
#include "MQTTConnector.h"

#define PIN_LED 3     // Control signal, connect to DI of the LED
#define NUM_LED 1     // Number of LEDs in a strip

const int buttonPin1 = 2;
const int buttonPin2 = 4;
const int buttonPin3 = 5;
int buttonState1 = 0;  
int buttonState2 = 0;  
int buttonState3 = 0;  

Adafruit_NeoPixel RGB_Strip = Adafruit_NeoPixel(NUM_LED, PIN_LED, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(9600);
   wifiConnect(); // Branchement au réseau WIFI
    MQTTConnect(); // Branchement au broker MQTT à Thingsboard
     // pinMode(trigPin, OUTPUT); // Sets the trigPin as an OUTPUT
   pinMode(buttonPin1 , INPUT);
   pinMode(buttonPin2 , INPUT);
   pinMode(buttonPin3 , INPUT);
   RGB_Strip.begin();
  RGB_Strip.show();
  RGB_Strip.setBrightness(Intensite);    // Set brightness, 0-255 (darkest - brightest)
  
}

void colorWipe(uint32_t c, uint16_t wait);

void loop() {
   ClientMQTT.loop(); 
   
   buttonState1 = digitalRead(buttonPin1);
   buttonState2 = digitalRead(buttonPin2);
   buttonState3 = digitalRead(buttonPin3);

   Serial.println(code);

   if (code == 'r')
   {
      colorWipe(RGB_Strip.Color(255, 0, 0), 1000);  // Red
      colorWipe(RGB_Strip.Color(0, 0, 255), 1000);  // Blue
   }

   if (code == 'g')
   {
     colorWipe(RGB_Strip.Color(0, 255, 0), 1000);  // Green
   }


   if (code == 'b')
   {
       colorWipe(RGB_Strip.Color(255, 0, 0), 1000);  // Red
        colorWipe(RGB_Strip.Color(0, 255, 0), 1000);  // Green
   }

   

 appendPayload("bouton1" ,buttonState1);
 appendPayload("bouton2" ,buttonState2);
 appendPayload("bouton3" ,buttonState3);
 sendPayload();

  delay(1000);
}

// Fill the dots one after the other with a color
void colorWipe(uint32_t c, uint16_t wait) {
  for (uint16_t i = 0; i < RGB_Strip.numPixels(); i++) {
    RGB_Strip.setPixelColor(i, c);
    RGB_Strip.show();
    delay(wait);
  }
}