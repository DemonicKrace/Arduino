//Lab08-I2C通訊
// slave_receiver.ino
// Refer to the "master_sender" example for use with this
#include <Wire.h>

#include <string.h>
#include "DHT.h"

#define dht_dpin A0 //定義訊號要從Pin A0 進來

dht DHT;

const int SLAVE_ADDRESS = 1;
const int MASTER_ADDRESS = 2;

char incomingByte = 0;

char test[20];

void setup() {  
  Wire.begin(SLAVE_ADDRESS);    // join I2C bus as a slave with address 1
  Wire.onReceive(receiveEvent); // register event
  
  Serial.begin(9600);
  Serial.println("Received data:");

}

void loop() {
    postDataToMaster();
    delay(1000); //每1000ms更新一次
}

void receiveEvent(int howMany)
{
  while (Wire.available()) 
  {
    // receive one byte from Master
    incomingByte = Wire.read();
    Serial.print(incomingByte);
  }
}


void serialEvent()
{
  // send the received data to slave
  Wire.beginTransmission(MASTER_ADDRESS);
  Wire.write(Serial.read());
  Wire.endTransmission();
}

void postDataToMaster(){
  //去library裡面找DHT.read11
  DHT.read11(dht_dpin);
  
  Wire.beginTransmission(MASTER_ADDRESS);

  float h = DHT.humidity;
  float t = DHT.temperature;
  Wire.write("H=");
  Wire.write(floatToString(test, DHT.humidity, 2, 6));

  Wire.write("%,T=");
  Wire.write(floatToString(test, DHT.temperature, 2, 6));
  Wire.write("C\n");

  Wire.endTransmission();
}

char * floatToString(char * outstr, double val, byte precision, byte widthp){
 char temp[16];
 byte i;

 // compute the rounding factor and fractional multiplier
 double roundingFactor = 0.5;
 unsigned long mult = 1;
 for (i = 0; i < precision; i++)
 {
   roundingFactor /= 10.0;
   mult *= 10;
 }
 
 temp[0]='\0';
 outstr[0]='\0';

 if(val < 0.0){
   strcpy(outstr,"-\0");
   val = -val;
 }

 val += roundingFactor;

 strcat(outstr, itoa(int(val),temp,10));  //prints the int part
 if( precision > 0) {
   strcat(outstr, ".\0"); // print the decimal point
   unsigned long frac;
   unsigned long mult = 1;
   byte padding = precision -1;
   while(precision--)
     mult *=10;

   if(val >= 0)
     frac = (val - int(val)) * mult;
   else
     frac = (int(val)- val ) * mult;
   unsigned long frac1 = frac;

   while(frac1 /= 10)
     padding--;

   while(padding--)
     strcat(outstr,"0\0");

   strcat(outstr,itoa(frac,temp,10));
 }

 // generate space padding 
 if ((widthp != 0)&&(widthp >= strlen(outstr))){
   byte J=0;
   J = widthp - strlen(outstr);
   
   for (i=0; i< J; i++) {
     temp[i] = ' ';
   }

   temp[i++] = '\0';
   strcat(temp,outstr);
   strcpy(outstr,temp);
 }
 
 return outstr;
}

