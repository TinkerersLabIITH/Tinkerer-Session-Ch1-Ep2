#include <AdafruitIO.h> 

#define IO_USERNAME  ""
#define IO_KEY       ""

#define WIFI_SSID "" 
#define WIFI_PASS ""

#include <AdafruitIO_WiFi.h>  
AdafruitIO_WiFi io(IO_USERNAME, IO_KEY, WIFI_SSID, WIFI_PASS); 

#define LED_PIN 12 

void handleMessage(AdafruitIO_Data *data){ 

  Serial.print("received <- ");
 
  if(data->toPinLevel() == HIGH)
    Serial.println("HIGH");
  else
    Serial.println("LOW");

  digitalWrite(LED_PIN, data->toPinLevel());
 
}

// set up the 'digital' feed 
AdafruitIO_Feed *digital = io.feed("digital"); 

void setup() {
 
  // set led pin as a digital output
  pinMode(LED_PIN, OUTPUT); 
  pinMode(13,OUTPUT);
  pinMODE(13,HIGH);
 
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

void loop() {
  io.run(); 
}
