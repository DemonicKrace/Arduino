#include <SoftwareSerial.h>   //Software Serial Port
#define RxD 2
#define TxD 3
 
#define DEBUG_ENABLED  1
 
SoftwareSerial BLE(RxD,TxD);
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(RxD, INPUT);
  pinMode(TxD, OUTPUT);
  setupBleConnection();
 
} 
 
void loop() 
{ 
  char recvChar;
  while(1){
    if(BLE.available()){//check if there's any data sent from the remote BLE shield
      recvChar = BLE.read();
      Serial.print(recvChar);
    }
    if(Serial.available()){//check if there's any data sent from the local serial terminal, you can add the other applications here
      recvChar  = Serial.read();
      BLE.print(recvChar);
    }
  }
} 
 
void setupBleConnection()
{
  BLE.begin(9600); //Set BLE BaudRate to default baud rate 9600
  BLE.print("AT+CLEAR"); //clear all previous setting
  BLE.print("AT+ROLE1"); //set the bluetooth name as a master
  BLE.print("AT+SAVE1");  //don't save the connect information
}
