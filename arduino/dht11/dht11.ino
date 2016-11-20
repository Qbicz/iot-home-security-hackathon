#include <dht11.h>
 
dht11 DHT11;
 
#define DHT11PIN 2    //przypisanie pinu 2 Arduino jako odczyt z sensora
int tempPin = 1;
float temp;
 
void setup()
{
  Serial.begin(9600);                    //inicjalizacja monitora szeregowego
  Serial.println("Program testowy DHT11"); 
  Serial.println();
;
}
 
void loop()
{
  int chk = DHT11.read(DHT11PIN);         //sprawdzenie stanu sensora, a następnie wyświetlenie komunikatu na monitorze szeregowym
 
  Serial.print("Stan sensora: ");
  switch (chk)
  {
    case DHTLIB_OK: 
        Serial.print("OK\t"); 
        break;
    case DHTLIB_ERROR_CHECKSUM: 
        Serial.println("Błąd sumy kontrolnej"); 
        break;
    case DHTLIB_ERROR_TIMEOUT: 
        Serial.println("Koniec czasu oczekiwania - brak odpowiedzi"); 
        break;
    default: 
        Serial.println("Nieznany błąd"); 
        break;
  }
  Serial.print("Wilgotnosc (%): ");              //wyświetlenie wartości wilgotności
  Serial.print((float)DHT11.humidity, 2);
  Serial.print("\t\t");
  Serial.print("Temperatura (C): ");           //wyświetlenie temperatury
  Serial.println((float)DHT11.temperature-3, 2);
  Serial.print("\t\t");
  float temp;
  temp = (5.0 * analogRead(tempPin) * 100.0) / 1024;
  Serial.print("Temperatura_lm (C): ");  
  Serial.println(temp);
  Serial.print("\t\t");
  delay(200);
  
 
  delay(1000);                                  //opóźnienie między kolejnymi odczytami - 1 s
} 
