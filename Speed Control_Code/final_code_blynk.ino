#define BLYNK_PRINT Serial

#define BLYNK_TEMPLATE_ID "TMPL6ge-1XtPE"
#define BLYNK_TEMPLATE_NAME "Cable car control"
#define BLYNK_AUTH_TOKEN "QmVk3zOxhj-K09rJGXFiH-bs3kzz2Wmg"

#include <ESP8266WiFi.h>
#include <BlynkSimpleEsp8266.h>
#include <LiquidCrystal_I2C.h>
#include <Wire.h>

char auth[] = BLYNK_AUTH_TOKEN;
char ssid[] = "Nha Tro 25 C";  // Nhập tên mạng WiFi của bạn
char pass[] = "matmangroi";    // Nhập mật khẩu mạng WiFi của bạn

int M1PWM = D5;
int M1F = D3;  // GPIO0
int M1R = D4;  // GPIO2
int pinValue1 = 0;
int increment = 15;  // Giá trị tăng/giảm tốc độ (có thể điều chỉnh)
LiquidCrystal_I2C lcd(0x27,16,2);

BLYNK_WRITE(V1)
{
  int buttonState = param.asInt();
  if (buttonState == HIGH)
  { 
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Start...");
    digitalWrite(M1F, HIGH);
    digitalWrite(M1R, LOW);
  }
  else
  {
    digitalWrite(M1F, LOW);
    digitalWrite(M1R, LOW);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Stop...");
  }
}

BLYNK_WRITE(V2)
{
  int buttonState = param.asInt();
  if (buttonState == HIGH)
  { 
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Start...");
    digitalWrite(M1F, LOW);
    digitalWrite(M1R, HIGH);
  }
  else
  {
    digitalWrite(M1F, LOW);
    digitalWrite(M1R, LOW);
    lcd.clear();
    lcd.setCursor(0, 1);
    lcd.print("Stop...");
  }
}

BLYNK_WRITE(V3)
{
  int sliderValue = param.asInt();
  analogWrite(M1PWM, sliderValue);
  pinValue1 = sliderValue;
}

BLYNK_WRITE(V4)
{
  int buttonState = param.asInt();
  if (buttonState == HIGH)
  {
    if (pinValue1 < 255 - increment)
    {
      pinValue1 += increment;
    }
    else
    {
      pinValue1 = 255;
    }
    analogWrite(M1PWM, pinValue1);
    Blynk.virtualWrite(V3, pinValue1);
  }
}

BLYNK_WRITE(V5)
{
  int buttonState = param.asInt();
  if (buttonState == HIGH)
  {
    if (pinValue1 > increment)
    {
      pinValue1 -= increment;
    }
    else
    {
      pinValue1 = 0;
    }
    analogWrite(M1PWM, pinValue1);
    Blynk.virtualWrite(V3, pinValue1);
  }
}

void setup()
{
  lcd.init();
  lcd.backlight();
  lcd.print("Cap treo nhom 2");
  pinMode(M1PWM, OUTPUT);
  pinMode(M1F, OUTPUT);
  pinMode(M1R, OUTPUT);
  digitalWrite(M1F, LOW);
  digitalWrite(M1R, LOW);
  
  Serial.begin(9600);
  Blynk.begin(auth, ssid, pass);
}

void loop()
{
  Blynk.run();
}

