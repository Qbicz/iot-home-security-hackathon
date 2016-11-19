int czujnik = 8;   //pin 8 połączony z sygnałem z czujnika
 
void setup(){
  Serial.begin(9600);        
  pinMode(czujnik, INPUT);   
   
  Serial.println("---- TEST CZUJNIKA RUCHU ----"); 
}
 
void loop(){
  int ruch = digitalRead(czujnik);      
  if(ruch == HIGH)                      
  {                                     
    Serial.println("RUCH WYKRYTY!");
  }
  else  {Serial.println("BRAK RUCHU");}
   
  delay(200);                         
}
