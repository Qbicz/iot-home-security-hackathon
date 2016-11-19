int czujnik = 8; //pin 8 - sygnał z pir
int pullup = 2; //pin 2 - kontaktron
int dioda = 13; //pin 13 - dioda sprawdzajaca kontaktron
void setup() {
  Serial.begin(9600);
  pinMode(czujnik, INPUT);
  pinMode(pullup, INPUT_PULLUP);
  pinMode(dioda, OUTPUT);
 
}
void loop() {
  int ruch = digitalRead(czujnik);
  int sensorVal = digitalRead(pullup);
  if(sensorVal == HIGH && ruch == HIGH) {
    digitalWrite(dioda, LOW);
    Serial.println("RUCH WYKRYTY!      OKNO ZAMKNIĘTE!");
  }
  else if(sensorVal == LOW && ruch == HIGH) {
    digitalWrite(dioda, HIGH);
    Serial.println("RUCH WYKRYTY!      OKNO OTWARTE!");
  }
  else if(sensorVal == HIGH && ruch == LOW) {
    digitalWrite(dioda, HIGH);
    Serial.println("BRAK RUCHU!      OKNO ZAMKNĘTE!");
  }
  else if(sensorVal == LOW && ruch == LOW) {
    digitalWrite(dioda, HIGH);
    Serial.println("BRAK RUCHU!      OKNO ZAMKNIĘTE!");
  }
  delay(200);
}

