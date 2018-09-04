/**************************************************************
 * IoT Motion Detector with Blynk
 * Blynk library is licensed under MIT license
 * This example code is in public domain.
 * 
 * Developed by Marcelo Rovai - 30 November 2016
 **************************************************************/
#include <ESP8266WiFi.h>
#include <WiFiManager.h> 

/* WiFi credentials */
const char* ssid = "Pixel2";
const char* password = "";

WiFiClientSecure client;
const char* server = "carpet.plumblem.com";
const char* fingerprint = "2B FB 80 0A E2 C0 42 9D BE BE 48 FA BD 9A 89 9D 30 89 88 FA";
const String serverString = server; 
const int httpPort = 443;
const String url = "/motion_sensor?detect=";

/* HC-SR501 Motion Detector */
int pirPin = 5; // GPIO 5, Input for HC-S501
int pirValue = false; // Place to store read PIR Value
int pirState = LOW; 

void setup()
{
  Serial.begin(115200);
  delay(100);
  pinMode(pirPin, INPUT);
  delay(100);

  connectWiFi();
  //configureInterrupts();
}

void configureInterrupts() {
  attachInterrupt(pirPin, pinRisingInterrupt, RISING);
  attachInterrupt(pirPin, pinFallingInterrupt, FALLING);
}

int count = 0;
void pinRisingInterrupt() {
  Serial.println("Pin Rising Interrupt");
  //connectToServer();
  //sendResult("yes");
}

void pinFallingInterrupt() {
  Serial.println("Pin Falling Interrupt");
  //connectToServer();
  //sendResult("no");
}

void connectWiFi(){
   Serial.println("Connecting to WIFI");
   WiFi.begin(ssid, password);
   while ((!(WiFi.status() == WL_CONNECTED)))
   {
     delay(300);
     Serial.print("..");
   }

  Serial.println("WiFi connected");
  Serial.print("NodeMCU Local IP is : ");
  Serial.println((WiFi.localIP()));
}

void connectToServer () {
  Serial.println("connecting to Server");
  // Use WiFiClient class to create TCP connections
  if (!client.connect(server, httpPort)) {
    Serial.println("connection failed");
  }
  else {
    if (client.verify(fingerprint, server)) {
      Serial.println("certificate matches");
      Serial.println("connect to server success!");
    } else {
      Serial.println("certificate doesn't match");
    }
  }
}

void sendResult(String detect) {
  // This will send the request to the server
  client.print(String("GET ") + url + detect + " HTTP/1.1\r\n" +
               "Host: " + serverString + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
}

void loop()
{
  getPirValue();
  delay(500); 
}

/***************************************************
 * Get PIR data
 **************************************************/
void getPirValue(void)
{
  pirValue = digitalRead(pirPin);
  if (pirValue == HIGH) { 
    Serial.println("***** Motion detected *****");
    if (pirState == LOW) {
      connectToServer();
      sendResult("yes");
      pirState = HIGH;
    }
  }
  else {
    Serial.println("Nothing detected");
    if (pirState == HIGH){
      connectToServer();
      sendResult("no");
      pirState = LOW;
    }
  }
  Serial.flush();
}
