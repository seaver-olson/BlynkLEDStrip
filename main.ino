/*
 * Blynk Virtual Pinout
 * V1 - Brightness scroll
 * V2 - Green scroll
 * V3 - Red scroll
 * V4 - Blue scroll
 * V5 - IO button
 * 
 */


#include <FastLED.h>
#define BLYNK_PRINT Serial

#include <SPI.h>
#include <WiFiNINA.h>
#include <BlynkSimpleWiFiNINA.h>
#define LED_PIN     5
#define NUM_LEDS    300
#define LED_TYPE    WS2812
#define COLOR_ORDER GRB
CRGB leds[NUM_LEDS];

#define UPDATES_PER_SECOND 100


char auth[] = "wegr-qeQy99VzLUwYrb6FGiGr8qVhtba";


// Set password to "" for open networks.
char ssid[] = "Clarkson Air Central";
char pass[] = "ScottsdaleOlsons";
int Brightness = 0;
int IO = 0;
int Red = 0;
int Blue = 0;
int Green = 0;
void setup()
{
  // Debug console
  
  Serial.begin(9600);
  Serial.println("initializing");
  Blynk.begin(auth, ssid, pass);
  Serial.println(Brightness);
  delay( 3000 );//safety delay for LED powerup sequence
  FastLED.addLeds<LED_TYPE, LED_PIN, COLOR_ORDER>(leds, NUM_LEDS).setCorrection( TypicalLEDStrip );
  //starting brightness value, will change based on blynk value
  FastLED.setBrightness(  Brightness );
}
BLYNK_WRITE(V1){
   Brightness = param.asInt();
  }
BLYNK_WRITE(V2){
   Green = param.asInt();
  }
BLYNK_WRITE(V3){
   Red = param.asInt();
  }
BLYNK_WRITE(V4){
   Blue = param.asInt();
  }
BLYNK_WRITE(V5){
   IO = param.asInt();
  }
void loop()
{
  Blynk.run();
  Serial.println(IO);
  if (IO == 1){
    Serial.println("ON");
    FastLED.setBrightness( Brightness );
    fill_solid( leds, NUM_LEDS, CRGB(Red,Blue,Green));
    FastLED.show();
  }
   else{
    Serial.println("OFF");
    FastLED.clear();//clears data
    FastLED.show();
   } 
}
