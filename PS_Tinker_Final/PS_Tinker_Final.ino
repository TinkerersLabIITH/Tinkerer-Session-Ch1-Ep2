#include <AdafruitIO.h> 
#include "Adafruit_MQTT.h"
#include "Adafruit_MQTT_Client.h"

#define AIO_SERVER      "io.adafruit.com"
#define AIO_SERVERPORT  1883

#define IO_USERNAME  "PS_Assistant"
#define IO_KEY       ""

#define WIFI_SSID "" 
#define WIFI_PASS ""  

#include <AdafruitIO_WiFi.h>  
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); 
WiFiClient client;


Adafruit_MQTT_Client mqtt(&client, AIO_SERVER, AIO_SERVERPORT, IO_USERNAME, IO_KEY);
Adafruit_MQTT_Publish Tinker = Adafruit_MQTT_Publish(&mqtt, IO_USERNAME "/feeds/Tinker");
AdafruitIO_Feed *digital = io.feed("Tinker"); 

#define LED_PIN 12
#define Sensor_Pin 34
int temp=0;
int minimum_value=0; // According to your LDR

void handleMessage(AdafruitIO_Data *data){ 

  Serial.print("received <- ");
 
  if(data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");

  digitalWrite(LED_PIN, data->toPinLevel());
 
}

void setup() {
   
  // set led pin as a digital output
  pinMode(LED_PIN, OUTPUT);
  pinMode(Sensor_Pin,INPUT);
  pinMode(13,OUTPUT);
  digitalWrite(13,HIGH); 

 
  // start the serial connection
  Serial.begin(115200); 
 
  // wait for serial monitor to open
  while(! Serial);
 
  // connect to io.adafruit.com
  Serial.println("Connecting to Adafruit IO"); 
  io.connect(); 
  digital->onMessage(handleMessage);
 
  // wait for a connection
  while(io.status() < AIO_CONNECTED) {
    Serial.println("Can't connect to Adafruit IO  ");
    delay(500);
  }
 
  Serial.println();
  Serial.println(io.statusText()); 
  digital->get();
  digital->onMessage(handleMessage); 
}

void connect() {
  Serial.print(F("Connecting to Adafruit IO... "));
  int8_t ret;
  while ((ret = mqtt.connect()) != 0) {
    switch (ret) {
      case 1: Serial.println(F("Wrong protocol")); break;
      case 2: Serial.println(F("ID rejected")); break;
      case 3: Serial.println(F("Server unavail")); break;
      case 4: Serial.println(F("Bad user/pass")); break;
      case 5: Serial.println(F("Not authed")); break;
      case 6: Serial.println(F("Failed to subscribe")); break;
      default: Serial.println(F("Connection failed")); break;
    }

    if(ret >= 0)
      mqtt.disconnect();

    Serial.println(F("Retrying connection..."));
    delay(10000);
  }
  Serial.println(F("Adafruit IO Connected!"));
}


void loop() {
  io.run(); 
  
  int ra1=analogRead(Sensor_Pin);
  Serial.println(ra1);

 if(! mqtt.ping(3)) {
    // reconnect to adafruit io
    if(! mqtt.connected())
      connect();
  }
  int k;
  temp++;
  
  if(temp==20)
  {
    if(ra1>minimum_value)
      k=1;
    else
        k=0;

    //Serial.print("Value of ra1 =");
   // Serial.println(ra1);
    
    if (! Tinker.publish(k)) {                     //Publish to Adafruit
      Serial.println(F("Failed"));
    } else {
      Serial.println(F("Sent!"));
    }
    temp=0;   
 }
}
