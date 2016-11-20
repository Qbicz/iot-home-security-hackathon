#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

const char* server = "192.168.137.1";
const int port = 80;

const char* ssid = "ESPTest";
const char* pass = "test1234";

const int doorSensorPin = 13;
const int temperatureSensorPin = A0;

const float SCALLING_FACTOR = 10.0;
//const int ledPin = 7777;

void sendHttpPostData(int roomId, bool sensor, float analogValue)
{
    //"room=1&data=[1,23.7]";
    String PostData = "room=";
    PostData += roomId;
    PostData += "&data=";
    PostData += 'x';
//    PostData += ",";
//    PostData += analogValue;
//    PostData += "]";
    
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    Serial.print("Trying: "); Serial.print(server); Serial.print(":"); Serial.println(port);

    if (client.connect(server, port)) 
    {
        client.println("POST /data/send HTTP/1.1");
        client.println("Host: 192.168.137.1");
        client.println("Cache-Control: no-cache");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.print("Content-Length: ");
        client.println(PostData.length());
        client.println();
        client.println(PostData);
        
//for debugging
        //Serial.println(PostData);
        
        long interval = 2000;
        unsigned long currentMillis = millis(), previousMillis = millis();
        
        while(!client.available()){
        
          if( (currentMillis - previousMillis) > interval ){
        
            Serial.println("Timeout");
            //blinkLed.detach();
            //digitalWrite(2, LOW);
            client.stop();     
            return;
          }
          currentMillis = millis();
        }
        
        while (client.connected())
        {
          while ( client.available() )
          {
            String line = client.readStringUntil('\r');
            Serial.print(line);
          }      
        }
        client.stop();
    }
    
}

void setup() {
    pinMode(doorSensorPin, INPUT_PULLUP);
  
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP(ssid, pass);

    Serial.println();
    Serial.println();
    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println("");
    Serial.println("WiFi connected");
    Serial.println("IP address: ");
    Serial.println(WiFi.localIP());

    delay(500);
}


void loop() {
    const int roomId = 1;
    bool locked = digitalRead(doorSensorPin);
    float temperature = analogRead(temperatureSensorPin)/SCALLING_FACTOR;


    sendHttpPostData(roomId, locked, temperature);
    
    Serial.println("wait 5 sec...");
    delay(5000);
}

