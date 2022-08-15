#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

#define SSID "space1"
#define PASSWORD "@lmor@ba3"

#define FIREBASE_HOST "fire-detection-robot-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "eV6sxUs1lTPkcyQphKwf9z1u4rlOxb3nlEmMNDWS"

#define LED D3

const int flame = 5; //--> The pin used for the FLAME sensor is Pin D1 = GPIO5
bool flame1 = 0; //state flame {False}
int isFlame = LOW; // HIGH when Flame Exposed

void connectToWiFi(char const *ssid, char const *password);

void setup()
{
  Serial.begin(115200);
  connectToWiFi(SSID, PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  pinMode(flame, INPUT); 
}

void loop()
{
  isFlame = digitalRead(flame);

  if (isFlame == HIGH) {
    flame1 = 1;
      
    Serial.println("FLAME, FLAME, FLAME");
      
    Firebase.setString("FLAME", "FLAME DETECTED");
    Firebase.set("FLAME STATE", flame1); //--> Command or code for sending data (int data type) to Firebase Realtime Database.
   
  } else {
    flame1 = 0;
    
    Serial.println("no flame");

    Firebase.setString("FLAME", "NOT DETECTED");

    Firebase.set("FLAME STATE", flame1);
  }
  Serial.println(flame1);
  

  //handling error
  if (Firebase.failed())
  {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());
    return;
  }
}

void connectToWiFi(char const *ssid, char const *password)
{
  delay(10);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.print(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("WiFi connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());
  Serial.println("");
}

  

