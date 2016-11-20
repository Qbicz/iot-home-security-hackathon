void setup(){  
  Serial.begin(9600);  
  pinMode(A0, INPUT);  
}  
  
void loop(){  
  int pomiar=analogRead(A0);  
  Serial.print(pomiar);  
  if(pomiar>100){  
    Serial.print("GAZ!!");  
  }  
  Serial.println();  
  delay(250);  
}  
