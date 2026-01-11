#include "../driver/leds.driver.c"
#include "../driver/keyboard.driver.c"

// all leds light up after 5 secs
int main(void) {
    while (1) {
        light_leds(0x00F00000);
        __asm("syscall");
        light_leds(0x000F0000);
    }
    return 0;
}