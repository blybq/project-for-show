#include "../driver/leds.driver.c"
#include "../driver/digits.driver.c"
#include "../util/minisys.util.c"

// LED counter: Use LED lights to display the binary counter, and display the decimal value on the 7-segment display
int main(void) {
  int counter;
  int delay_count;
  
  counter = 0;
  
  while (1) {
    // Display the binary value (low 24 bits) on the LED
    light_leds(counter);
            
    // Delay approximately 1 seconds
    delay_count = 10000;
    while (delay_count > 0) {
      // Display the decimal value on the 7-segment display
      smart_display_digit(counter);
      delay_count = delay_count - 1;
    }
    
    // Counter increment
    counter = counter + 1;
    
    // Limit the counter to the range of 24 bits (0-16777215)
    if (counter > 16777215) {
      counter = 0;
    }
  }
  
  return 0;
}

