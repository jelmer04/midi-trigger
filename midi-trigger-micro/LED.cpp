#include <arduino.h>

class LED {
  byte pin;
  int duration;
  unsigned long time;
  byte dark, light, flashlevel;
  int period, fade, crossover;
  
  public:
    LED (byte p, int d, byte f, int per, byte dk, byte lt) {
      pinMode(p, OUTPUT);
      pin = p;
      duration = d;
      flashlevel = f;
      
      period = per;
      dark = dk;
      light = lt;
      
      fade = period/(light-dark);
      crossover = period/fade;
    }
    
    void flash () {
      analogWrite(pin, flashlevel);
      time =  millis() + duration;
    }
    
    void update () {
      unsigned long m = millis();
      if (m > time) {
        byte level = m%(period*2)/fade;
        if (level > crossover) level = crossover * 2 - level;
        level += dark;
        
        analogWrite(pin, level);
      }
    }
};
