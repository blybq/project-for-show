#include "../driver/digits.driver.c"
#include "../util/minisys.util.c"

// Fibonacci sequence: Display the first 10 Fibonacci numbers on the 7-segment display
int fib[10];

int main(void) {  
  int i;
  int delay_count;
  
  // Initialize the first two numbers
  fib[0] = 0;
  fib[1] = 1;
  
  // Calculate the Fibonacci sequence
  i = 2;
  while (i < 10) {
    fib[i] = fib[i - 1] + fib[i - 2];
    i = i + 1;
  }
  
  // Display the Fibonacci numbers on the 7-segment display
  i = 0;
  while (i < 10) {
    smart_display_digit(fib[i]);
    delay_count = 500000; // Approximately 1 second delay
    while (delay_count > 0) {
      delay_count = delay_count - 1;
    }
    i = i + 1;
  }
  
  // Loop display
  while (1) {
    i = 0;
    while (i < 10) {
      smart_display_digit(fib[i]);
      delay_count = 500000;
      while (delay_count > 0) {
        delay_count = delay_count - 1;
      }
      i = i + 1;
    }
  }
  
  return 0;
}

