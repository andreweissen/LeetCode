/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 10 September 2021
 * @brief A C-based solution to LeetCode question 12
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The author was particularly pleased with the way this implementation
 * turned out, as the function in large part wrote itself. The approach largely
 * revolved around the base idea of "splitting" the input <code>int</code> into
 * its base <code>char</code>s, i.e. 1994 -> 1, 9, 9, 4. Given the formulatic
 * nature of the Roman numeral system, the evaluation of thousands, hundreds,
 * tens, and ones was mostly the same at each level and differed only in the
 * numerals employed for the given number. Among many advantages, this allowed
 * for the quick and easy calculation of the string size necessary to store the
 * return <code>char</code> array.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 81% of all C implementations with a runtime of 3 ms and more efficient
 * in terms of memory usage than 94% of C implementations with a memory usage
 * of 5.8 MB.
 *
 * @param num int The number to be converted to a Roman numeral string
 * @return s char* The parsed string of the input <code>int</code>
 */
char * intToRoman(int num) {

  // Declarations
  char c, i, j, k, l, spl[4], rn[7], * s;

  // "Split" the int into chars (1994 -> 1, 9, 9, 4)
  spl[0] = num / 1000;
  spl[1] = (num / 100) % 10;
  spl[2] = (num / 10) % 10;
  spl[3] = num % 10;

  // Set initial string size
  l = 0;

  // Calculate return string size
  for (i = 0; i < 4; i++) {

    // Input only goes to 4999, so only need to add number of 'M's present
    if (spl[i] == 0) {
      l += spl[i];
    } else {

      // 1s and 5s only get one numeral; examples: I, V, L, C
      if (spl[i] == 1 || spl[i] == 5) {
        l += 1;

      // 2s, 4s, 6s, and 9s get two numerals; examples: IV, VI, LX, CC, II
      } else if (spl[i] == 2 || spl[i] == 4 || spl[i] == 6 || spl[i] == 9) {
        l += 2;

      // 3s and 7s get three numerals; examples: III, VII, LXX, CCC, DCC
      } else if (spl[i] == 3 || spl[i] == 7) {
        l += 3;

      // 8s get four numerals; examples: VIII, LXXX, DCCC
      } else if (spl[i] == 8) {
        l += 4;

      // Unreachable edge case because why not (input guaranteed wellformed)
      } else {
        l += 0;
      }
    }
  }
  
  // String iterator
  c = 0;

  // Create new return string of required size for number
  s = malloc(l + 1);

  // Define numerals (predetermined order important)
  rn[0] = 'M';
  rn[1] = 'C';
  rn[2] = 'D';
  rn[3] = 'X';
  rn[4] = 'L';
  rn[5] = 'I';
  rn[6] = 'V';

  // Iterate over 1000s, 100s, 10s, and 1s respectively
  for (i = 0, k = 0; i < 4; i++) {

    // Input only goes to 4999, so only add as many 'M's as there are thousands
    if (i == 0) {
      if (spl[i] != 0) {
        for (j = 0; j < spl[i]; j++) {
          s[c++] = rn[i];
        }
      }
    } else {

      // Helper variable to keep track of which numeral to use
      k = i * 2 - 1;
      if (spl[i] != 0) {

        // Examples: 3=III, 20=XX,
        if (spl[i] > 0 && spl[i] < 4) {
          for (j = 0; j < spl[i]; j++) {
            s[c++] = rn[k];
          }

        // Examples: 4=IV, 40=XL
        } else if (spl[i] == 4) {
          s[c++] = rn[k];
          s[c++] = rn[k + 1];

        // Examples: 7=VII, 800=DCCC
        } else if (spl[i] > 4 && spl[i] < 9) {
          s[c++] = rn[k + 1];
          for (j = 0; j < (spl[i] - 5); j++) {
            s[c++] = rn[k];
          }

        // Examples: 9=IX, 90=XC
        } else if (spl[i] == 9) {
          s[c++] = rn[k];
          s[c++] = rn[k - ((k == 1) ? 1 : 2)];
        }
      }
    }
  }

  s[c] = '\0';
  
  return s;
}

/**
 * @brief <code>main</code> serves as the example driver for the exercise and
 * runs a few of the test cases supplied on the LeetCode website to permit the
 * solution to be tested offsite.
 *
 * @param argc int The number of command line args
 * @param argv char** The command line args in string form
 * @return int A status <code>int</code>
 */
int main(int argc, char * argv) {
  
  // Declarations
  int i, len, testCases[] = {5, 3, 4, 9, 58, 1994};
  char * result;

  len = sizeof(testCases) / sizeof(*testCases);
  for (i = 0; i < len; i++) {
    result = intToRoman(testCases[i]);
    printf("%s\n", result);
    free(result);
  }

  return 0;
}
