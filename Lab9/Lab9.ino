// HCSR04Ultrasonic/examples/UltrasonicDemo/UltrasonicDemo.pde
#include <Ultrasonic.h>


// 引用 LiquidCrystal Library
#include <LiquidCrystal.h>
 
// 建立 LiquidCrystal 的變數 lcd
//                 LCD 接腳:  rs, enable, d4, d5, d6, d7 
//      對應到 Arduino 接腳:  12,     11,  5,  4,  3,  2
LiquidCrystal lcd(12, 11, 5, 4, 3, 6);


#define TRIGGER_PIN  8
#define ECHO_PIN     9

volatile int buttonState; 
const int interruptNumber = 0;   

const int buttonPin = 2;

Ultrasonic ultrasonic(TRIGGER_PIN, ECHO_PIN);

void setup()
{
  Serial.begin(9600);
  pinMode(buttonPin, INPUT);
  
  // 把外部中斷(interrupt 0)連接到 buttonStateChanged() 函式
  // CHANGE 是指當 pin 狀態改變時就觸發中斷，不管是從 HIGH 到 LOW 或從 LOW 到 HIGH
  attachInterrupt(interruptNumber, buttonStateChanged, CHANGE);


  //
  
  
  // 設定 LCD 的行列數目 (2 x 16)
  lcd.begin(16, 2);


 
  // 列印 "Hello World" 訊息到 LCD 上
  lcd.print("03050485");

  // 將游標設到 column 0, line 1
  // (注意: line 1 是第二行(row)，因為是從 0 開始數起):
  lcd.setCursor(0, 1);

//  lcd.print("Hana Sun");
  
}

void loop()
{

  lcd.scrollDisplayLeft();
  delay(1000);


}

// Interrupt 0 的中斷處理函式
// 讀取 buttonPin 的狀態，並反應到 ledPin 上
void buttonStateChanged() {
  buttonState = digitalRead(buttonPin);
//  buttonState = !buttonState;
  Serial.print("buttonState = ");
  Serial.println(buttonState);


  float cmMsec, inMsec;
  long microsec = ultrasonic.timing();

  cmMsec = ultrasonic.convert(microsec, Ultrasonic::CM); // 計算距離，單位: 公分
  inMsec = ultrasonic.convert(microsec, Ultrasonic::IN); // 計算距離，單位: 英吋

  lcd.print("MS:");
  lcd.print(microsec);
  lcd.print(",CM:");
  lcd.print(cmMsec);
  lcd.print(",IN:");
  lcd.println(inMsec);
  
  lcd.setCursor(0, 1);
}

