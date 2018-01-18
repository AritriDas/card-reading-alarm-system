#include <SPI.h>
#include <MFRC522.h>
 
#define SS_PIN 10
#define RST_PIN 9
MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
  int t=200;
void setup() 
{ pinMode(5,INPUT);
  digitalWrite(1,0);
 pinMode(3,OUTPUT);
  pinMode(6,OUTPUT);
  pinMode(7,OUTPUT);
  pinMode(4,OUTPUT);

  Serial.begin(9600);   
  SPI.begin();      
  mfrc522.PCD_Init();   
  Serial.println("Put your card to the reader...");
  Serial.println();
 

}

void lock()
{
  digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
    analogWrite(4,250);
    delay(t);
      digitalWrite(7,LOW);
    digitalWrite(6,HIGH);
    analogWrite(4,0);

}

void unlock()
{
    
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    analogWrite(4,250);
    delay(t);
    digitalWrite(7,HIGH);
    digitalWrite(6,LOW);
    analogWrite(4,0);
}

void buzzer(int val)
{
if(val==1)
  {
   digitalWrite(3,1);
   card(); 
  }
  else
   digitalWrite(3,0);  
}

void loop() 
{
  
  int val=digitalRead(5);
  Serial.println(val);
  buzzer(val);
} 

void card()
{

  // Look for new cards
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Show UID on serial monitor
  Serial.print("UID tag :");
  String content= "";
  byte letter;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     content.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     content.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Message : ");
  content.toUpperCase();
  if (content.substring(1) == "EA FC 2A 04") //change here the UID of the card/cards that you want to give access
  { 
    digitalWrite(3,0); 
    Serial.println("Authorized access");
    Serial.println();
    unlock();
    delay(5000);
    lock();
    delay(3000);
  }
 
 else   {
    
    Serial.println("Access denied");
    lock();
    delay(3000);
  }
}

