/*
A simple web server using an Arduino Wiznet Ethernet shield. 
For Arduino IDE V1.0 only. Previous IDE versions require mods to this code.

Original code created 18 Dec 2009
by David A. Mellis
modified 4 Sep 2010
by Tom Igoe
modified 18 Jan 2012
by Tim Dicus 
*/

#include <SPI.h>
#include <Ethernet.h>

// Enter a MAC address and IP address for your controller below.
// The IP address will be dependent on your local network:
byte mac[] = { 0x90, 0xA2, 0xDA, 0xF0, 0x52, 0xEA };// 60:f8:1d:ad:4d:2a //yun01 wifi 90:A2:DA:F0:52:EA  eth 90:A2:DA:F8:52:EA
//byte mac[] = { 0x90, 0xA2, 0xDA, 0xF8, 0x52, 0xEA };
/*
IPAddress ip(172.16.72.64);
IPAddress gateway(172.16.64.1);
IPAddress subnet(255,255,192,0);
IPAddress dns(172.16.64.1);
*/
// the dns server ip
IPAddress dnServer(192, 168, 0, 1);
// the router's gateway address:
IPAddress gateway(192, 168, 0, 1);
// the subnet:
IPAddress subnet(255, 255, 255, 0);
//the IP address is dependent on your network
IPAddress ip(192, 168, 0, 107);

// Initialize the Ethernet server library
// with the IP address and port you want to use 
// (port 80 is default for HTTP):
EthernetServer server(80);

void setup()
{
 Serial.begin(9600);

 // set SPI SS pins on w5100 and SD
 pinMode(10,OUTPUT);
 digitalWrite(10,HIGH);
 pinMode(4,OUTPUT);
 digitalWrite(4,HIGH);

 // start the SD interface here if you want.
 // Add the SD.h library above
 // SD.begin(4);

 // start the Ethernet connection and the server:
 Ethernet.begin(mac, ip, dns, gateway, subnet);
 // disable w5100 SPI so SD SPI can work with it
 digitalWrite(10,HIGH);
 delay(2000);

  //print out the IP address
  Serial.print("Local IP = ");
  Serial.println(Ethernet.localIP());
  
 server.begin();

 Serial.println("setup finished");
}

void loop()
{
 // listen for incoming clients
 EthernetClient client = server.available();
 if (client) {
   Serial.println("Client");
   // an http request ends with a blank line
   boolean currentLineIsBlank = true;
   while(client.connected()){
     while(client.available()){
       char c = client.read();
       // if you've gotten to the end of the line (received a newline
       // character) and the line is blank, the http request has ended,
       // so you can send a reply
       if (c == '\n' && currentLineIsBlank) {

         // Here is where the POST data is.  
         while(client.available()){
            Serial.write(client.read());
         }
         Serial.println();

         Serial.println("Sending response");
         // send a standard http response header
         client.println("HTTP/1.0 200 OK");
         client.println("Content-Type: text/html");
         client.println();
         client.println("<HTML><BODY>TEST OK!</BODY></HTML>");
         client.stop();
       }
       else if (c == '\n') {
         // you're starting a new line
         currentLineIsBlank = true;
       } 
       else if (c != '\r') {
         // you've gotten a character on the current line
         currentLineIsBlank = false;
       }
     }
   }
   Serial.println("Disconnected");
 }
}
