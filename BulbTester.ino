#include <SoftwareSerial.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <Keypad.h>

LiquidCrystal_I2C lcd(0x27,16,2);//Default 0x27 

const byte ROWS = 4;
const byte COLS = 4;
char keys[ROWS][COLS] = {
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};
byte rowPins[ROWS] = {13,12,11,10}; // connect to the row pinouts of the keypad 
byte colPins[COLS] = {9,8,7,6}; // connect to the column pinouts of the keypad

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

int bulb=2;
int keyNum, num;
int delayTime=1000;
char key;

void setup()
{
  Serial.begin(9600);
  lcd.init();	//Initiate the I2C LCD module
  lcd.backlight();	//Turn on the LCD backlight
  pinMode(bulb, OUTPUT);
  start();
  
}
void start()
{
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("BULB TESTER");
  lcd.setCursor(1,1);
  lcd.print("S.E.Elec Div B");
  delay(3000);
}
char input()
{
  char key1;
  lcd.clear();
  lcd.setCursor(2,0);
  lcd.print("Blink [0-9]");
  lcd.setCursor(0,1);
  lcd.print("ON-A Off-B Rst-D");
  do{
    key1=keypad.getKey();
  }
  while(key1==NO_KEY);
    lcd.clear();
    return key1;
  
}
void blink(int n)
{
  for(int i=1;i<=n;i++)
  {
      
    lcd.setCursor(0,1);
    lcd.print("Blinked ");
    lcd.setCursor(8,1);
    lcd.print(i);
    lcd.setCursor(10,1);
    lcd.print("Rem ");
    lcd.setCursor(14,1);
    lcd.print(n-i);
    digitalWrite(bulb, HIGH);
    delay(delayTime);
    digitalWrite(bulb, LOW);
    delay(delayTime);
  }
}
void reset()
{
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Resetting...");
  digitalWrite(bulb, LOW);
  delay(2000);
  lcd.clear();
  lcd.setCursor(5,0);
  lcd.print("Reset");
  lcd.setCursor(2,1);
  lcd.print("Successfully");
  delay(2000);
  lcd.clear();
  start();
}
void loop()
{
  key = input();
  if(key)
  {
    keyNum=(int)key;
      lcd.clear();
      lcd.setCursor(3,0);
      lcd.print("Pressed ");
      lcd.setCursor(11,0);
      lcd.print(key);  
    if(keyNum>=48 && keyNum<=57)//[0-9]
    {
      num=keyNum-48;
      Serial.println(num);
      blink(num);
    }
    if(keyNum==65)//A - ON
    {
      lcd.setCursor(0,1);
      lcd.print("Bulb Stat ");
      lcd.setCursor(10,1);
      lcd.print("ON");
      digitalWrite(bulb,HIGH);
    }
    if(keyNum==66)//B - OFF
    {
      lcd.setCursor(0,1);
      lcd.print("Bulb Stat ");
      lcd.setCursor(10,1);
      lcd.print("OFF");
      digitalWrite(bulb,LOW);
    }
    if(keyNum==68)//B - OFF
    {
      reset();
    }
  }
}