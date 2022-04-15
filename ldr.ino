#define BLYNK_PRINT Serial
#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>

char auth[] = "j8us3HaIlu9oOEkx3CvJ9-gRH6W_VFB";
char ssid[] = "trf-id";                       // Your WiFi credentials.
char pass[] = "passworde123sampe8";

#define ldrPin A0
#define ledPin D2 
BlynkTimer timer;

WidgetLED led1(V6);
// This function sends Arduino's up time every second to Virtual Pin (5).
// In the app, Widget's reading frequency should be set to PUSH. This means
// that you define how often to send data to Blynk App.
void sendSensor()
{
  int sensorValue = analogRead(ldrPin);
  Blynk.virtualWrite(V5, sensorValue);
  Serial.println(sensorValue);
  if(sensorValue > 500){
    digitalWrite(ledPin, HIGH);
  }else{
    digitalWrite(ledPin, LOW);
  }
}


void blinkLedWidget()
{
  if (led1.getValue()) {
    led1.off();
    Serial.println("LED on V1: off");
  } else {
    led1.on();
    Serial.println("LED on V1: on");
  }
}


void setup()
{
  // Debug console
  Serial.begin(9600);

  Blynk.begin(auth, ssid, pass);
  // You can also specify server:
  //Blynk.begin(auth, ssid, pass, "blynk-cloud.com", 80);
  //Blynk.begin(auth, ssid, pass, IPAddress(192,168,1,100), 8080);

  pinMode(ledPin, OUTPUT);
  timer.setInterval(1000L, sendSensor);
  timer.setInterval(1000L, blinkLedWidget);
}

void loop()
{
  Blynk.run();
  timer.run();
}
