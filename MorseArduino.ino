#include "Morse.h"

// the standard dit duration is 300 milliseconds
#define MORSE_DEFAULT_DIT_DURATION 300
#define DEBUG true

// int morseOutputPin = LED_BUILTIN; 
int morseOutputPin = 9; 

// Initialize the morse object
// when DEBUG is true, the morse codes will be reflected in the serial console

Morse morse(morseOutputPin,       // the pin to use
            MORSE_SOUND,          // use either MORSE_LIGHT or MORSE_SOUND 
            MORSE_DEFAULT_DIT_DURATION,   
            DEBUG);

String message = "hello world 2022."; 
String morse_encoded_string = morse.encode(message); 
            

void setup()
{
  Serial.begin(9600); 
  Serial.println("Message:");
  Serial.println(message);
  Serial.println("Encoded Message:");
  Serial.println(morse_encoded_string);


  //  morse_encoded_string = "----- .---- ..--- ...-- .-.-.- ..--- ----- ..--- ..--- -....- .---- -----  -....- ..--- -.... .-.-.-"; 
  String decoded_string= morse.decode(morse_encoded_string); 
  Serial.print("decoded_string: ");
  Serial.println(decoded_string);
}

void loop()
{

  morse.dit(); morse.dit(); morse.dit();morse.space();
  morse.dah(); morse.dah(); morse.dah();morse.space();
  morse.dit(); morse.dit(); morse.dit();
  delay(3000);
  morse.dit_simple(); morse.dit_simple(); morse.dit_simple();morse.space();
  morse.dah_simple(); morse.dah_simple(); morse.dah_simple();morse.space();
  morse.dit_simple(); morse.dit_simple(); morse.dit_simple();
  delay(3000);

  morse.sendText("s o s "); 
  morse.sendMorse(morse_encoded_string); 

}
