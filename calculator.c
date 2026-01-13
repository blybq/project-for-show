#include "../driver/digits.driver.c"
#include "../driver/keyboard.driver.c"
#include "../util/minisys.util.c"

// Use A/B/C/D to represent addition/subtraction/multiplication/division
int main(void) {
  int tempNumber;
  int lastNumber;
  int result;
  int op;
  int key;
  int lastKey;
  int display_num;

  tempNumber = 0;
  lastNumber = 0;
  op = 0;
  result = 0;
  key = 0;
  lastKey = 0;
  display_num = 0;

  while (1) {
    lastKey = key;
    key = read_keyboard();

    if (key == lastKey) {
        if (key < 10 || key == 14) {
          smart_display_digit(display_num);
        } else if (key == 15) {
          smart_display_digit(0);
        } else {
            clear_digits();
        }
        continue;
    }

    // number key: 0~9 
    if (key >= 0 && key <= 9) {
        tempNumber = tempNumber * 10 + key;
        display_num = tempNumber;
        smart_display_digit(display_num);
    }
    
    if (key >= 10 && key <= 13) {
        lastNumber = tempNumber;
        tempNumber = 0;

        if (key == 10) { // A key: Addition
            op = 1;
        } else if (key == 11) { // B key: Subtraction
            op = 2;
        } else if (key == 12) { // C key: Multiplication
            op = 3;
        } else { // D key: Division
            op = 4;
        }

    }

    // E key: Equal 
    if (key == 14) {
        if (op == 1) {
            result = lastNumber + tempNumber;
        } else if (op == 2) {
            result = lastNumber - tempNumber;
        } else if (op == 3) {
            result = lastNumber * tempNumber;
        } else {
            if (tempNumber != 0) {
                result = lastNumber / tempNumber;
            } else {
                result = 0;   // division by zero
            }
        }

        tempNumber = result;
        display_num = result;
        smart_display_digit(display_num);
    }

    // F key: Clear 
    if (key == 15) {
        tempNumber = 0;
        lastNumber = 0;
        op = 0;
        result = 0;
        smart_display_digit(0);
    }
  }
  
  return 0;
}

