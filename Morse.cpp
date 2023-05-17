/*
  Morse.cpp - Library for morse code on arduino.
  Created by Shalom Carmel, 2022
  Copyright MIT
*/

#include "Arduino.h"
#include "Morse.h"
#include "morse_codes.h"

Morse::Morse(int pin, int output_type, int dit_duration, bool debug, bool ignore_unknown, int console_baud_rate)
{
  pinMode(pin, OUTPUT);
  _morse_pin = pin;
  _dit_duration = dit_duration ; 
  _debug = debug;
  _ignore_unknown = ignore_unknown; 
  _console_baud_rate = console_baud_rate; 
  _dits_in_dah = 3; 
  _dits_between_letters = 3; 
  _dits_between_words = 7; 
  _dah_duration = _dits_in_dah * _dit_duration; 
  _extra_space_between_letters = (_dits_between_letters -1) * _dit_duration; 
  _extra_space_between_words = (_dits_between_words - _dits_between_letters -1) * _dit_duration; 
  _output_type = output_type; 
	if (_debug) {
		Serial.begin(_console_baud_rate); 
  }

  
}

void Morse::signal_out(int status, int output_type)
/* signal_out 
 *  Function: interface to the actual arduino signalling capabilities. 
 *  Parameters: int status SIGNAL_ON / SIGNAL_OFF 
 *              int output_type MORSE_LIGHT / MORSE_SOUND ; default=MORSE_SOUND
 */
{
  // check what is the actual signal channel and act accordingly
  if (status==SIGNAL_ON && output_type==MORSE_LIGHT) {
      digitalWrite(_morse_pin, HIGH);
  } else if (status==SIGNAL_OFF && output_type==MORSE_LIGHT) {
      digitalWrite(_morse_pin, LOW);
  } else if (status==SIGNAL_ON && output_type==MORSE_SOUND) {
      tone(_morse_pin, MORSE_TONE_FREQUENCY);
  } else if (status==SIGNAL_OFF && output_type==MORSE_SOUND) {
      noTone(_morse_pin);
  } else if (status==SIGNAL_ON ) {
      digitalWrite(_morse_pin, HIGH);
  } else if (status==SIGNAL_OFF ) {
      digitalWrite(_morse_pin, LOW);
  }
}



void Morse::dit()
{
  signal_out(SIGNAL_ON);
  delay(_dit_duration);
  signal_out(SIGNAL_OFF);
  delay(_dit_duration);  
}

void Morse::dah()
{
  signal_out(SIGNAL_ON);
  delay(_dah_duration);
  signal_out(SIGNAL_OFF);
  delay(_dit_duration);
}

void Morse::dit_simple()
{
  digitalWrite(_morse_pin, HIGH);
  delay(_dit_duration);
  digitalWrite(_morse_pin, LOW);
  delay(_dit_duration);  
}

void Morse::dah_simple()
{
  digitalWrite(_morse_pin, HIGH);
  delay(_dah_duration);
  digitalWrite(_morse_pin, LOW);
  delay(_dit_duration);
}

void Morse::space()
{
  delay(_extra_space_between_letters);
}



void Morse::sendMorse(String morsecode) {
  // low level function, outputs any combination of dots and dashes
  int c;
  char ascii;
  for(c=0;c<morsecode.length();c++){
    switch (morsecode.charAt(c)) {
      case '.':  // ascii 46
        dit(); 
        break;
      case '-':  // ascii 45
        dah(); 
        break;
      case ' ':  // space ascii 32 
        if (_debug) {
          Serial.print("\t"); 
        }
        delay(_extra_space_between_words);
        break;
      default:
        // default is optional
        break;
    }
  }
  space();
}

void Morse::sendText(String msg ) {  
  // accepts an english string, sends a morse message
    String morsecode = encode(msg); 
    if (_debug) {
      Serial.println(msg); 
      Serial.println(morsecode); 
    }
    sendMorse(morsecode);
}

String Morse::encode(String msg ) {  
  // accepts an english string, returns a morse message string
  // morsecodes_array is a global variable, defined in morse_codes.h
   char unknown[7]; 
   if (_ignore_unknown) {
      char unknown[] = " " ;
   }
   else {
      // use question mark
      char unknown[]="..--.." ;
   }
  int numOfMorseLetters = (sizeof(morsecodes_array)/sizeof(char *));  //array size
  String morsecode;
  String encoded_string = "";
  msg.toUpperCase(); 
  for (int c=0;c<msg.length();c++){
    int ascii = (int) msg.charAt(c);
    int morseIndex = ascii- 32; 
    if (morseIndex <0 || morseIndex >= numOfMorseLetters) {
      morsecode=unknown; // unsupported letter
    } 
    else{
      morsecode=morsecodes_array[morseIndex]; 
    }
    encoded_string.concat(morsecode); 
    encoded_string.concat(" "); 
    if (_debug) {
  		Serial.print(msg.charAt(c));
  		Serial.print("\t");
  		Serial.print(ascii);
  		Serial.print("\t");
  		Serial.print(morsecode);
  		Serial.print("\t");
      Serial.println(); 
    }
  }
return(encoded_string);
}


char Morse::mfind(String morse_letter) {
  int numOfMorseLetters = (sizeof(morsecodes_array)/sizeof(char *));  //array size
  String decoded_string = "";
  // loop on morsecodes_array to find the proper english letter. 
  // if not found return '?'
  for (int c=0; c<numOfMorseLetters; c++){
    if (morse_letter == morsecodes_array[c]) {
      char english_letter = c + 32; 
      return english_letter; 
      break;
    }
  }
  return '?'; 
}
String Morse::decode(String msg ) {  
  // accepts a morse message string, returns a english string
  // morsecodes_array is a global variable, defined in morse_codes.h
  String morseletter = ""; 
  String decoded_letter; 
  String decoded_string = ""; 
  for (int c=0;c<msg.length();c++){
    // treat . and - as valid morse code components, everything else as a delimiter. 
    bool is_valid_morse_code = (msg.charAt(c)=='.' || msg.charAt(c)=='-'); 
      if (is_valid_morse_code) {
        morseletter.concat(msg.charAt(c));
      } else { // probably white space
        if (morseletter.length() > 0) {
          decoded_letter = mfind(morseletter); 
          decoded_string.concat(decoded_letter); 
          morseletter=""; 
        }
    }
  }
  if (morseletter.length() > 0) {
    decoded_letter = mfind(morseletter); 
    decoded_string.concat(decoded_letter); 
    morseletter=""; 
  }
  return decoded_string; 
}
