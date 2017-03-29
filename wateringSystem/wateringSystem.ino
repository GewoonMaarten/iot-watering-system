#include <Firebase.h>
#include <ESP8266WiFi.h>


// All passwords and urls
#include "configuration.h"


const int moisture_sensor_vcc_pin = 5;

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(moisture_sensor_vcc_pin, OUTPUT);  

  WiFi.begin(ssid, ssid_password);
  while (WiFi.status() != WL_CONNECTED){
    delay(500);
    Serial.print(".");
  }
  Serial.println(WiFi.localIP());

  // Sleep for an hour
  Serial.println("Going into deep sleep");
  ESP.deepSleep(3600000000);
}

void loop() {
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (3.2 / 1023.0);
  Serial.println(voltage);
  
  delay(5000);

}

