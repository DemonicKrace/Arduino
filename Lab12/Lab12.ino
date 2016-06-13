//Lab 12 – WiFi Module

#include <SoftwareSerial.h>
SoftwareSerial mySerial(4, 5); // Arduino RX:4, TX:5  
void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(115200);
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only

  
  mySerial.begin(115200);

  Serial.println("setup finish");
}
void loop() // run over and over
{
//  mySerial.write("AT\n");
  if (mySerial.available())
    Serial.write(mySerial.read());
    
  if (Serial.available())
    mySerial.write(Serial.read());

}
