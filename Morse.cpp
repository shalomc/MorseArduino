/*
  Morse.cpp - Library for morse code on arduino.
  Created by Shalom Carmel, 2022-05-06
  Copyright GNU
*/

#include "Arduino.h"
#include "Morse.h"


Morse::Morse(int pin=LED_BUILTIN, int output_type=MORSE_LIGHT, int dit_duration=300, bool debug=false, bool ignore_unknown=true, int console_baud_rate=9600)
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

void Morse::signal()
{
  // check what is the actual signal channel and act accordingly
  switch (_output_type) {
    case MORSE_LIGHT:
      digitalWrite(_morse_pin, HIGH);
      delay(_dit_duration);
      digitalWrite(_morse_pin, LOW);
      delay(_dit_duration); 
      break;
    case MORSE_SOUND:
      tone(_morse_pin, MORSE_TONE_FREQUENCY, _dit_duration);
      noTone(_morse_pin);
      delay(_dit_duration); 
      break;
    default: // light
      digitalWrite(_morse_pin, HIGH);
      delay(_dit_duration);
      digitalWrite(_morse_pin, LOW);
      delay(_dit_duration); 
      break;

    } 
}

void Morse::dit()
{
  digitalWrite(_morse_pin, HIGH);
  delay(_dit_duration);
  digitalWrite(_morse_pin, LOW);
  delay(_dit_duration);  
}

void Morse::dah()
{
  digitalWrite(_morse_pin, HIGH);
  delay(_dah_duration);
  digitalWrite(_morse_pin, LOW);
  delay(_dit_duration);
}


void Morse::outputMorse(String morsecode) {
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
  delay(_extra_space_between_letters);
}

void Morse::sendMessage(String msg ) {  
  // accepts an english string, sends a morse message
   char unknown[7]; 
   if (_ignore_unknown) {
      char unknown[] = " " ;
   }
   else {
      // use question mark
      char unknown[]="..--.." ;     
   }
  const char *morsecodes[] = { 
    " ", //  space 
    "-.-.--", //!
    ".-..-.", //"
    unknown, //#
    "...-..-", //$
    unknown, //%
    ".-...", //&
    ".----.", //'
    "-.--.", //(
    "-.--.-", //)
    unknown, //*
    ".-.-.", //+
    "--..--", //,
    "-....-", //-
    ".-.-.-", //.
    "-..-.",  ///
    "-----",  //0
    ".----",  //1
    "..---",  //2
    "...--",  //3
    "....-",  //4
    ".....",  //5
    "-....",  //6
    "--...",  //7
    "---..",  //8
    "----.",  //9
    "---...", //:
    "-.-.-.", //;
    unknown,  //<
    "-...-:",  //=
    unknown,  //>
    "..--..", //?
    ".--.-.", //@
    ".-",   //A
    "-...", //B
    "-.-.", //C
    "-..",  //D
    ".",    //E
    "..-.", //F
    "--.",  //G
    "....", //H
    "..",   //I
    ".---", //J
    "-.-",  //K
    ".-..", //L
    "--",   //M
    "-.",   //N
    "---",  //O
    ".--.", //P
    "--.-", //Q
    ".-.",  //R
    "...",  //S
    "-",    //T
    "..-",  //U
    "...-", //V
    ".--",  //W
    "-..-", //X
    "-.--", //Y
    "--.." //Z
    };
  int numOfMorseLetters = (sizeof(morsecodes)/sizeof(char *));  //array size
  String morsecode;
  msg.toUpperCase(); 
  for (int c=0;c<msg.length();c++){
    int ascii = (int) msg.charAt(c);
    int morseIndex = ascii- (int)msg.charAt(0); 
    if (morseIndex <0 || morseIndex >= numOfMorseLetters) {
      morsecode=unknown; // unsupported letter
    } 
    else{
      morsecode=morsecodes[ascii- (int)msg.charAt(0)]; 
    }
    
    if (_debug) {
  		Serial.print(msg.charAt(c));
  		Serial.print("\t");
  		Serial.print(ascii);
  		Serial.print("\t");
  		Serial.print(morsecode);
  		Serial.print("\t");
      Serial.println(); 
    }
    outputMorse(morsecode);
  }

}
