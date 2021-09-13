/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 13 September 2021
 * @brief A C-based solution to LeetCode question 273
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define REQUIRES_BILLION  0x01 // 0b00000001
#define REQUIRES_MILLION  0x02 // 0b00000010
#define REQUIRES_THOUSAND 0x04 // 0b00000100

/**
 * @brief This implementation of question 273 was built to be similar in form to
 * the author's submission for question 12 "Integer to Roman" on LeetCode. As
 * with that question, the function "splits" the input <code>int</code> into its
 * component digits (i.e. 0000000123 -> 0, 0, 0, 0, 0, 0, 0, 1, 2, 3) and adds
 * them to an array of size 10. This array is then iterated over twice, first to
 * determine the size of the string to be returned from the function and second
 * to actually assemble the string from an English words listing.
 * <br />
 * <br />
 * The author toyed with the idea of making use of a different data structure
 * than a single 10-item array early in the design process. Noticing that
 * English-language numeric representations follow a similar structure for the
 * millions, thousands, and singles, the author considered treating billions as
 * an edge case and grouping the hundreds, tens, and singles of the millions,
 * thousands, and hundreds into arrays of three to form a 3x3 matrix that could
 * more easily traversed. However, this approach was ultimately abandoned due to
 * the fact that its code was equally as obtuse as that of the default 10-item
 * array approach.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 100% of all C implementations with a runtime of 0 ms and more efficient
 * in terms of memory usage than 96% of C implementations with a memory usage
 * of 5.7 MB.
 *
 * @param num int The number to be converted to an English sentence
 * @return s char* The parsed string of the input <code>int</code>
 */
