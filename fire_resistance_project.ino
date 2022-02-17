#include<LiquidCrystal.h>
int contrast = 100;
LiquidCrystal lcd(4, 5, 6, 7, 8, 9);
#include <SoftwareSerial.h>
SoftwareSerial SIM900A(10, 11);

int lpg = A5;
int buzzer = 13;
int reading;
int relay = A0;

void sendSMS(){
 
  SIM900A.println("AT+CMGF=1");    //Sets the GSM Module in Text Mode
  delay(1000);
  SIM900A.println("AT+CMGS=\"+8801991545081\"\r"); //Mobile phone number to send message
  delay(1000);
  SIM900A.println("Gas leak detected in your house");// Messsage content
  delay(100);
  SIM900A.println((char)26);// ASCII code of CTRL+Z
  delay(1000);
  SIM900A.println();
  delay(5000);
}
void call(){
  SIM900A.println("ATD + +8801991545081;");
  delay(100);
  SIM900A.println();
}




void setup()
{
  analogWrite(3, contrast);
  lcd.begin(16, 2);
  pinMode(lpg, INPUT);
  pinMode(buzzer, OUTPUT);
  pinMode(relay, OUTPUT);
   SIM900A.begin(9600);
}
void loop()
{
  reading = analogRead(A5);
   if(reading>150)
   {
    digitalWrite(buzzer, HIGH);
     lcd.setCursor(4, 0);
   lcd.print("Gas leak ");
   lcd.setCursor(4, 1);
   lcd.print("Detected");
   delay(10000);
   digitalWrite(buzzer, LOW);
   lcd.clear();
   digitalWrite(relay, HIGH);
   delay(10000);
   digitalWrite(relay, LOW);
   sendSMS();
   call();
   
   }
  
  
}
