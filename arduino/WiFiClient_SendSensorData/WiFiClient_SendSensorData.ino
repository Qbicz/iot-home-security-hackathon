#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <dht11.h>

dht11 DHT11;
#define DHT11PIN 12

#define ESP1 1
//define one of the ESP1 or ESP2 for compiling
//also remember to midify pinout if needed

ESP8266WiFiMulti WiFiMulti;

const char* server = "192.168.137.1";
const int port = 80;

const char* ssid = "ESPTest";
const char* pass = "test1234";

const int PirSensorPin = 16;
const int temperatureSensorPin = 12;
const int buzzerPin = 5;

const int LEDPin = 2;
const int MotorPin = 4;

const float SCALLING_FACTOR = 10.0;
const char STATUS_ERROR = 255;
const int CYCLE_TIME_S = 1;

void action0_setLight(bool state)
{
  //Serial.printf("Bit0: Light 1: %d\n", state);
  digitalWrite(LEDPin, state);
}

void action1_setLight(bool state)
{
  //Serial.printf("Bit1: Light 2: %d\n", state);
  digitalWrite(LEDPin, state);
}

void action2_Alarm1(bool state)
{
  //Serial.printf("Bit2: Alarm 1: %d\n", state);
  digitalWrite(buzzerPin, state);
}

void action3_Alarm2(bool state)
{
  //Serial.printf("Bit3: Alarm 2: %d\n", state);
}

void action4_coolingFan(bool state)
{
  //Serial.printf("Bit4: Fan: %d\n", state);
  digitalWrite(MotorPin, state);
}

void takeActionBasedOnDataFromServer(char inputChar)
{
    /*
     * ESP WiFi module receives a byte of data from 
     * smart home server and takes action in its local network
     */
    
    if(STATUS_ERROR == inputChar)
    {
      //Serial.printf("Error receiving data from server\n");
      return;
    }
        
    //Serial.printf("Received: %c, Taking actions:\n", inputChar);

    #ifdef ESP1
        action0_setLight((inputChar & 0x01) == 0x01);
        action2_Alarm1((inputChar & 0x04) == 0x04);
        action4_coolingFan((inputChar & 0x10) == 0x10);
    #endif

    #ifdef ESP2     
      action1_setLight((inputChar & 0x02) == 0x02);
      action3_Alarm2((inputChar & 0x08) == 0x08);   
    #endif
}

char exchangeDataUsingHTTP(int roomId, bool sensor, float analogValue)
{
    String lineBuffer = "";
     //"room=1&data=[1,23.7]";
    String PostData = "room=";
    PostData += roomId;
    PostData += "&data=";
    PostData += sensor;
    PostData += ",";
    PostData += analogValue;
    
    // Use WiFiClient class to create TCP connections
    WiFiClient client;
    //Serial.print("Trying: "); Serial.print(server); Serial.print(":"); Serial.println(port);

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
        
            //Serial.println("Timeout");
            //blinkLed.detach();
            //digitalWrite(2, LOW);
            client.stop();     
            return STATUS_ERROR;
          }
          currentMillis = millis();
        }
        
        while (client.connected())
        {
          while ( client.available() )
          {
            lineBuffer = client.readStringUntil('\n');
          }
        }
        //Serial.println(lineBuffer); 
        client.stop();
    }
    //Serial.printf("We will send %c\n", lineBuffer[0]);
    //Serial.printf("Its length is: %d\n", lineBuffer.length());

    if(lineBuffer.length() != 0)
      return lineBuffer[0];
    else
      return STATUS_ERROR;
}

void setup() {
    pinMode(PirSensorPin, INPUT);
    pinMode(temperatureSensorPin, INPUT);
    pinMode(LEDPin, OUTPUT);
    pinMode(MotorPin, OUTPUT);
    pinMode(buzzerPin, OUTPUT);
  
    //Serial.begin(115200);
    delay(10);

    // We start by connecting to a WiFi network
    WiFiMulti.addAP(ssid, pass);

//    Serial.println();
//    Serial.println();
//    Serial.print("Wait for WiFi... ");

    while(WiFiMulti.run() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

//    Serial.println("");
//    Serial.println("WiFi connected");
//    Serial.println("IP address: ");
//    Serial.println(WiFi.localIP());

    delay(500);
}


void loop() {
    const int roomId = 2;
    bool detected = digitalRead(PirSensorPin);
    float temperature = ((float)DHT11.temperature-3, DHT11PIN);
//    Serial.print("Temperatura (C): ");           //wyświetlenie temperatury
//    Serial.println(temperature);
    
    char action = exchangeDataUsingHTTP(roomId, detected, temperature);
    takeActionBasedOnDataFromServer(action);
    
    //Serial.printf("wait %d seconds...\n", CYCLE_TIME_S);
    delay(CYCLE_TIME_S*1000);
}

