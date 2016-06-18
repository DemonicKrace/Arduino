//Lab10-紅外線控制
/*
 * IRRemote 紅外線遙控教學
 *   範例 2.1v2: 發射紅外線訊號
 *     注意! 紅外線發射器(IR LED)必須接到 pin 3, 不能接其它腳位
 */
#include <IRremote.h>                    // 引用 IRRemote 函式庫

IRsend irsend;                           // 定義 IRsend 物件來發射紅外線訊號

const int irReceiverPin = 7;             // 紅外線接收器 OUTPUT 訊號接在 pin 2

IRrecv irrecv(irReceiverPin);            // 定義 IRrecv 物件來接收紅外線訊號
decode_results results;                  // 解碼結果將放在 decode_results 結構的 result 變數裏


const int irReceiver = 2;                // 紅外線接收器
const int irLed  = 3;                    // 紅外線發射器
const int ledPin = 13;                   // 紅外線指示燈
const unsigned int frequency = 38000;    // 發射頻率(單位: Hz)



void setup() {       
  Serial.begin(9600);                     // 開啟 Serial port, 通訊速率為 9600 bps

  irrecv.enableIRIn();                   // 啟動紅外線解碼     
      
  //pinMode(irReceiver, INPUT);           // 把 irReceiver 接腳設置為 INPUT
  //pinMode(irLed, OUTPUT);               // 把 irLed 接腳設置為 INPUT
  pinMode(ledPin, OUTPUT);              // 把 ledPin 設置為 OUTPUT
  
}

// 讓指示燈閃爍幾下 
void blinkLED() {
  for (int i=1; i<= 4; i++) {
    digitalWrite(ledPin, HIGH);          // 打開指示燈
    delay(100);
    digitalWrite(ledPin, LOW);           // 關掉指示燈
    delay(100);
  }  
}

void loop() {

  // 檢查 Serial Port 是否有資料
  // 有的話，Serial.read() 會回傳非 -1 的數值
  if (Serial.read() != -1) {    
    // 發射紅外線訊號
    irsend.sendNEC(0x4FB48B7, 32);   // 我電視 Power 鈕的紅外線編碼, 記得換成你的紅外線編碼 
  }
  
  if (irrecv.decode(&results)) {         // 解碼成功，收到一組紅外線訊號
    blinkLED();
    // 印到 Serial port  
    Serial.print("irCode: ");            
    Serial.print(results.value, HEX);    // 紅外線編碼
    Serial.print(",  bits: ");           
    Serial.println(results.bits);        // 紅外線編碼位元數
    irrecv.resume();                    // 繼續收下一組紅外線訊號        
  }  
}
