#include <SoftwareSerial.h>

SoftwareSerial mySerial(0, 1); // RX, TX

void setup()
{
  // Open serial communications and wait for port to open:
  Serial.begin(9600);

  // wait for serial port to connect. Needed for Leonardo only
  while (!Serial);
  

  // set the data rate for the SoftwareSerial port
  mySerial.begin(9600);
  delay(3500);
  
//  Serial.println("AT");
  mySerial.print("AT");

 // Serial.println("AT+RESET");
//  mySerial.print("AT+RESET");
}

void loop() // run over and over
{
  if (mySerial.available())
    Serial.write(mySerial.read());
    
  if (Serial.available())
    mySerial.write(Serial.read());
}
