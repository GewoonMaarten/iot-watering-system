#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>

#include <ArduinoOTA.h>

// All passwords and urls
#include "configuration.h"

int relayPin = 5;
int sensorVCCPin = 4;
int whatToFlash = 0;

void setup() {
  Serial.begin(115200);
  Serial.println();

  pinMode(relayPin, OUTPUT);
  pinMode(sensorVCCPin, OUTPUT);

  digitalWrite(relayPin, LOW);
  digitalWrite(sensorVCCPin, LOW);
  
  //Connect to wifi
  WiFi.begin(ssid, ssid_password);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED){
    Serial.print(".");
    delay(500);
  }
  Serial.println(WiFi.localIP());


  ArduinoOTA.begin();
  ArduinoOTA.setPort(3000);
  ArduinoOTA.setHostname((char*) "water-system-0");
  ArduinoOTA.setPassword((char*) ota_password);

  Firebase.begin(firebase_url, firebase_auth);

  ArduinoOTA.onStart([]() {
    Firebase.setInt("devices/1/watering-system-0/readyToFlash", 0);
  });

  whatToFlash = Firebase.getInt("devices/1/watering-system-0/whatToFlash");
}

void uploadValue(){
  float value = readSensor();
  boolean isWatering = powerPump(value);
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); 
  root["value"] = double_with_n_digits(value, 2);
  root["isWatering"] = isWatering;
  
  root.prettyPrintTo(Serial);
  Firebase.push("devices/1/watering-system-0/measurements", root);
  if(Firebase.failed()){
    Serial.print("setting /truth failed:");
    Serial.println(Firebase.error());
    return;
  }
  Serial.println("Going into deep sleep");
  
  // Sleep for an 1 hour
  ESP.deepSleep(3600000000, WAKE_RF_DEFAULT);
  delay(100);
}

float readSensor(){
  digitalWrite(sensorVCCPin, HIGH);
  delay(1000);
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (3.2 / 1023.0);
  digitalWrite(sensorVCCPin, LOW);
  return voltage;
}

boolean powerPump(float value){
  if(value > 2.90){
    digitalWrite(relayPin, HIGH);
    Serial.println("Relay high");
    delay(10000);
    return true;
  } else {
    digitalWrite(relayPin, LOW);
    Serial.println("Relay low");
    return false;
  }
}
void loop(){
  if(whatToFlash == 1){
    Firebase.setInt("devices/1/watering-system-0/readyToFlash", 1);
    ArduinoOTA.handle();
  } else {
    Firebase.setInt("devices/1/watering-system-0/readyToFlash", 0);
    uploadValue();
  }
}