char * numberToWords(int num) {
  
  // Declarations
  char c, i, l, f, spl[10], * p_w, * s;
  int x;

  // English display text to be returned
  char * words[] = {    //  Ind  Num letters
    "Zero ",            //  0 -> 5
    "One ",             //  1 -> 4
    "Two ",             //  2 -> 4
    "Three ",           //  3 -> 6
    "Four ",            //  4 -> 5
    "Five ",            //  5 -> 5
    "Six ",             //  6 -> 4
    "Seven ",           //  7 -> 6
    "Eight ",           //  8 -> 6
    "Nine ",            //  9 -> 5
    "Ten ",             // 10 -> 4
    "Eleven ",          // 11 -> 7
    "Twelve ",          // 12 -> 7
    "Thirteen ",        // 13 -> 9
    "Fourteen ",        // 14 -> 9
    "Fifteen ",         // 15 -> 8
    "Sixteen ",         // 16 -> 8
    "Seventeen ",       // 17 -> 10
    "Eighteen ",        // 18 -> 9
    "Nineteen ",        // 19 -> 9
    "Twenty ",          // 20 -> 7
    "Thirty ",          // 21 -> 7
    "Forty ",           // 22 -> 6
    "Fifty ",           // 23 -> 6
    "Sixty ",           // 24 -> 6
    "Seventy ",         // 25 -> 8
    "Eighty ",          // 26 -> 7
    "Ninety ",          // 27 -> 7
    "Hundred ",         // 28 -> 8
    "Thousand ",        // 29 -> 9
    "Million ",         // 30 -> 8
    "Billion "          // 31 -> 8
  };

  /*
   *  Len  Num
   *  4 -> 1, 2, 6
   *  5 -> 0, 4, 5, 9
   *  6 -> 3, 7, 8
   *
   *  4 -> 10
   *  7 -> 11, 12
   *  8 -> 15, 16
   *  9 -> 13, 14, 18, 19
   * 10 -> 17
   *
   *  6 -> 40, 50, 60
   *  7 -> 20, 30, 80, 90
   *  8 -> 70
   */

  // "Split" the input int into its component digits (1994 -> 1, 9, 9, 4)
  for(x = 1000000000, i = 0; x > 0; x /= 10, i++) {
    spl[i] = (num / x) % 10;
  }

  // Calculate size of return string
  for (i = 0, l = 0, f = 0; i < 10; i++) {

    // Ignore if no number in this position
    if (spl[i] == 0) {
      continue;
    }

    // A "Billion" marker is needed
    if (i == 0) {
      f = f | REQUIRES_BILLION;

    // A "Million" marker is needed
    } else if (i > 0 && i < 4) {
      f = f | REQUIRES_MILLION;

    // A "Thousand" marker is needed
    } else if (i > 3 && i < 7) {
      f = f | REQUIRES_THOUSAND;
    }

    // Singles
    if (i % 3 == 0) {
      
      // Only add length for singles if billions or if tens value isn't 1
      if (i == 0 || spl[i - 1] != 1) {
        if (spl[i] == 1 || spl[i] == 2 || spl[i] == 6) {
          l += 4;
        } else if (spl[i] == 0 || spl[i] == 4 || spl[i] == 5 || spl[i] == 9) {
          l += 5;
        } else if (spl[i] == 3 || spl[i] == 7 || spl[i] == 8) {
          l += 6;
        } else {
          l += 0;
        }
      }

    // Tens
    } else if (i == 2 || i == 5 || i == 8) {

      // Use teen forms in conjunction with singles value if tens value is 1
      if (spl[i] == 1) {
        if (spl[i + 1] == 0) {
          l += 4;
        } else if (spl[i + 1] == 1 || spl[i + 1] == 2) {
          l += 7;
        } else if (spl[i + 1] == 5 || spl[i + 1] == 6) {
          l += 8;
        } else if (spl[i + 1] == 3 || spl[i + 1] == 4 || spl[i + 1] == 8 ||
            spl[i + 1] == 9) {
          l += 9;
        } else if (spl[i + 1] == 7) {
          l += 10;
        } else {
          l += 0;
        }

      // Use multiple tens forms (twenty, thirty, etc.)
      } else {
        if (spl[i] == 4 || spl[i] == 5 || spl[i] == 6) {
          l += 6;
        } else if (spl[i] == 2 || spl[i] == 3 || spl[i] == 8 || spl[i] == 9) {
          l += 7;
        } else if (spl[i] == 7) {
          l += 8;
        } else {
          l += 0;
        }
      }

    // Hundreds
    } else {
      if (spl[i] == 1 || spl[i] == 2 || spl[i] == 6) {
        l += 4;
      } else if (spl[i] == 4 || spl[i] == 5 || spl[i] == 9) {
        l += 5;
      } else if (spl[i] == 3 || spl[i] == 7 || spl[i] == 8) {
        l += 6;
      } else {
        l += 0;
      }

      // All hundreds values add "Hundred " after numeric representation
      l += 8;
    }
  }

  // Include length of string "Billion" if marker is required
  if (f & REQUIRES_BILLION) {
    l += 8;
  }

  // Include length of string "Million" if marker is required
  if (f & REQUIRES_MILLION) {
    l += 8;
  }

  // Include length of string "Thousand" if marker is required
  if (f & REQUIRES_THOUSAND) {
    l += 9;
  }

  // Handle edge case of zero
  if (l == 0) {
    s = malloc(5);
    c = 0;

    p_w = words[0];
    while (*p_w) s[c++] = *p_w++;
  } else {

    // Build the string of specified length
    for (i = 0, c = 0, s = malloc(l); i < 10; i++) {
      if (spl[i] == 0 && i % 3 != 0) {
        continue;
      }

      // Singles
      if (i % 3 == 0) {
        if (spl[i] != 0 && (i == 0 || spl[i - 1] != 1)) {
          p_w = words[spl[i]];
          while (*p_w) s[c++] = *p_w++;
        }

        if (i == 0 && (f & REQUIRES_BILLION)) {
          p_w = words[31];
          while (*p_w) s[c++] = *p_w++;
        } else if (i == 3 && (f & REQUIRES_MILLION)) {
          p_w = words[30];
          while (*p_w) s[c++] = *p_w++;
        } else if (i == 6 && (f & REQUIRES_THOUSAND)) {
          p_w = words[29];
          while (*p_w) s[c++] = *p_w++;
        }

      // Tens
      } else if (i == 2 || i == 5 || i == 8) {

        if (spl[i] == 1) {
          p_w = words[spl[i + 1] + 10];
        } else {
          p_w = words[spl[i] + 18];
        }

        while (*p_w) s[c++] = *p_w++;

      // Hundreds
      } else {

        p_w = words[spl[i]];
        while (*p_w) s[c++] = *p_w++;

        p_w = words[28];
        while (*p_w) s[c++] = *p_w++;
      }
    }
  }

  s[--c] = '\0';

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
int main(int argc, char ** argv) {

  // Declarations
  int i, len, testCase;
  char * result;
  int testCases[] = {    // String length
    0,                   // 4 + 1
    123,                 // 24 + 1
    12345,               // 40 + 1
    1234567,             // 69 + 1
    1234567891,          // 102 + 1
    10000                // 12 + 1
  };

  len = sizeof(testCases) / sizeof(*testCases);
  for (i = 0; i < len; i++) {
    testCase = testCases[i];
    result = numberToWords(testCase);
    printf("%d: %s\n", testCase, result);
    free(result);
  }

  return 0;
}
