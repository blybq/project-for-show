#include "../driver/digits.driver.c"
#include "../driver/keyboard.driver.c"
#include "../util/minisys.util.c"

// Use A/B/C/D to represent addition/subtraction/multiplication/division
int main(void) {
  int num1;
  int num2;
  int result;
  int op;
  int key;
  int lastKey;
  int state;
  
  // 0: Wait for the first number, 1: Wait for the operator
  // 2: Wait for the second number, 3: Display the result
  state = 0;
  
  num1 = 0;
  num2 = 0;
  op = 0;
  result = 0;
  key = 0;
  lastKey = 0;

  while (1) {
    lastKey = key;
    key = read_keyboard();

    if (key == lastKey && key != 14 && key != 15) {
      smart_display_digit(key);
      continue;
    }

    // number key: 0~9 
    if (key >= 0 && key <= 9 && state == 0) {
        num1 = key;
        state = 1;
        smart_display_digit(key);
    }

    if (key >= 0 && key <= 9 && state == 2) {
        num2 = key;
        state = 3;
        smart_display_digit(key);
    }

    // A key: Addition 
    if (key == 10 && state == 1) {
        op = 1;
        state = 2;
    }

    // B key: Subtraction 
    if (key == 11 && state == 1) {
        op = 2;
        state = 2;
    }

    // C key: Multiplication 
    if (key == 12 && state == 1) {
        op = 3;
        state = 2;
    }

    // D key: Division 
    if (key == 13 && state == 1) {
        op = 4;
        state = 2;
    }

    // E key: Equal 
    if (key == 14 && state == 3 && op == 1) {
        result = num1 + num2;
    }

    if (key == 14 && state == 3 && op == 2) {
        result = num1 - num2;
    }

    if (key == 14 && state == 3 && op == 3) {
        result = num1 * num2;
    }

    if (key == 14 && state == 3 && op == 4 && num2 != 0) {
        result = num1 / num2;
    }

    if (key == 14 && state == 3 && op == 4 && num2 == 0) {
        result = 0;   // division by zero
    }

    if (key == 14 && state == 3) {
        smart_display_digit(result);
        state = 0;
    }

    // F key: Clear 
    if (key == 15) {
        num1 = 0;
        num2 = 0;
        op = 0;
        result = 0;
        state = 0;
        smart_display_digit(0);
    }
  }
  
  return 0;
}

