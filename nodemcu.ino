#include <ArduinoJson.h>

#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);

#include <ESP8266WiFi.h>
#include <FirebaseArduino.h>

// Set these to run example.
#define FIREBASE_HOST "#FirebaseHost"
#define FIREBASE_AUTH "#Firebase Authentication Code"
#define WIFI_SSID "#UserSSID"
#define WIFI_PASSWORD "#UserPassword"

int n=0;

void setup() {
  
  Serial.begin(9600);
  s.begin(9600);
  

  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }
  Serial.println();
  Serial.print("connected: ");
  Serial.println(WiFi.localIP());
  
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);
  
}

// the loop function runs over and over again forever
void loop() {  
  
  DynamicJsonBuffer jBuffer;
  JsonObject& root = jBuffer.parseObject(s);
  if(root==JsonObject::invalid())
    return;

//  root.prettyPrintTo(Serial);
  Serial.print("Angle");
  int angle = root["Angle"];
  Serial.println(angle);

  Serial.print("Xaxis");
  int xaxis = root["Xaxis"];
  Serial.println(xaxis);

  Serial.print("Yaxis");
  int yaxis = root["Yaxis"];
  Serial.println(yaxis);

  Serial.print("Zaxis");
  int zaxis = root["Zaxis"];
  Serial.println(zaxis);
  
  Firebase.pushInt("Angle: ",angle);
  Firebase.pushInt("Xaxis: ",xaxis);
  Firebase.pushInt("Yaxis: ",yaxis);
  Firebase.pushInt("Zaxis: ",zaxis);
    
delay(2000);
}
