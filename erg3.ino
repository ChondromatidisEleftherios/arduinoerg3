// Θέτω τιμές σε μεταβλητές για να ορίσω τις θέσεις των pin στο arduino//
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
void setup()//Συνάρτηση που θα τρέξει ΜΟΝΟ ΜΙΑ ΦΟΡΑ όταν θα εκτελέσουμε το πρόγραμμα//
{
  pinMode(l1, OUTPUT); //Θέτω όλα τα led ως εξόδους//
  pinMode(l2, OUTPUT);
  pinMode(l3, OUTPUT);
  pinMode(r, OUTPUT);
  pinMode(o, OUTPUT);
  pinMode(g, OUTPUT);
  pinMode(panep, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT); 
  pinMode(pi, OUTPUT);
  pinMode(pir, INPUT); //Θέτω το PIR Sensor ως input//
  Serial.begin(9600); //Χρησιμοποιούμε τη συνάρτηση αυτή για να επικοινωνήσουμε το Arduino μέσω εισόδων και εξόδων//
}

void loop()//Συνάρτηση που θα επαναλαμβάνεται συνέχεια μέχρι να τερματίσουμε το πρόγραμμα//
{
  int value = analogRead(A0); //Analog read επειδή είναι συνδεδεμένο σε αναλογικό pin στο arduino//
  Serial.println("Analog value : ");
  Serial.println(value); //Εμφάνιση της τιμής του σένσορα//
  if (value<=929)//Αν η φωτεινότητα είναι <= 929//
  {
    digitalWrite(l1,HIGH); //Να ανάψουν όλα τα ledάκια της πόλης//
    digitalWrite(l2, HIGH);
    digitalWrite(l3, HIGH);
  }
  else if (value > 929) //Αν η φωτεινότητα είναι > 929//
  {
    digitalWrite(l1,LOW); //Να σβήσουν όλα τα ledάκια της πόλης//
    digitalWrite(l2, LOW);
    digitalWrite(l3, LOW);
  }
  
  delay (100);
  if (((time>=0) && (time<=6))||(time==23)) //Αν η ώρα είναι 23:00 - 6:00//
  {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration * 0.034 / 2;
    if (distance <= 25) //Εαν η απόσταση είναι μικρότερη από 25 μέτρα//
    {
      noTone(pi);
      delay(10);
      tone(pi, 1500); //Το piezo να βγάλει ήχο συχνότητας 1500//
      delay(10);
      digitalWrite(o, LOW); //Nα σβήσει το πορτοκαλί ledάκι//
      digitalWrite(g, LOW); //Nα σβήσει το πράσινο ledάκι//
      digitalWrite(r, HIGH); //Να ανάψει το κόκκινο ledάκι//
      Serial.println("O EISBOLEAS EINAI EDW!!! TREXA!");
    }
    else if (((distance > 25)&&(distance <=50)))//Εαν η απόσταση είναι μεταξύ των 25 και 50 μέτρων//
    {
      noTone(pi);
      delay(10);
      tone(pi, 666); //Το piezo να βγάλει ήχο συχνότητας 666//
      delay(10);
     digitalWrite(g, LOW); //Nα σβήσει το πράσινο ledάκι//
      digitalWrite(r, LOW); //Να σβήσει το κόκκινο ledάκι//
     digitalWrite(o, HIGH); //Nα ανάψει το πορτοκαλί ledάκι//  
     Serial.println("EISBOLEAS PLHSIAZEI!");
  }
    else if (distance > 50) //Εαν η απόσταση είναι μεγαλύτερη από τα 50 μέτρα//
    {
      noTone(pi);
      delay(10);
      tone(pi, 300); //Το piezo να βγάλει ήχο συχνότητας 300//
      delay(10);
      digitalWrite(o, LOW); //Nα σβήσει το πορτοκαλί ledάκι//
      digitalWrite(r, LOW); //Nα σβήσει το κόκκινο ledάκι//
      digitalWrite(g, HIGH); //Nα ανάψει το πράσινο ledάκι//
      Serial.println("EISBOLEAS LIGO PIO MAKRIA APO 50 METRA...");
    }
    
  }
  else //Αν είναι μέρα//
  {
  Serial.println("Einai mera."); //Μήνυμα πως είναι μέρα ακόμα//
  }
 
  delay (200);
  val = digitalRead(pir); //Διάβασμα τιμής PIR αισθητήρα//
  if (val == HIGH) { //Αν ανιχνεύτηκε κίνηση//           
    digitalWrite(panep, HIGH); //Να ανάψει το ledάκι//   
    delay(100);                
    
    if (state == LOW) { //Αν η κατάσταση κίνησης ήταν low//
      Serial.println("KINHSH MESA STO PANEPISTHMIO"); 
      state = HIGH;  //Να γίνει high αφού υπάρχει κίνηση//     
    }
  } 
  else if (val==LOW){ //Aν δεν υπάρχει κίνηση//
      digitalWrite(panep, LOW); //Να σβήσει το ledάκι//
      delay(200);              
      
      if (state == HIGH){ //Αν η κατάσταση κίνησης ήταν high//
        state = LOW; //Nα γίνει low αφού δεν υπάρχει κίνηση//        
    }
  }
  delay(50);
}
