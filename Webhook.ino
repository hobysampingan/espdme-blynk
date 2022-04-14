ete.

2



Martin
Jun '19
Thank you so much for the help!!!

I guess it makes sense to read error messages >.>

If anyone else is looking to do something similar this is my final code, with a WebHook widget in the app attached to V8.

#include <ArduinoJson.h>
#define BLYNK_PRINT Serial
#define BLYNK_MAX_READBYTES 1024

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>



char auth[] = "___AUTH TOKEN___";

char ssid[] = "___SSID___";
char pass[] = "___PSWD___";


void setup() {
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);

  Blynk.virtualWrite(V8, "http://api.openweathermap.org/data/2.5/weather?id=7290688&APPID=1f7238a8c0f08b401922637efe12****");

}


void loop() {
  Blynk.run();
}

BLYNK_WRITE(V8)
{
  StaticJsonDocument<1024> doc;
  String json = param.asStr();
  Serial.println("WebHook data:");
  Serial.println(json);
  deserializeJson(doc, json);
  float windSpeed = doc["wind"]["speed"];
  Serial.println(windSpeed);
}
