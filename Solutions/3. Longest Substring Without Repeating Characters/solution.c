/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 17 September 2021
 * @brief A C-based solution to LeetCode question 3
 */

#include <stdio.h>

/**
 * @brief This submission constitutes the second of two attempts at answering
 * this question. The author's original submission, though slightly more memory
 * efficient than this approach, was some 20 times slower on account of its
 * quadratic time complexity. It previously iterated character by character for
 * each character, adding a "1" to a storage array whenever a new character was
 * found. On account of its requiring two nested loops and a separate function
 * dedicated to resetting storage array members back to 0 each time the outer
 * loop iterated, the implementation was slow and sluggest, necessitating the
 * author develop an alternate approach.
 * <br />
 * <br />
 * The subsequent submission likewise makes use of a storage array, but instead
 * of storing "1" or "0" depending on whether the character had previously been
 * encountered, it stores the index of the last encounter and thus requires only
 * one pass and no ancillary array reset function. While traditionally the index
 * "-1" is used to denote a nonexistent index, this implementation uses "0" as a
 * nonexistent index and treats "1" as the first index when iterating along the
 * parameter string. This permits the exclusion of the for loop that would
 * otherwise be required to set all array elements to -1 at the start of the
 * program in favor of simply using the shorthand {0}, thus shaving off up to 4
 * ms and .2 MB and propelling this implementation into the top 1% and 4% of
 * C-based implementations.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 100% of all C implementations with a runtime of 0 ms and more efficient
 * in terms of memory usage than 96.2% of C implementations with a memory usage
 * of 5.7 MB.
 *
 * @param s char* The input string to be parsed by the function
 * @return longest int The length of the longest unique substring in the input
 */
int lengthOfLongestSubstring(char * s) {

  // Declarations (array of size 95 since only letters, digits, & symbols) 
  unsigned short int i, longest, previous, start, occurrences[95] = {0};

  // Start index at 1 to preclude need for a loop setting array elements to -1
  for (i = 1, longest = 0, start = 1; *s; s++, i++) {

    // Grab index of previous appearance (0 if hasn't appeared previously)
    previous = occurrences[*s - 32];

    // Set current index as new previous
    occurrences[*s - 32] = i;

    if (previous >= start) {

      // Reset longest if a new longest unique substring located
      if (longest < (i - start)) {
        longest = i - start;
      }

      // Reset start and continue iterating
      start = previous + 1;
    }
  }

  // Handle cases in which input string has no duplicates
  if (longest < (i - start)) {
    longest = i - start;
  }

  return longest;
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
  unsigned char i, len;

  char * testCases[] = {
    "abcabcbb",
    "bbbbb",
    "pwwkew",
    "dvdf",
    "",
    " ",
    "c"
  };

  len = sizeof(testCases) / sizeof(*testCases);
  for (i = 0; i < len; i++) {
    printf("%s: %d\n", testCases[i],
        lengthOfLongestSubstring(testCases[i]));
  }

  return 0;
}
