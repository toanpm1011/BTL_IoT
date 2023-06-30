/*Kết nối     HC-SR04              ARDUINO          LCD1602-I2C
 *             Trig                  D8
 *             Echo                  D7
 *                                   D20               SDA
 *                                   D21               SCL
 */
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2); 
const int trig = 8; // chân trig của HC-SR04
const int echo = 7;  // chân echo của HC-SR04
//...............................................
void setup()
{
  Serial.begin(9600); // giao tiếp Serial với baudrate 9600
  lcd.init(); 
  lcd.backlight();
  lcd.setCursor(0, 0);
  lcd.print("Distance:");
  lcd.setCursor(13, 0);
  lcd.print(" cm");
  pinMode(trig, OUTPUT); // chân trig sẽ phát tín hiệu
  pinMode(echo, INPUT); // chân echo sẽ nhận tín hiệu
}
//...............................................
void loop()
{
  unsigned long duration;   // biến đo thời gian
  int distance;    // biến lưu khoảng cách

  /* Phát xung từ chân trig */
  digitalWrite(trig, 0);  // tắt chân trig
  delayMicroseconds(2);   // xung có độ dài 2 microSeconds
  digitalWrite(trig, 1); // phát xung từ chân trig		
  delayMicroseconds(5);  // xung có độ dài 5 microSeconds
  digitalWrite(trig, 0);  // tắt chân trig

  /* Tính toán thời gian */
  duration = pulseIn(echo, HIGH);	// Đo độ rộng xung HIGH ở chân echo. 
  distance = int(duration / 2 / 29.412);  // Tính khoảng cách đến vật. 29,412 microSeconds/cm = (10^6 / (340*100))

/* In kết quả ra Serial Monitor */
  lcd.setCursor(10, 0);
  lcd.print(distance);
  if (distance < 10) {
    lcd.setCursor(11, 0);
    lcd.print("  ");
  }
  else if (distance < 100) {
    lcd.setCursor(12, 0);
    lcd.print(' ');
  }
  delay(200);
}
