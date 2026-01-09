#include "../driver/keyboard.driver.c"
#include "../util/minisys.util.c"

// Little electronic piano: Use keyboard keys to control the buzzer to emit different tones
// The keys 0-9 correspond to different tones, and different tones are simulated by controlling the buzzer switch frequency
int main(void) {
  int key;
  int delay_count;
  int cycle_count;
  int i;
  
  while (1) {
    key = read_keyboard();
    
    if (key >= 0 && key <= 9) {
      // Control the buzzer switch frequency according to the key (simulate different tones)
      // The key 0: The slowest frequency, the key 9: The fastest frequency
      cycle_count = 50 - key * 5; // The number of cycles: 50, 45, 40, ..., 5
      
      i = 0;
      while (i < cycle_count) {
        // Open the buzzer
        $0xFFFFFD10 = 1;
        
        // Delay (adjust the delay time according to the key)
        delay_count = 10000 - key * 1000; // Delay: 10000, 9000, ..., 1000
        while (delay_count > 0) {
          delay_count = delay_count - 1;
        }
        
        // Close the buzzer
        $0xFFFFFD10 = 0;
        
        delay_count = 10000 - key * 1000;
        while (delay_count > 0) {
          delay_count = delay_count - 1;
        }
        
        i = i + 1;
      }
    } 
    if (key < 0 || key > 9) {
      $0xFFFFFD10 = 0; // Close the buzzer when there is no key
    }
  }
  
  return 0;
}

