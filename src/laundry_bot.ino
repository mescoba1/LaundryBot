#include <WiFi.h>
#include <Adafruit_MQTT.h>
#include <Adafruit_MQTT_Client.h>

// Adafruit IO Credentials
#include "aio.h"

// WiFi Credentials
#include "wifi.h"

#define washerPin A0
#define dryerPin A1
#define relayPin A2

//Username & AIO key
#define AIO_SERVER          "io.adafruit.com"
#define AIO_SERVERPORT      1883                   // use 8883 for SSL
#define AIO_WASHER_FEED "/feeds/washervibrations"
#define AIO_DRYER_FEED "/feeds/dryervibrations"
//#define AIO_USERNAME  "<AIO_USERNAME>"
//#define AIO_KEY       "<AIO_KEY>"
 
// WiFi SSID & Password
//#define WLAN_SSID "<SSID>"
//#define WLAN_PASS "<PASSWORD>"

// Create an ESP8266 WiFiClient class to connect to the MQTT server.
WiFiClient client;

// Setup the MQTT client class by passing in the WiFi client and MQTT server and login details.
Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, AIO_USERNAME, AIO_KEY);

// Setup a feeds for publishing changes.
Adafruit_MQTT_Publish washer_feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME AIO_WASHER_FEED);
Adafruit_MQTT_Publish dyer_feed = Adafruit_MQTT_Publish(&mqtt, AIO_USERNAME AIO_DRYER_FEED);
 
void MQTT_connect();

void setup() {
  pinMode(relayPin, OUTPUT);
  digitalWrite(relayPin, LOW);
  
  Serial.begin(115200);
  delay(10);
 
  // Connect to WiFi access point.
  Serial.println(); Serial.println();
  Serial.print("Connecting to ");
  Serial.println(WLAN_SSID);
 
  WiFi.begin(WLAN_SSID, WLAN_PASS);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println();
 
  Serial.println("WiFi connected");
  Serial.println("IP address: "); 
  Serial.println(WiFi.localIP());
 
  // Setup MQTT subscription for onoff feed.
  //mqtt.subscribe(&onoffbutton);
}
 
uint32_t x=0;
 
void loop() {
  // Ensure the connection to the MQTT server is alive (this will make the first
  // connection and automatically reconnect when disconnected).  See the MQTT_connect
  // function definition further below.
  MQTT_connect();
 
  // this is our 'wait for incoming subscription packets' busy subloop
  // try to spend your time here
 
  Adafruit_MQTT_Subscribe *subscription;
  while ((subscription = mqtt.readSubscription(5000))) {
    if (subscription == &onoffbutton) {
      Serial.print(F("Got: "));
      Serial.println((char *)onoffbutton.lastread);
      //converts the received 1 or 0 to string to compare in the if-else statement
      String response = (char*)onoffbutton.lastread; 
      
      if (response == "1"){
        digitalWrite(relayPin, HIGH);
      }
      else {
        digitalWrite(relayPin, LOW);
      }
    }
  }
}

void MQTT_connect() {
  int8_t ret;
 
  // Stop if already connected.
  if (mqtt.connected()) {
    return;
  }
 
  Serial.print("Connecting to MQTT... ");
 
  uint8_t retries = 3;
  while ((ret = mqtt.connect()) != 0) { // connect will return 0 for connected
       Serial.println(mqtt.connectErrorString(ret));
       Serial.println("Retrying MQTT connection in 5 seconds...");
       mqtt.disconnect();
       delay(5000);  // wait 5 seconds
       retries--;
       if (retries == 0) {
         // basically die and wait for WDT to reset me
         while (1);
       }
  }
  Serial.println("MQTT Connected!");
}