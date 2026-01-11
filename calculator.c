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
  int display_num;
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
  display_num = 0;

  while (1) {
    lastKey = key;
    key = read_keyboard();

    if (key == lastKey) {
        if (key < 10) {
          smart_display_digit(display_num);
        }
        if (key >= 10 && key <= 13) {
            clear_digits();
        }
        if (key == 14) {
          smart_display_digit(result);
        }
        if (key == 15) {
          smart_display_digit(0);
        }
        continue;
    }

    // number key: 0~9 
    if (key >= 0 && key <= 9 && state == 0) {
        num1 = num1 * 10 + key;
        display_num = num1;
        smart_display_digit(display_num);
    }

    if (key >= 0 && key <= 9 && state == 1) {
        num2 = num2 * 10 + key;
        display_num = num2;
        smart_display_digit(display_num);
    }

    // A key: Addition 
    if (key == 10 && state == 0) {
        op = 1;
        state = 1;
    }

    // B key: Subtraction 
    if (key == 11 && state == 0) {
        op = 2;
        state = 1;
    }

    // C key: Multiplication 
    if (key == 12 && state == 0) {
        op = 3;
        state = 1;
    }

    // D key: Division 
    if (key == 13 && state == 0) {
        op = 4;
        state = 1;
    }

    // E key: Equal 
    if (key == 14 && state == 1 && op == 1) {
        result = num1 + num2;
    }

    if (key == 14 && state == 1 && op == 2) {
        result = num1 - num2;
    }

    if (key == 14 && state == 1 && op == 3) {
        result = num1 * num2;
    }

    if (key == 14 && state == 1 && op == 4 && num2 != 0) {
        result = num1 / num2;
    }

    if (key == 14 && state == 1 && op == 4 && num2 == 0) {
        result = 0;   // division by zero
    }

    if (key == 14 && state == 1) {
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

