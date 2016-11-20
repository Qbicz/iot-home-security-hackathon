#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;


const int doorSensorPin = 13;
//const int ledPin = 7777;

void action0_turnTheLightOn()
{
  
}

void action1_turnTheLightOn()
{
  
}

void action2_Alarm1()
{
  
}

void action3_Alarm2();
{
    
}

void action4_coolingFan()
{
    
}

void takeActionBasedOnDataFromServer(String inputString)
{
    /*
     * ESP WiFi module receives a byte of data from 
     * smart home server and takes action in its local network
     */
    char inputChar = inputString.charAt(0);

    if (inputChar & 0x01 == 0x01)
    {
        client.println("Bit0: Turn the Light 1 ON");
        action0_turnTheLightOn();
    }
    if (inputChar & 0x02 == 0x02)
    {
        client.println("Bit1: Turn the Light 2 ON");
        action1_turnTheLightOn();
    }
    if (inputChar & 0x04 == 0x04)
    {
        client.println("Bit2: ALARM 1");
        action2_Alarm1();
    }
    if (inputChar & 0x08 == 0x08)
    {
        client.println("Bit3: ALARM 2");
        action3_Alarm2();
    }
    if (inputChar & 0x08 == 0x08)
    {
        client.println("Bit4: Cooling fan ON");
        action4_coolingFan();
    }
}

void sendHttpPostData(int roomId, bool sensor, float analogValue)
{
    //"room=1&data=[1,23.7]";
    String PostData = "room=";
    PostData += roomId;
    PostData += "&data=[";
    PostData += sensor;
    PostData += ",";
    PostData += analogValue;
    PostData += "]";
    
    const uint16_t port = 7777; //change it to 80 when HTTP server will be available
    const char* host = "10.42.0.1"; // ip of Piotrek's laptop
    // Use WiFiClient class to create TCP connections
    WiFiClient client;

    if (client.connect(host, port)) 
    {
        client.println("POST /posts HTTP/1.1");
        client.println("Host: 10.42.0.1");
        client.println("Cache-Control: no-cache");
        client.println("Content-Type: application/x-www-form-urlencoded");
        client.print("Content-Length: ");
        client.println(PostData.length());
        client.println();
        client.println(PostData);
        client.stop();
//for debugging
        Serial.println(PostData);
        
//        long interval = 2000;
//        unsigned long currentMillis = millis(), previousMillis = millis();
//        
//        while(!client.available()){
//        
//          if( (currentMillis - previousMillis) > interval ){
//        
//            Serial.println("Timeout");
//            //blinkLed.detach();
//            //digitalWrite(2, LOW);
//            client.stop();     
//            return;
//          }
//          currentMillis = millis();
//        }
        
//        while (client.connected())
//        {
//          if ( client.available() )
//          {
//            char str=client.read();
//            Serial.println(str);
//          }      
//        }
    }
    
}

void setup() {
    pinMode(doorSensorPin, INPUT_PULLUP);
  
    Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP("LetsCodeESP", "ssij1234");

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
    float temperature = 66.6;

    sendHttpPostData(roomId, locked, temperature);
    
    Serial.println("wait 5 sec...");
    delay(5000);
}

