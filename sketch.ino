#include <LiquidCrystal.h>

LiquidCrystal lcd(5,4,11,10,9,8);

const int tempPin=A0;
const int heater=6;
const int fan=7;
const int buzzer=3;

float setTemp=25.0;

void setup()
{
  pinMode(heater,OUTPUT);
  pinMode(fan,OUTPUT);
  pinMode(buzzer,OUTPUT);

  lcd.begin(16,2);

  lcd.print("HVAC SYSTEM");
  delay(1500);
  lcd.clear();
}

void loop()
{
  int value=analogRead(tempPin);

  // Simulated Temperature 0-50°C
  float temperature=map(value,0,1023,0,500)/10.0;

  lcd.setCursor(0,0);
  lcd.print("Temp:");
  lcd.print(temperature,1);
  lcd.write(byte(223));
  lcd.print("C ");

  lcd.setCursor(0,1);
  lcd.print("Set:");
  lcd.print(setTemp,1);
  lcd.write(byte(223));
  lcd.print("C ");

  if(temperature<setTemp-1)
  {
    digitalWrite(heater,HIGH);
    digitalWrite(fan,LOW);
    noTone(buzzer);
  }
  else if(temperature>setTemp+1)
  {
    digitalWrite(heater,LOW);
    digitalWrite(fan,HIGH);
    noTone(buzzer);
  }
  else
  {
    digitalWrite(heater,LOW);
    digitalWrite(fan,LOW);
    noTone(buzzer);
  }

  if(temperature>=40)
  {
    tone(buzzer,1000);
  }

  delay(300);
}