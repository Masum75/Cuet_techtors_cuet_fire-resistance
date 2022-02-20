#include<LiquidCrystal.h>
#include<Servo.h>
Servo servo;
int contrast = 100;
LiquidCrystal lcd(0, 1, 2, 4, 5, 6);
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
   servo.attach(9);
}
void loop()
{
  reading = analogRead(A5);
  servo.write(0);
   if(reading>200)
   {
    digitalWrite(buzzer, HIGH);
    lcd.clear();
     lcd.setCursor(4, 0);
   lcd.print("Gas leak ");
   lcd.setCursor(4, 1);
   lcd.print("Detected");
   
   delay(10000);
   
   digitalWrite(buzzer, LOW);
   
   servo.write(180);
   digitalWrite(relay, HIGH);
   delay(10000);
   digitalWrite(relay, LOW);
   
   sendSMS();
   call();
   }
   else{
    lcd.clear();
    lcd.setCursor(3, 1);
    lcd.print("No gas leak");
    delay(10000);
   }
   
}
