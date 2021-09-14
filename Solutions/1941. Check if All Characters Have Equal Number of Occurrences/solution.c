/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 14 September 2021
 * @brief A C-based solution to LeetCode question 1941
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief This implemention came together on its own very quickly. In keeping
 * with the age-old developers' wisdom "when in doubt, throw a hash map at the
 * problem," the author approached the problem from the perspective of key/value
 * pairs in which each key corresponds to one of the 26 lowercase English
 * letters the problem establishes as constituting wellformed input and the
 * value corresponds to the number of appearances of that letter. 
 * <br />
 * <br />
 * As implementating a hashtable for such a small problem would be neither
 * fast nor memory efficient, the author instead embraced the idea of a simple
 * <code>int</code> array of size 26 wherein each index would correspond to a
 * letter and each <code>int</code> value at that index the number of
 * appearances.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 100% of all C implementations with a runtime of 0 ms and more efficient
 * in terms of memory usage than 91% of C implementations with a memory usage
 * of 5.7 MB.
 *
 * @param s char* The input string to be parsed and examined
 * @return bool A status boolean indicating if the input has equal # of characters
 */
bool areOccurrencesEqual(char * s) {

  // Declarations (define array with 26 zeroes)
  unsigned short int i, p, o[26] = {0};

  // Fill array with number of appearances (subtract char by 'A' to find index)
  for (i = 0; s[i] != '\0'; i++) {
    o[s[i] - 97]++;
  }

  for (i = 0, p = 0; i < 26; i++) {

    // Iterate until a non-zero value is found and set as marker
    if (o[i] > 0 && p == 0) {
      p = o[i];

    // Return false if value found larger or smaller than previous marker
    } else if (o[i] > 0 && o[i] != p) {
      return false;
    }
  }

  return true;
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
  unsigned char i, len;
  char * testCases[] = {
    "abacbc",
    "aaabb",
    "a",
    "abba"
  };

  len = sizeof(testCases) / sizeof(*testCases);
  for (i = 0; i < len; i++) {
    printf("%d: %s -> %s", i + 1, testCases[i],
      areOccurrencesEqual(testCases[i]) ? "true\n" : "false\n");
  }

  return 0;
}
