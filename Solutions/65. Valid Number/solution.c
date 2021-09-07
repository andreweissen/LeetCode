/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 7 September 2021
 * @brief A C-based solution to LeetCode question 65
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define TC_TYPES 2
#define TC_CASES 17

/**
 * @brief This solution, though <code>O(n)</code> and thus dependent upon the
 * number of characters that constitute the string, is very fast on account of
 * its largely hardcoded nature. No data structures are employed, and the
 * determination as to which symbols should follow which is mediated by means of
 * a number of boolean flags that serve to keep track of the parsing operation.
 * The author originally made a quick mockup in JavaScript to get a feel for the
 * problem before creating a faster, more efficient and readable C
 * implementation. 
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 100% of all C implementations with a runtime of 0 ms and more efficient
 * in terms of memory usage than 67.69% of C implementations. 
 *
 * @param s char* The string to be parsed and evaluated
 * @return bool A boolean denoting whether input string  is a number
 */
bool isNumber(char * s) {

  // Declarations
  int i;
  bool hasDecimal, hasE, hasDigit;

  // Definitions
  hasDecimal = false;
  hasE = false;
  hasDigit = false;

  for (i = 0; s[i] != '\0'; i++) {

    // 0-9 digit
    if (s[i] >= '0' && s[i] <= '9') {
      hasDigit = true;

    // Exponent (e or E)
    } else if (s[i] == 'e' || s[i] == 'E') {

      // Only one exponent per number, only valid if preceded by number
      if (hasE || !hasDigit) {
        return false;
      }
      hasE = true;
      hasDigit = false;

    // Decimal
    } else if (s[i] == '.') {

      // Only one decimal per number, no decimal after exponent
      if (hasDecimal || hasE) {
        return false;
      }
      hasDecimal = true;

    // Sign (+ or -)
    } else if (s[i] == '-' || s[i] == '+') {

      // Sign may only appear as first char of number or first of exponent
      if (i != 0 && s[i - 1] != 'e' && s[i - 1] != 'E') {
        return false;
      }

    // All other characters are illegitimate
    } else {
      return false;
    }
  }

  // Numbers cannot be non-numeric (., e, E, +, -)
  return hasDigit;
}

/**
 * @brief  <code>main</code> serves as the example driver for the exercise and
 * runs a  few of the test cases supplied on the LeetCode website to permit the
 * solution to be tested offsite.
 *
 * @param argc int The number of command line args
 * @param argv char** The command line args in string form
 * @return int A status <code>int</code>
 */
int main(int argc, char ** argv) {

  // Declarations
  int i, j;
  char * testCase;

  // Test cases, wellformed and malformed divided into arrays
  char * testCases[TC_TYPES][TC_CASES] = {
    {
      "2",
      "0089",
      "-0.1",
      "+3.14",
      "4.",
      "-.9",
      "2e10",
      "-90E3",
      "3e+7",
      "+6e-1",
      "53.5e93",
      "-123.456e789",
      "1e1",
      "+.1",
      "0",
      "-12E4",
      "46.e3"
    },
    {
      "abc",
      "1a",
      "1e",
      "e3",
      "99e2.5",
      "--6",
      "-+3",
      "95a54e53",
      "3-",
      "33-44.2",
      "99.2.5",
      "000ee11",
      ".",
      ".e1",
      "4e+",
      "+.",
      "+E3"
    }
  };

  for (i = 0; i < TC_TYPES; i++) {
    printf((i == 0) ? "Wellformed input:\n" : "\nMalformed input:\n");
    for (j = 0; j < TC_CASES; j++) {
      testCase = testCases[i][j];
      printf("%s: %s\n", testCase, isNumber(testCase) ? "true" : "false");
    }
  }

  return 0;
}
