#include "Morse.h"
#define MORSE_DIT_DURATION 300
#define DEBUG true

// Initialize the morse object
// when DEBUG is true, the morse codes will be reflected in the serial console
Morse morse(LED_BUILTIN,MORSE_DIT_DURATION,DEBUG);

void setup()
{
  if (DEBUG) {
    Serial.begin(9600); 
  }
}

void loop()
{
/*
  morse.dit(); morse.dit(); morse.dit();
  morse.dah(); morse.dah(); morse.dah();
  morse.dit(); morse.dit(); morse.dit();
  delay(3000);
*/ 
  // if looping message, terminate the message with white space
  String message = "hello world 2022 "; 
  morse.sendMessage(message); 
}
