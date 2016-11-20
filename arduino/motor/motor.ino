int motor = 9;
void setup() {
  pinMode(motor, OUTPUT);
  Serial.begin(9600);

}
void loop() {
  digitalWrite(motor, !digitalRead(motor));
  delay(3000);
}
