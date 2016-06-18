//Lab08-I2C通訊
// master_sender.ino
// Refer to the "slave_receiver" example for use with this
#include <Wire.h>

// 引用 LiquidCrystal Library
#include <LiquidCrystal.h>

// 建立 LiquidCrystal 的變數 lcd
//                 LCD 接腳:  rs, enable, d4, d5, d6, d7 
//      對應到 Arduino 接腳:  12,     11,  5,  4,  3,  2
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
 

const int SLAVE_ADDRESS = 1;
const int MASTER_ADDRESS = 2;

char incomingByte = 0;

void setup() {  
  Wire.begin(MASTER_ADDRESS);         // join I2C bus as a Master
  Wire.onReceive(receiveEvent);
  
  Serial.begin(9600);
  Serial.println("Type something to send:");


  //LCD
  
  // 設定 LCD 的行列數目 (2 x 16)
  lcd.begin(16, 2);

 
  // 列印 "Hello World" 訊息到 LCD 上
//  lcd.print("03050485");

  // 將游標設到 column 0, line 1
  // (注意: line 1 是第二行(row)，因為是從 0 開始數起):
 // lcd.setCursor(0, 1);

//  lcd.print("Hana Sun");

}

void loop() {
  //  // 列印 Arduino 重開之後經過的秒數
//  lcd.print(millis()/1000);
  /*
  while(Serial.available()){
    lcd.write(Serial.read());
  }
  */
}

void serialEvent()
{
  // read one byte from serial port
  incomingByte = Serial.read();

  // send the received data to slave
  Wire.beginTransmission(SLAVE_ADDRESS);
  Wire.write(incomingByte);
  Wire.endTransmission();
}

void receiveEvent(int howMany)
{
  while (Wire.available()) 
  {
    // receive one byte from Master
    incomingByte = Wire.read();
    Serial.print(incomingByte);
    lcd.write(incomingByte);
//    lcd.setCursor(10, 1);
  }
}
