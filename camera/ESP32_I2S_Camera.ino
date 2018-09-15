#include "OV7670.h"

#include <WiFi.h>
#include <WiFiMulti.h>
#include <WiFiClientSecure.h>
//#include <WiFiClient.h>
#include "BMP.h"
//#include <WiFiUdp.h>
#include <HTTPClient.h>

const int SIOD = 23; //SDA
const int SIOC = 22; //SCL

const int VSYNC = 21;
const int HREF = 19;

const int XCLK = 18;
const int PCLK = 5;

const int D0 = 13;
const int D1 = 12;
const int D2 = 14;
const int D3 = 27;
const int D4 = 26;
const int D5 = 25;
const int D6 = 33;
const int D7 = 32;

//DIN <- MOSI 23
//CLK <- SCK 18

// ap
const char * networkName = "Pixel2";
const char * networkPswd = "6692652138";

//ec2 address
const char * udpAddress = "34.211.88.132";
const int udpPort = 50766;

OV7670 *camera;

unsigned char bmpHeader[BMP::headerSize];
boolean connected = false;
//WiFiUDP udp;
HTTPClient http; 

uint8_t payload[BMP::headerSize + 9600];
//WiFiClient client;
void serve()
{
//    if(connected){
//        //Send a packet
//        udp.beginPacket(udpAddress,udpPort);
//        //udp.printf("Seconds since boot: %u", millis()/1000);
//        for(int i = 0; i < BMP::headerSize; i++)
//           udp.write(bmpHeader[i]);
//        for(int i = 0; i < camera->xres * camera->yres * 2; i++)
//           udp.write(camera->frame[i]);
//        udp.endPacket();
//        udp.beginPacket(udpAddress,udpPort);
//        udp.printf("done");
//       // udp.endPacket();
//       Serial.println(udp.endPacket());
//       int sizeSend = BMP::headerSize + (camera->xres * camera->yres * 2);
//       Serial.println(sizeSend);
//    }
//    Serial.println("no connection");


//    if (!client.connect("34.211.88.132", 80)) {
//        Serial.println("connection failed");
//    } else {
//      size_t len = BMP::headerSize + (camera->xres * camera->yres * 2);
//        String response = "POST /camera HTTP/1.1\r\n";
//        response += "Content-Type: image/bmp\r\n";
//        response += "Content-Length: " + String(len) + "\r\n";
//        Serial.println("conected to the server");
//        client.println(response);
////        for(int i = 0; i < BMP::headerSize; i++)
////           client.write(bmpHeader[i]);
////        for(int i = 0; i < camera->xres * camera->yres * 2; i++)
////           client.write(camera->frame[i]);
//        Serial.println("done");
//    }
      size_t len = BMP::headerSize + (camera->xres * camera->yres * 2);
      http.begin("http://carpet.plumblem.com/camera"); 
      http.addHeader("Content-Type", "text/plain");
      //payload[0] = '{'; payload[1] = '"'; payload[2] = 'i'; payload[3] = 'm' ; payload[4] = 'a'; payload[5] = 'g'; payload[6] = 'e'; payload[7] = '"'; payload[8] = ':'; payload[9] = '"';
      memcpy(payload, bmpHeader, BMP::headerSize);
      memcpy(payload + BMP::headerSize, camera->frame, (camera->xres * camera->yres * 2));
//      payload[BMP::headerSize + 9600 + 10] = '"';
//      payload[BMP::headerSize + 9600 + 11] = '}';
      int httpResponseCode = http.POST(payload, len);
      //int httpResponseCode = http.POST("test");
      
     if(httpResponseCode>0){
 
      String response = http.getString();                       //Get the response to the request
   
      Serial.println(httpResponseCode);   //Print return code
      Serial.println(response);           //Print request answer
   
     } else {
   
      Serial.print("Error on sending POST: ");
      Serial.println(httpResponseCode);
   
     }
   
     http.end();  //Free resources
}

void setup() 
{
  Serial.begin(115200);
  connectToWiFi(networkName, networkPswd);
  camera = new OV7670(OV7670::Mode::QQQVGA_RGB565, SIOD, SIOC, VSYNC, HREF, XCLK, PCLK, D0, D1, D2, D3, D4, D5, D6, D7);
  BMP::construct16BitHeader(bmpHeader, camera->xres, camera->yres);
}

void loop()
{
  camera->oneFrame();
  Serial.println("hihihi");
  serve();
  //delay(3000);
  //displayRGB565(camera->frame, camera->xres, camera->yres);
}

void connectToWiFi(const char * ssid, const char * pwd){
  Serial.println("Connecting to WiFi network: " + String(ssid));

  // delete old config
  WiFi.disconnect(true);
  //register event handler
  WiFi.onEvent(WiFiEvent);
  
  //Initiate connection
  WiFi.begin(ssid, pwd);

  Serial.println("Waiting for WIFI connection...");
}

void WiFiEvent(WiFiEvent_t event){
    switch(event) {
      case SYSTEM_EVENT_STA_GOT_IP:
          //When connected set 
          Serial.print("WiFi connected! IP address: ");
          Serial.println(WiFi.localIP());  
          //initializes the UDP state
          //This initializes the transfer buffer
         // udp.begin(WiFi.localIP(),udpPort);
          connected = true;
          break;
      case SYSTEM_EVENT_STA_DISCONNECTED:
          Serial.println("WiFi lost connection");
          connected = false;
          break;
    }
}
