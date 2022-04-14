#include <Wire.h>
 #include <Adafruit_Sensor.h>
 #include <Adafruit_BME280.h>
 #include <Blynk.h>
 #include <ESP8266WiFi.h>
 #include <BlynkSimpleEsp8266.h>
 char auth[] = "xxxxxxxxxxxxxxxxxxxxxx";       // You should get Auth Token in the Blynk App.
 char ssid[] = "xxxxxxxxxxx";                       // Your WiFi credentials.
 char pass[] = "passwordxxxx";
 float temperature;
 float pressure;
 float humidity;
 float altitude;
 
int speakerPin = 14;
 
 
 #define SEALEVELPRESSURE_HPA (1013.25)
 Adafruit_BME280 bme; // For I2C interface
 void setup() {
   Serial.begin(9600);
   
   Blynk.begin(auth, ssid, pass);
   pinMode(speakerPin, OUTPUT);

   Serial.println(F("BME280 Sensor event test"));
   if (!bme.begin(0x76))
   {
     Serial.println("Could not find a valid BME280 sensor, check wiring!");
     while (1);
   }

 }
 void loop() {
   Blynk.run(); // Initiates Blynk

     temperature = bme.readTemperature();
     pressure = bme.readPressure() / 100.0F;
     humidity = bme.readHumidity();
     altitude = bme.readAltitude(SEALEVELPRESSURE_HPA);
     double dewPoint = dewPointFast(temperature, humidity);

 Serial.print("Temperature = ");
   Serial.print(temperature);
   Serial.println("*C");
 Serial.print("Pressure = ");
   Serial.print(pressure);
   Serial.println("hPa");
 Serial.print("Humidity = ");
   Serial.print(humidity);
   Serial.println("%");
 Serial.print("Approx. Altitude = ");
   Serial.print(altitude);
   Serial.println("m");
 Serial.print("Dew point = ");
   Serial.print(dewPoint);
   Serial.println(" *C");
 Serial.println();
     Blynk.virtualWrite(V1, temperature); // For Temperature
     Blynk.virtualWrite(V2, pressure); // For Pressure
     Blynk.virtualWrite(V3, humidity); // For Humidity
     Blynk.virtualWrite(V4, altitude); //For Approx. Altitude
     Blynk.virtualWrite(V5, dewPoint); // For DewPoint
   delay(1000);
 }
 double dewPointFast(double celsius, double humidity)
 {
   double a = 17.271;
   double b = 237.7;
   double temp = (a * celsius) / (b + celsius) + log(humidity * 0.01);
   double Td = (b * temp) / (a - temp);
   return Td;
 }
