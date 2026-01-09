#include "../driver/keyboard.driver.c"
#include "../driver/digits.driver.c"
#include "../util/minisys.util.c"

// Keyboard display program: Display the keyboard key value in real time, support hexadecimal display
int main(void) {
  int key;
  int last_key;
  
  last_key = 0xFFFFFFFF;
  
  while (1) {
    key = read_keyboard();
    
    // Only update the display when the key changes
    if (key != last_key) {
      if (key >= 0 && key <= 15) {
        // Valid key: Display the hexadecimal value (0-F)
        smart_display_digit(key);
      } 
      if (key < 0 || key > 15) {
        // No key: Display 0
        smart_display_digit(0);
      }
      last_key = key;
    }
  }
  
  return 0;
}

