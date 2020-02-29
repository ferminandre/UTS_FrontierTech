#include <Arduino.h>

#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>
#include <Adafruit_NeoPixel.h>

// You should get Auth Token in the Blynk App.
// Go to the Project Settings (nut icon).
char auth[] = "ySqSi2noKBCKS93gBMVvD-Gb_ZxHXjM9";

// Your WiFi credentials.
// Set password to "" for open networks.
char ssid[] = "Rey-Wifi";
char pass[] = "reyreynaldo002";

#define NeoPixel 27
#define NumPixels 1
int r,g,b;
Adafruit_NeoPixel pixels(NumPixels, NeoPixel, NEO_GRB + NEO_KHZ800);

void setup() {
  Serial.begin(115200);
  Blynk.begin(auth, ssid, pass);
  pinMode(NeoPixel, OUTPUT);
  pixels.begin();
  pixels.clear();
}

BLYNK_READ(V0){
  int value = analogRead(36);
  Blynk.virtualWrite(V0, value);
}

BLYNK_WRITE(V1) // zeRGBa assigned to V1 
{
    // get a RED channel value
    r = param[0].asInt();
    // get a GREEN channel value
    g = param[1].asInt();
    // get a BLUE channel value
    b = param[2].asInt();
    pixels.setPixelColor(0, pixels.Color(r, g, b));
    pixels.show();
}

void loop() {
  Blynk.run();
  int value = analogRead(36);
  Serial.print("Analog Reading : ");
  Serial.println(value);
  if (value >= (0.8*4095)){
    Blynk.notify("Its over 80%");
  }
}
