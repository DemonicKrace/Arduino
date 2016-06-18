//Lab 11 - 計時計數器
//MSTimer2，show on LCD to implement a clock
#include <MsTimer2.h>
// 引用 LiquidCrystal Library
#include <LiquidCrystal.h>

const int INTERVAL = 1000; //ms 
 
// 建立 LiquidCrystal 的變數 lcd
//                 LCD 接腳:  rs, enable, d4, d5, d6, d7 
//      對應到 Arduino 接腳:  12,     11,  5,  4,  3,  2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

int h = 0;
int m = 0;
int s = 0;

void counter( ) {
  
  if(!(h==0&&m==0&&s==0)){
    s--;
    if(s<0){
      s = 59;
      m--;
    }

    if(m<0){
      m = 59;
      h--;
    }
    
    Serial.print(h);
    Serial.print(":");
    Serial.print(m);
    Serial.print(":");
    Serial.println(s);

    lcd.print(h);
    lcd.print(":");
    lcd.print(m);
    lcd.print(":");
    lcd.print(s);

  }else{
    digitalWrite(13, HIGH);

    Serial.println("time is up!");
    
    lcd.print("time is up!");
  }
  lcd.setCursor(0, 1);
}
 
void setup() {

  Serial.begin(9600);

  
  // 設定 LCD 的行列數目 (2 x 16)
  lcd.begin(16, 2);

  lcd.setCursor(0, 1);
  pinMode(13, OUTPUT);
  MsTimer2::set(INTERVAL, counter); // INTERVAL ms 
}
 
void loop() {
 
//  // 列印 Arduino 重開之後經過的秒數
//  lcd.print(millis()/1000);
  if(Serial.available()){
    digitalWrite(13, LOW);
    h = Serial.parseInt();
    m = Serial.parseInt();
    s = Serial.parseInt();
    MsTimer2::start( );
  }
}
