#include "ThingSpeak.h"
#include <ESP8266WiFi.h>
  
//----------- Enter you Wi-Fi Details---------//
char ssid[] = "IOT"; //SSID
char pass[] = "c0v3ntry"; // Password
//-------------------------------------------//
WiFiClient  client;

unsigned long myChannelField = 2209876; // Channel ID
const int ChannelField = 2; // Which channel to write data
const char * myWriteAPIKey = "134K27BTNG6IKVDW"; // Your write API Key

void setup() {
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  ThingSpeak.begin(client);
  Serial.println("pH meter experiment!");    //Test the serial monitor
 
}
void loop() {
   if (WiFi.status() != WL_CONNECTED)
  {
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(ssid);
    while (WiFi.status() != WL_CONNECTED)
    {
      WiFi.begin(ssid, pass);
      Serial.print(".");
      delay(5000);
    }
    Serial.println("\nConnected.");
  }
  
 static unsigned long samplingTime = millis();
  static unsigned long printTime = millis();
  int sensorValue = analogRead(A0);
  float voltage = sensorValue * (5.0 / 1024.0);
 
  Serial.println ("Sensor Output (V):");
  Serial.println (voltage);
  Serial.println();
  ThingSpeak.writeField(myChannelField, ChannelField, voltage, myWriteAPIKey);
  delay(1000);
}