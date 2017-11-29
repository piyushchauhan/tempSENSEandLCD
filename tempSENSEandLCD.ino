#include<LiquidCrystal.h>
#include<DHT11.h>
int pin=10;         //the middle pin of DHT11
DHT11 dht11(pin);
LiquidCrystal lcd(12,11,5,4,3,2);
byte smiley[8] = {    //This is a smiey character
  B00000,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
byte wink[8] = {    //This is a wink smiley
  B00001,
  B10001,
  B00000,
  B00000,
  B10001,
  B01110,
  B00000,
};
byte heart[8]={     //This is heart emoticon
  B00000,
  B00000,
  B01010,
  B11111,
  B11111,
  B01110,
  B00100,
};
void setup(){
    lcd.begin(16,2);
    lcd.createChar(0, smiley);
    lcd.createChar(1, heart);
    lcd.createChar(2, wink);
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Hello World!!");
    lcd.setCursor(0,2);
    lcd.print("I am Arduino");
    Serial.begin(9600);
    pinMode(9 ,OUTPUT);
    pinMode(8 ,OUTPUT);
    pinMode(7 ,OUTPUT);
    digitalWrite(9, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(7, HIGH);
    delay(10);
    delay(500);
    lcd.write(byte(0));
    delay(1000);
    lcd.write(byte(1));
    delay(1000);
    lcd.write(byte(2));
    delay(50);
}
void loop(){
    int err;
     float temp,humi;
     lcd.clear();
     if((err=dht11.read(humi,temp)==0))
     {
        Serial.print("Temperature: ");
        Serial.print(temp);
        Serial.write("\t");
        Serial.print("Humidity: ");
        Serial.print(humi);
        Serial.println();
        lcd.clear();
        lcd.print("Temp: ");
        lcd.print(temp);
        lcd.write("  ");
        lcd.write(byte(0));
        lcd.write(byte(1));
        lcd.write(byte(2));
        lcd.setCursor(0,2);
        lcd.print("Humid: ");
        lcd.print(humi);
        lcd.write(" ");
        lcd.write(byte(0));
        lcd.write(byte(1));
        lcd.write(byte(2));
        {
            if (temp<22){   //cold set to below 22 degree C so blue glows
                digitalWrite(9, HIGH);
                digitalWrite(8, LOW);
                digitalWrite(7, LOW);
                }
            else if (temp >= 28) { //hot set to above and 28 degree C so red glows
                digitalWrite(9, LOW);
                digitalWrite(8, LOW);
                digitalWrite(7, HIGH);
                }
            else { //when temp is between 22 and 28 so green glows
                digitalWrite(9, LOW);
                digitalWrite(8, HIGH);
                digitalWrite(7, LOW);
                }
        }
     }
     else
     {
        Serial.println();
        Serial.print("Error No :");
        Serial.print(err);
        Serial.println();    
    }
    delay(DHT11_RETRY_DELAY); //delay for reread
    lcd.blink();
}
