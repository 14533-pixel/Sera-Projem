#include <Servo.h>
#include <DHT11.h>
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

DHT11 dht11(3);

LiquidCrystal_I2C lcd(0x27,20,4); 

const int prob = A0;
int olcum_sonucu;

Servo myservo;
Servo myservo2;

int waterlevel=A1;
int water;

int role=9;

void setup()
{
  lcd.init();                     
  lcd.init();
  lcd.backlight();
  Serial.begin(9600);
  myservo.attach(5);
  myservo2.attach(6);
  pinMode(waterlevel,INPUT);
  pinMode(role,OUTPUT);
  digitalWrite(role,LOW);
}


void loop()
{
  int temperature = dht11.readTemperature();
  lcd.setCursor(1,0);
  lcd.print("Sicaklik: ");
  lcd.setCursor(11,0);
  lcd.print(temperature);
  lcd.setCursor(14,0);
  lcd.print(" C");
  delay(1000);
  water=analogRead(waterlevel);
  Serial.println(water);
  //600 üzeri dolu
  //600 altı bitmek üzere
  //300 altı bitti
  if(temperature>27)
  {
    myservo.write(30); //ön
    myservo2.write(150); //arka
    lcd.setCursor(1,1);
    lcd.print("                ");
    lcd.setCursor(1,1);
    lcd.print("cati acik");
    delay(2000);
  }
  else
  {
    myservo.write(0); //ön
    myservo2.write(180); //arka
    lcd.setCursor(1,1);
    lcd.print("cati kapali");
    delay(2000);
  }
  olcum_sonucu = analogRead(prob);
  if(olcum_sonucu>700)
  {
    lcd.setCursor(1,1);
    lcd.print("toprakta su yok");
    delay(2000);
    digitalWrite(role,HIGH);
  }
  else
  {
    lcd.setCursor(1,1);
    lcd.print("toprakta su var");
    delay(2000);
    digitalWrite(role,LOW);
  }
  lcd.setCursor(1,1);
  lcd.print("                ");
  if(water>600)
  {
    lcd.setCursor(1,1);
    lcd.print("depo dolu");
    delay(2000);
  }
  else if(water<550 and water>350)
  {
    lcd.setCursor(1,1);
    lcd.print("depo bitiyor");
    delay(2000);
  }
  else
  {
    lcd.setCursor(1,1);
    lcd.print("                ");
    lcd.setCursor(1,1);
    lcd.print("depo bitti");
    delay(2000);
  }
  delay(500);
}
