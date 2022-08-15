#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <FirebaseArduino.h>

#define SSID "*****"
#define PASSWORD "*****"

#define FIREBASE_HOST "fire-detection-robot-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "eV6sxUs1lTPkcyQphKwf9z1u4rlOxb3nlEmMNDWS"

#define LED D3

#define LM1 4       // left motor D2
#define LM2 5       // left motor D1
#define RM1 12       // right motor D5
#define RM2 14       // right motor D6
#define pump 15     // D8


void connectToWiFi(char const *ssid, char const *password);
void put_off_fire();
void setup()
{
  Serial.begin(115200);
  connectToWiFi(SSID, PASSWORD);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);

  pinMode(LM1, OUTPUT);
  pinMode(LM2, OUTPUT);
  pinMode(RM1, OUTPUT);
  pinMode(RM2, OUTPUT);
  pinMode(pump, OUTPUT);
}

void loop()
{
   if (Firebase.getBool("FLAME STATE")) {
    Serial.println("PUMP On");
    Serial.println();

        //Move the robot forward
    digitalWrite(LM1, HIGH);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, HIGH);
    digitalWrite(RM2, LOW);

    put_off_fire();
  }
  else{
    Serial.println("PUMP Off");
    Serial.println();
        //Do not move the robot
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
   }
  delay(500);

  //handling error
  if (Firebase.failed())
  {
    Serial.print("setting /message failed:");
    Serial.println(Firebase.error());
    return;
  }
}

void put_off_fire()
{
    delay (1000);
    
    digitalWrite(LM1, LOW);
    digitalWrite(LM2, LOW);
    digitalWrite(RM1, LOW);
    digitalWrite(RM2, LOW);
    
   digitalWrite(pump, HIGH); 
   delay(1000);

  
  digitalWrite(pump,LOW);
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