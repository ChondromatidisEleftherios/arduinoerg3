int trigPin=13;
int echoPin=12;
int l1=2;
int l2=3;
int l3=4;
int panep=6;
int r=7;
int o=8;
int g=9;
int time= 23;
int pi=10;
int pir=11;
int state = LOW; 
int val =1; 
long duration;
int distance;
void setup()
{
  pinMode(l1, OUTPUT);
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(o, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(panep, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(pi, OUTPUT);
  pinMode(pir, INPUT);
  Serial.begin(9600);
}

void loop()
{
  int value = analogRead(A0);
  Serial.println("Analog value : ");
  Serial.println(value);
  if (value<=929)
  {
    digitalWrite(l1,HIGH);
    digitalWrite(l2, HIGH);
    digitalWrite(l3, HIGH);
  }
  else 
  {
    digitalWrite(l1,LOW);
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
  }
  
  delay (100);
  if (((time>=0) && (time<=6))||(time==23))
  {
    digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
    if (distance <= 25)
    {
      noTone(pi);
      delay(10);
      tone(pi, 1500);
      delay(10);
      digitalWrite(o, LOW);
      digitalWrite(g, LOW);
      digitalWrite(r, HIGH);
    }
    else if (((distance > 25)&&(distance <=50)))
    {
      noTone(pi);
      delay(10);
      tone(pi, 666);
      delay(10);
     digitalWrite(g, LOW);
      digitalWrite(r, LOW);
     digitalWrite(o, HIGH);        
  }
    else if (distance > 50)
    {
      noTone(pi);
      delay(10);
      tone(pi, 300);
      delay(10);
      digitalWrite(o, LOW);
      digitalWrite(r, LOW);
      digitalWrite(g, HIGH); 
    }
    
  }
  else
  {
  Serial.println("Einai mera");
  }
 
  val = digitalRead(pir);
  Serial.println(val);
  if (val == 1) {         
    digitalWrite(panep, HIGH);  
    delay(100);                
    
    if (state == LOW) {
      Serial.println("Motion detected!"); 
      state = HIGH;       
    }
  } 
  else {
      digitalWrite(panep, LOW); 
      delay(200);           
      
      if (state == HIGH){
        Serial.println("Motion stopped!");
        state = LOW;       
    }
  }
  delay(10);
}
