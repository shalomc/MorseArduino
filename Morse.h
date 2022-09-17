/*
  Morse.h - Library for morse code on arduino.
*/
#ifndef Morse_h
#define Morse_h

#include "Arduino.h"

class Morse
{
  public:
    Morse(int pin=LED_BUILTIN, int dit_duration=300, bool debug=false, bool ignore_unknown=true, int console_baud_rate=9600);

    // accepts an english string, converts to a morse string, and sends a morse message
    void sendMessage(String msg ); 
    
    // low level function. accepts a string of dots and dashes, outputs the corresponding morse code
    void outputMorse(String morsecode); 

    // low level function. sends a morse dot (dit)
    void dit();

    // low level function. sends a morse dash (dah)
    void dah();

	
  private:
    int _morse_pin; 
    int _dit_duration ; 
    bool _debug ;
    bool _ignore_unknown ; 
    int _console_baud_rate ; 
    int _dits_in_dah ; 
    int _dits_between_letters ; 
    int _dits_between_words ; 
    int _dah_duration ; 
    int _extra_space_between_letters ; 
    int _extra_space_between_words ; 

};

#endif
