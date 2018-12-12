/*
  
  Emic 2 Text-to-Speech Module: Basic Demonstration       
                                                         
  Author: Joe Grand [www.grandideastudio.com]             
  Contact: support@parallax.com                            
  
  Program Description:
  
  This program provides a simple demonstration of the Emic 2 Text-to-Speech
  Module. Please refer to the product manual for full details of system 
  functionality and capabilities.

  Revisions:
  
  1.0 (February 13, 2012): Initial release
  1.1 (April 29, 2014): Changed rxPin/txPin to use pins 10/11, respectively, for widest support across the Arduino family (http://arduino.cc/en/Reference/SoftwareSerial)
    
*/

// include the SoftwareSerial library so we can use it to talk to the Emic 2 module
#include <SoftwareSerial.h>

#define rxPin   2  // Serial input (connects to Emic 2's SOUT pin)
#define txPin  3  // Serial output (connects to Emic 2's SIN pin)
#define ledPin  13  // Most Arduino boards have an on-board LED on this pin

// set up a new serial port
SoftwareSerial emicSerial =  SoftwareSerial(rxPin, txPin);

void setup()  // Set up code called once on start-up
{
  // define pin modes
  pinMode(ledPin, OUTPUT);
  pinMode(rxPin, INPUT);
  pinMode(txPin, OUTPUT);
  
  // set the data rate for the SoftwareSerial port
  emicSerial.begin(9600);

  digitalWrite(ledPin, LOW);  // turn LED off
  
  /*
    When the Emic 2 powers on, it takes about 3 seconds for it to successfully
    initialize. It then sends a ":" character to indicate it's ready to accept
    commands. If the Emic 2 is already initialized, a CR will also cause it
    to send a ":"
  */
  emicSerial.print('\n');             // Send a CR in case the system is already up
  while (emicSerial.read() != ':');   // When the Emic 2 has initialized and is ready, it will send a single ':' character, so wait here until we receive it
  delay(10);                          // Short delay
  emicSerial.flush();                 // Flush the receive buffer
}

void loop()  // Main code, to run repeatedly
{
  emicSerial.print("D0\n");
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);

emicSerial.print("SI can even sing a song.\n");
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);

  
  // Sing a song
  emicSerial.print("D1\n");
  digitalWrite(ledPin, HIGH);         // Turn on LED while Emic is outputting audio
  while (emicSerial.read() != ':');   // Wait here until the Emic 2 responds with a ":" indicating it's ready to accept the next command
  digitalWrite(ledPin, LOW);

  while(1)      // Demonstration complete!
  {
    delay(500);
    digitalWrite(ledPin, HIGH);
    delay(500);              
    digitalWrite(ledPin, LOW);
  }
}



