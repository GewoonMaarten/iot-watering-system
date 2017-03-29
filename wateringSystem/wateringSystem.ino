#include <Firebase.h>
#include <ESP8266WiFi.h>

// All passwords and urls
#include "configuration.h"

void setup() {
  Serial.begin(115200);
  Serial.println();
  //Connect to wifi
  WiFi.begin(ssid, ssid_password);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());

  Firebase.begin(firebase_url, firebase_auth);

  uploadValue();

  // Sleep for an hour
  Serial.println("Going into deep sleep");
  ESP.deepSleep(3600000000);
}

void loop() {

}

void uploadValue(){
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (3.2 / 1023.0);

  Firebase.setFloat("value", voltage);
  if(Firebase.failed()){
    Serial.print("setting /truth failed:");
    Serial.println(Firebase.error());
    return;
  }
}

