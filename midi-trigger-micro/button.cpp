#include <arduino.h>

class Button {
    byte pin;
    byte history;
  
  public:
    Button (byte p) {
      pinMode(p, INPUT_PULLUP);
      pin = p;
      history = 0;
    }
    
    Button ()
    {
    }
    
    void update() {
      history = history << 1;
      history |= digitalRead(pin);
    }
    
    byte pressed() {      
      if ((history & 0b11000111) == 0b11000000) { 
        history = 0b00000000;
        return 1;
      }
      return 0;
    }
    
    byte unpressed() {      
      if ((history & 0b11000111) == 0b000000111) { 
        history = 0b11111111;
        return 1;
      }
      return 0;
    }
    
};

#define MASK  0b00111111
#define NEXT  0b00000111
#define NEXT2 0b00111000
#define PREV  0b00110100
#define PREV2 0b00001011

class Knob {
    Button a;
    Button b;
    
  public:
    byte history;
  
  //public:
    Knob (byte pina, byte pinb) {
      a = Button(pina);
      b = Button(pinb);
      history = 0;
    }
  
    void update() {
      a.update();
      if (a.pressed()) {
        byte tmp = history & 0b00000010;
        history = history << 2;
        history |= 0b00000001;
        history |= tmp;
      }
      if (a.unpressed()) {
        byte tmp = history & 0b00000010;
        history = history << 2;
        history |= tmp;
      }
      
      b.update();
      if (b.pressed()) {
        byte tmp = history & 0b00000001;
        history = history << 2;
        history |= 0b00000010;
        history |= tmp;
      }
      if (b.unpressed()) {
        byte tmp = history & 0b00000001;
        history = history << 2;
        history |= tmp;
      }
    }
    
    byte next() {
      byte hist = history & MASK;
      byte pressed = 0;
      if (hist == NEXT || hist == NEXT2) {
        history = history & 3;
        return 1;
      }
      return 0;
    }
    
    byte prev() {
      byte hist = history & MASK;
      if (hist == PREV || hist == PREV2){
        history = history & 3;
        return 1;
      }
      return 0;
    }
    
};
