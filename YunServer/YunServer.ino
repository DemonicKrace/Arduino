#include <Bridge.h>
#include <YunServer.h>
#include <YunClient.h> 
 
YunServer server;
 
void setup() {
  Serial.begin(19200);
  Bridge.begin(); // 啟動Bridge
  while(!Serial);
//  server.listenOnLocalhost(); // 設定讓伺服器聆聽本地端IP位址的連線
  server.begin(); // 開始
  Serial.println("Server was started...");
}
 
void loop() {
  YunClient client = server.accept(); // 有連線進來了
  if(client){
    process(client); // 開始處理，分析API
    client.stop();
  }
  delay(50);
}

void process(YunClient client){
//  Serial.println(client.readString());
  
  String command = client.readStringUntil('/');
  if(command == "digital"){ // 數位輸入輸出
    digitalCommand(client);
  }
  else if(command == "analog"){ // 類比輸入輸出
    analogCommand(client);
  }
  else if(command == "mode"){ // 設定腳位模式
    modeCommand(client);
  }
}
void digitalCommand(YunClient client){
  Serial.println("digitalCommand called");
  int pin, value;
  pin = client.parseInt();
  if(client.read() == '/'){ // 數位輸出，設定為1（高電位）或0（低電位）
    value = client.parseInt();
    digitalWrite(pin, value);
    client.print("Pin ");
    client.print(pin);
    client.print(" set to ");
    client.println(value);
  }
  else{ // 數位輸入，讀取該腳位的值
    value = digitalRead(pin);
    client.print("Pin ");
    client.print(pin);
    client.print(" reads ");
    client.println(value);
  }
}
void analogCommand(YunClient client){
  Serial.println("analogCommand called");
  int pin, value;
  pin = client.parseInt();
  if(client.read() == '/'){ // 類比輸出，設定PWM值為0~255
    value = client.parseInt();
    analogWrite(pin, value);
    client.print("Pin ");
    client.print(pin);
    client.print(" set to analog ");
    client.println(value);
  }
  else{ // 類比輸入，讀取該類比腳位的值
    value = analogRead(pin);
    client.print("Pin ");
    client.print(pin);
    client.print(" reads analog ");
    client.println(value);
  }
}
void modeCommand(YunClient client){
  Serial.println("modeCommand called");
//  Serial.println(client.readString());
  int pin;
  pin = client.parseInt();
  if (client.read() != '/') {
    client.println("error command");
    return;
  }
  String mode = client.readStringUntil('\r');
  if(mode == "input"){ // 設為輸入模式
    pinMode(pin, INPUT);
    client.print("Pin ");
    client.print(pin);
    client.print(" configured as INPUT.");
    return;
  }
  else if(mode == "output"){ // 設為輸出模式
    pinMode(pin, OUTPUT);
    client.print("Pin ");
    client.print(pin);
    client.print(" configured as OUTPUT.");
    return;
  }
  client.print("error: invalid mode ");
  client.print(mode);
}
