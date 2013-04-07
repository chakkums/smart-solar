#include <SoftwareSerial.h>
char incoming_char=0; //Will hold the incoming character from the Serial Port.
SoftwareSerial cell(2,3); //Create a 'fake' serial port. Pin 2 is the Rx pin, pin 3 is the Tx pin.
void setup()
{
 //Initialize serial ports for communication.
 Serial.begin(9600);
 cell.begin(9600);
 Serial.println("Starting SM5100B Communication...");
}
void loop()
{
 //If a character comes in from the cellular module...
 if(cell.available() >0)
 {
 incoming_char=cell.read(); //Get the character from the cellular serial port.
 Serial.print(incoming_char); //Print the incoming character to the terminal.
 }
 //If a character is coming from the terminal to the Arduino...
 if(Serial.available() >0)
 {
 incoming_char=Serial.read(); //Get the character coming from the terminal
 cell.print(incoming_char); //Send the character to the cellular module.
 }
}
