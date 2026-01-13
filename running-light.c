#include "../driver/leds.driver.c"
#include "../util/minisys.util.c"

// Running light program: The LED lights are lit from both sides to the middle one by one, and then extinguished from the middle to both sides one by one
int main(void) {
  int pattern;
  int delay_count;
  int i;
  int mask;
  int j;
  
  while (1) {
    // Light from both sides to the middle one by one
    pattern = 0x00800001; // The leftmost and rightmost LEDs each have one LED
    i = 0;
    while (i < 12) {
      light_leds(pattern);
      delay_count = 100000; // Approximately 0.5 second delay
      while (delay_count > 0) {
        delay_count = delay_count - 1;
      }
      // Expand to the middle
      pattern = pattern | (pattern * 2) | (pattern / 2);
      i = i + 1;
    }
    
    // Extinguish from the middle two LEDs to both sides one by one
    // Start with all 24 LEDs on, then turn off from middle to both sides
    pattern = 0x00FFFFFF; // All 24 LEDs are on (high 8 bits are 0)
    i = 0;

    while (i < 12) {
      // Create mask for middle LEDs to turn off: start with middle two, expand outward
      // Use multiplication and division instead of shift operations

      mask = 0x00001800; // Start with middle two LEDs
      j = 0;

      while (j < i) {
        mask = mask | (mask * 2) | (mask / 2);
        mask = mask & 0x00FFFFFF; // Ensure high 8 bits are 0
        j = j + 1;
      }

      // Turn off the LEDs in the mask
      pattern = pattern & (~mask);
      light_leds(pattern);
      delay_count = 100000; // Approximately 0.5 second delay
      while (delay_count > 0) {
        delay_count = delay_count - 1;
      }
      i = i + 1;
    }
  }
  
  return 0;
}

