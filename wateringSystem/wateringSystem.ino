
#include <Firebase.h>
#include <FirebaseArduino.h>
#include <FirebaseCloudMessaging.h>
#include <FirebaseError.h>
#include <FirebaseHttpClient.h>
#include <FirebaseObject.h>

#include <ESP8266WiFi.h>

// All passwords and urls
#include "configuration.h"

int relayPin = 5;
int sensorVCCPin = 4;

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

  Firebase.begin(firebase_url, firebase_auth);

  uploadValue();
}

void uploadValue(){
  float value = readSensor();
  boolean isWatering = powerPump(value);
  
  StaticJsonBuffer<200> jsonBuffer;
  JsonObject& root = jsonBuffer.createObject(); 
  root["value"] = double_with_n_digits(value, 2);
  root["isWatering"] = isWatering;
  
  root.prettyPrintTo(Serial);
  Firebase.push("measurement", root);
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
  if(value == 2.98){
    digitalWrite(relayPin, HIGH);
    Serial.println("Relay high");
    return true;
  } else {
    digitalWrite(relayPin, LOW);
    Serial.println("Relay low");
    return false;
  }
//  digitalWrite(relayPin, HIGH);
//  return true;
}

void loop(){
//  uploadValue();
//  delay(1000);
}

