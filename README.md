# Sera-Projem
//KULLANDIĞIM KODLAR

#include <Servo.h>       //Servo motor kütüphanesini ekledim.

#include <DHT11.h>      //Sıcaklık ve nem sensörü kütüphanesini ekledim.
#include <LiquidCrystal.h>      //LCD ekran kütüphanesini ekledim.

const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;       //Lcd ekran pinlerini tanımladım.
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

DHT11 dht11(6); //Sıcaklık ve nem sensörünü bağladığım pini tanımladım.
Servo myservo;

void setup() {
  Serial.begin(9600);
  lcd.begin(16, 2); 
  myservo.attach(9); //Servo motorumu bağladığım pini tanımladım.
}

void loop() {
  int temperature = dht11.readTemperature();         //Sensörden gelen sıcaklık değerini okudum.
  int humidity = dht11.readHumidity();           //Sensörden gelen nem değerini okudum.
  lcd.setCursor(0, 0);            //Yazacağı satırı belirttim.
  lcd.print("Sicaklik: "); 
  lcd.print(temperature);             //Sensörden gelen sıcaklık değerini ekrana yazdırdım.
  lcd.setCursor(0, 1);           //Yazacağı satırı belirttim.
  lcd.println("Nem: ");
  lcd.print(humidity);         //Sensörden gelen nem değerini ekrana yazdırdım.
  if(temperature>30)
  {
    myservo.write(130);        //Servo motora açı vererek açılmasını sağladım.
  }
  else{
    myservo.write(70);          //Servo motorun eğerki sıcaklık düşükse eski haline gelerek açılmasını sağladım.
  }
  delay(500);

}

