void setup() {
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); //pin 2 jako wewnęrzny pull-up resistor
  pinMode(13, OUTPUT);

}

void loop() {
  int sensorVal = digitalRead(2); //wartości z kontaktronu
  Serial.println(sensorVal); //1, gdy okno otwarte, 0 gdy zamknięte
  if(sensorVal == HIGH) {
    digitalWrite(13,LOW);
  } else {
    digitalWrite(13, HIGH);
  }

}
