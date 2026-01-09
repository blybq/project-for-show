#include "../driver/leds.driver.c"
#include "../util/minisys.util.c"

// Running light program: The LED lights are lit from both sides to the middle one by one, and then extinguished from the middle to both sides one by one
int main(void) {
  int pattern;
  int delay_count;
  int i;
  
  while (1) {
    // Light from both sides to the middle one by one
    pattern = 0x80000001; // The leftmost and rightmost LEDs each have one LED
    i = 0;
    while (i < 12) {
      light_leds(pattern);
      delay_count = 250000; // Approximately 0.5 second delay
      while (delay_count > 0) {
        delay_count = delay_count - 1;
      }
      // Expand to the middle
      pattern = pattern | (pattern * 2) | (pattern / 2);
      i = i + 1;
    }
    
    // Extinguish from the middle to both sides one by one
    pattern = 0x00FFF000; // The middle 12 LEDs
    i = 0;
    while (i < 12) {
      light_leds(pattern);
      delay_count = 250000; // Approximately 0.5 second delay
      while (delay_count > 0) {
        delay_count = delay_count - 1;
      }
      // Contract to both sides
      pattern = (pattern / 2) & 0x7FFF8000;
      i = i + 1;
    }
  }
  
  return 0;
}

