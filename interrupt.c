#include "../driver/leds.driver.c"
#include "../driver/keyboard.driver.c"

// all leds light up after 5 secs
int main(void) {
  int key;
  int delay_count;
  while (1) {
    light_leds(0x00110000);
    delay_count = 1000000;
    while (delay_count > 0) {
        delay_count = delay_count - 1;
    }
    key = read_keyboard();
    if (key == 4) {
        __asm("syscall");
        delay_count = 1000000;
        while (delay_count > 0) {
            delay_count = delay_count - 1;
        }
        light_leds(0x0000FF00);
        delay_count = 1000000;
        while (delay_count > 0) {
            delay_count = delay_count - 1;
        }
    }
  }
  return 0;
}