/*
  Morse.h - Library for morse code on arduino.
*/
#ifndef Morse_h
#define Morse_h

#define MORSE_LIGHT 0
#define MORSE_SOUND 1
#define SIGNAL_ON 1
#define SIGNAL_OFF 0

#define MORSE_TONE_FREQUENCY 440 // 1000

#include "Arduino.h"

class Morse
{
  public:
    Morse(int pin=LED_BUILTIN, int output_type=MORSE_LIGHT, int dit_duration=300, bool debug=true, bool ignore_unknown=true, int console_baud_rate=9600);

    // accepts an english string, converts to a morse string, and sends a morse message
    void sendText(String msg ); 
    
    // accepts a morse string of dots and dashes, send the actual message to the arduino pin
    void sendMorse(String morsecode); 

    // accepts an english string, converts to a morse string
    String encode(String msg ); 
    
    // accepts an english string, converts to a morse string
    String decode(String msg ); 
    
    // low level function. sends a morse dot (dit)
    // the "dit_simple" function manipulates the arduino pins directly. 
    // the dit function uses "signal_out" as an additional abstraction   
    void dit();
    void dit_simple();

    // low level function. sends a morse dash (dah)
    // the "dah_simple" function manipulates the arduino pins directly. 
    // the dah function uses "signal_out" as an additional abstraction   
    void dah();
    void dah_simple();

    // low level function. sends an extra space between letters
    void space();


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
    int _output_type;
    void signal_out(int status, int output_type=MORSE_LIGHT); 
    char mfind(String morse_letter) ; 

};

#endif
