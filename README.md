# LaundryBot
Interface ESP32 with Facebook Messenger for laundry notifications

Based On:
- [Home Automation](https://community.createlabz.com/knowledgebase/home-automation-using-facebook-messenger-and-esp8266-nodemcu/)

## Hardware Components
1. ESP32 (1)
2. Vibration Sensors (2)
3. Noise Sensor (1)
4. Breadboards (2)

## Software Services
1. Arduino CLI
2. Facebook Messenger
3. IFFT Applet
4. Chatfuel

## Steps
1. Setup Hardware
  - Connect Arduino to Vibrations & Sound Sensors via Analog Pins
2. Adafruit IO Setup
  - Set up Feed + Dashboard
3. Arduino IDE Setup
  - Configure ESP32 Board
4. Chatfuel Setup
  - Create Facebook Page + Permission
5. IFTT Setup
 - Create Applet w/ Webhooks
6. Code
  - Adafruit_MQTT.h
  - Adafruit_MQTT_Client.h
  - ESP8266WiFi.h