
/* 
 * Mert Arduino and Tech - YouTube
 * WiFi Robot controlled by Phone (WiFibot/Android/IoT/ESP8266)
 * NodeMCU ESP8266 Tutorial 03
 * Please Subscribe for Support - https://goo.gl/RLT6DT
 */


/* include library */
#include <ESP8266WiFi.h>
//#include <WiFiClientSecure.h>
//#include <ESP8266WebServer.h>

/*
 * If you have no idea about this library, you can watch the tutorial below
 * NodeMCU ESP8266 Tutorial 01: Programming NodeMCU ESP-12E Using Arduino IDE
 * https://youtu.be/NtyFx1frYB0
 */

const char* ssid = "Pixel2";
const char* password = "";
WiFiClientSecure client;
const char* server = "carpet.plumblem.com";
const char* fingerprint = "2B FB 80 0A E2 C0 42 9D BE BE 48 FA BD 9A 89 9D 30 89 88 FA";
const String serverString = server; 
const int httpPort = 443;
const String url = "/get_car_direction";

/* data received from application */
String data = ""; 

/* define L298N or L293D motor control pins */
int leftMotorForward = 2;     /* GPIO2(D4) -> IN3   */
int leftMotorBackward = 0;    /* GPIO0(D3) -> IN4   */
int rightMotorForward = 15;   /* GPIO15(D8) -> IN1  */
int rightMotorBackward = 13;  /* GPIO13(D7) -> IN2  */

/* define L298N or L293D enable pins */
int rightMotorENB = 14; /* GPIO14(D5) -> Motor-A Enable */
int leftMotorENB = 12;  /* GPIO12(D6) -> Motor-B Enable */

const int rotationDelay = 150;

void setup()
{
  Serial.begin(115200);
  /* initialize motor control pins as output */
  pinMode(leftMotorForward, OUTPUT);
  pinMode(leftMotorBackward, OUTPUT);
  pinMode(rightMotorForward, OUTPUT); 
  pinMode(rightMotorBackward, OUTPUT);

  /* initialize motor enable pins as output */
  pinMode(leftMotorENB, OUTPUT); 
  pinMode(rightMotorENB, OUTPUT);

  /* start server communication */
  connectWiFi();
}

void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.print("NodeMCU Local IP is : ");
  Serial.println((WiFi.localIP()));
}

void loop()
{
  connectToServer();
  readCommand();
  //delay(50);
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

void readCommand() {
  // This will send the request to the server
  client.print(String("GET ") + url + " HTTP/1.1\r\n" +
               "Host: " + serverString + "\r\n" + 
               "Connection: keep-alive\r\n\r\n");
  data = checkClient();

  if (data == "forward") MotorForward();
  else if (data == "backward") MotorBackward();
  else if (data == "right") TurnRight();
  else if (data == "left") TurnLeft();
  else if (data == "stop") MotorStop();
}

String checkClient (void)
{
  while(!client.available()) delay(1); 
  String line;
  String command;
  while(client.available()){
    line = client.readStringUntil('\r');
    //Serial.println(line);
    if (line.startsWith("\nDirection")) {
      command = line.substring(12, line.length());
      break;
    }
  }
  //Serial.flush();
  
  return command;
}


/********************************************* FORWARD *****************************************************/
void MotorForward(void)   
{
  Serial.println("MotorForward");
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
    
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);
}

/********************************************* BACKWARD *****************************************************/
void MotorBackward(void)   
{
  Serial.println("MotorBackward");
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,HIGH);
  
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);
}

/********************************************* TURN LEFT *****************************************************/
void TurnLeft(void)   
{
  Serial.println("Turn left");
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH); 
  
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,HIGH);
  
  digitalWrite(rightMotorForward,HIGH);
  digitalWrite(rightMotorBackward,LOW);

  delay(rotationDelay);
  MotorStop();
}

/********************************************* TURN RIGHT *****************************************************/
void TurnRight(void)   
{
  Serial.println("Turn right");
  digitalWrite(leftMotorENB,HIGH);
  digitalWrite(rightMotorENB,HIGH);
  
  digitalWrite(leftMotorForward,HIGH);
  digitalWrite(leftMotorBackward,LOW);
  
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,HIGH);

  delay(rotationDelay);
  MotorStop();
}

/********************************************* STOP *****************************************************/
void MotorStop(void)   
{
  Serial.println("MotorStop");
  digitalWrite(leftMotorENB,LOW);
  digitalWrite(rightMotorENB,LOW);
  
  digitalWrite(leftMotorForward,LOW);
  digitalWrite(leftMotorBackward,LOW);
  
  digitalWrite(rightMotorForward,LOW);
  digitalWrite(rightMotorBackward,LOW);
}

