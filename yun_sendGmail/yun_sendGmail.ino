#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h"


// We limit this so you won't use all of your Temboo calls while testing
int maxCalls = 1;

// The number of times this Choreo has been run so far in this sketch
int calls = 0;

int outputPin = 13;

// your Gmail username, formatted as a complete email address, eg "bob.smith@gmail.com"
const String GMAIL_USER_NAME = "***";
 
// your Gmail password
const String GMAIL_PASSWORD = "***";
 
// the email address you want to send the email to, eg "jane.doe@temboo.com"
const String TO_EMAIL_ADDRESS = "***";

void setup() {
  Serial.begin(9600);
  
  // For debugging, wait until the serial console is connected
  delay(4000);
  while(!Serial);
  Bridge.begin();
  
  // Initialize pins
  pinMode(outputPin, OUTPUT);

  Serial.println("Setup complete.\n");
}

void loop() {
  if (calls < maxCalls) {
    Serial.println("Calling SendEmail Choreo...");
    runSendEmail();
    calls++;
  } else {
    Serial.println("Skipping to save Temboo calls. Adjust maxCalls as required.");
  }
  delay(30000);
}

void runSendEmail() {
  TembooChoreo SendEmailChoreo;

  // Invoke the Temboo client
  SendEmailChoreo.begin();

  // Set Temboo account credentials
  SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
  SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
  SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);

  // Set profile to use for execution
//  SendEmailChoreo.setProfile("SendGmailSample");

  // Identify the Choreo to run
  SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");


  // set the required choreo inputs
  // see https://www.temboo.com/library/Library/Google/Gmail/SendEmail/ 
  // for complete details about the inputs for this Choreo
  
  // the first input is your Gmail email address
  SendEmailChoreo.addInput("Username", GMAIL_USER_NAME);
  // next is your Gmail password.
  SendEmailChoreo.addInput("Password", GMAIL_PASSWORD);
  // who to send the email to
  SendEmailChoreo.addInput("ToAddress", TO_EMAIL_ADDRESS);
  // then a subject line
  SendEmailChoreo.addInput("Subject", "Send Gmail Test");
  
  // next comes the message body, the main content of the email   
  SendEmailChoreo.addInput("MessageBody", "Send Gmail Test");
 
  // Run the Choreo
  unsigned int returnCode = SendEmailChoreo.run();

  // a return code of zero (0) means everything worked
  if (returnCode == 0) {
      Serial.println("Success! Email sent!");
      digitalWrite(outputPin,HIGH);
  } else {
    // a non-zero return code means there was an error
    // read and print the error message
    while (SendEmailChoreo.available()) {
      char c = SendEmailChoreo.read();
      Serial.print(c);
    }
  } 

  SendEmailChoreo.close();
}
