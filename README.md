# CARPET 
CARPET is a remote controllable robot car included a camera which is activated by a motion sensor to enchance your home security.

# Background
Based on our investigation, the commercial security cameras in the current market must be installed on wall or put at a fixed spot, and they only provide limited vision ranges. To monitor the entire house, a customer has to purchase multiple cameras and install them all around the house. It becomes a waste of time and money when the scale of environment area is large. To solve the problem, our team come up with a solution, CARPET - an automatic house security guard.

# Introduction
<img src="/Report/pic/structure.png" width="80%" height="80%">
The skeleton of CARPET is based on ESP8266 chips. The ESP8266 serves as a bridge between the hardware components and the web server. To generate the full functionality of the automatic house security guard, we aggregated a motion sensor and a camera into a motor robot car. The motor robot car provides the mobility of the camera and the motion sensor. All components are connected to the web server through ESP chips. The web server is implemented by Node.js and run on an Amazon EC2 instance. The web application is developed in HTML and JavaScript.<br><br>
ESP8266
<img src="/Report/pic/ESP8266.png" title="ESP8266" width="30%" height="30%">
ESP32
<img src="/Report/pic/ESP32.png" title="ESP32"width="30%" height="30%">
These ESP chips are the heart of CARPET. They provide connectivity to other components. The manufacture model of ESP8266 we adopting is ESP-12E NodeMCU. CARPET has two ESP8266. One is integrated with the motor robot car. It makes the car become remotely controllable. The other one is integrated with a motion sensor to help send alarms to the server. For the camera component, it needs more bandwidth to upload live streaming video. Hence, we replaced ESP8266 with ESP32, a successor to ESP8266, integrating it with a camera.

# Demo
[![Alt text](https://img.youtube.com/vi/NtMm6EnA934/0.jpg)](https://www.youtube.com/watch?v=NtMm6EnA934)
# Technology
**Software**<br>
**Language:** C, Javascript, HTML, CSS<br>
**Library:** ESP8266 libraries, jQuery<br>
**Framework:** Node.js, Apache2, PhoneGap<br>

**Hardware**<br>
**Chip:** ESP8266, ESP32<br>
**Camera:** OV7670<br>
**Motion Sensor:** HC-SR501<br>
**Car:** 2WD Motor Smart Robot Car<br>
**Car Motor Controller:** L298N H-bridge<br>
# Contributers
<a href="https://github.com/kaicl">**_Kai Chieh Liu_**</a> Front-end Design and development, Car case development, Presentation<br>
<a href="https://github.com/tyeh11">**_Ting-Chi Yeh_**</a> Camera assembly, Camera control development, Backend development<br>
<a href="https://github.com/whchang10">**_Wen-Han Chang_**</a> Car assembly, Car control development, Motion sensor assembly, Motion sensor control development<br>
