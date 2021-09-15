/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 15 September 2021
 * @brief A C-based solution to LeetCode question 443
 */

#include <stdio.h>

/**
 * @brief This helper function is used by the main <code>compress</code>
 * function to automate the two separate instances in which the number of
 * appearances of a certain <code>char</code> in the <code>chars</code> array is
 * to be added to the result compressed array. Given that the LeetCode question
 * stipulates that group lengths that are 10 or longer are to be split into
 * multiple characters, the function "splits" the <code>occurrences</code> count
 * into its component digits (1994 -> 1, 9, 9, 4), appending the 0-9 digits to
 * the compressed array accordingly.
 *
 * @param occurrences unsigned short int The number of times this char appeared
 * @param chars char* The input array of characters (note: NOT a string)
 * @param n unsigned short int* The address of the <code>n</code> counter
 * @return void
 */
void addCounter(unsigned short int occurrences, char * chars,
    unsigned short int * n) {

  // Declarations
  unsigned short int x;
  unsigned char j, nonZeroes;

  // Split into digits (94 -> 9, 4)
  for (x = 1000, nonZeroes = 0; x > 0; x /= 10) {
    j = (occurrences / x) % 10;

    // Ignore zeroes unless preceded by number (2,0 -> 20)
    if (j != 0 || nonZeroes > 0) {
      chars[(*n)++] = j + '0';
      nonZeroes++;
    }
  }
}

/**
 * @brief This implementation, built to make use of a helper function and laid
 * out in such a way to be more readable than the more compact
 * <code>compress2</code> alternate implementation, is very fast and efficient
 * in comparison to other implementations on account of the fact that it mutates
 * the input array as it iterates over its contents, thus dispensing with the
 * need to make use of a secondary storage data structure.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 98.3% of all C implementations with a runtime of 4 ms and more efficient
 * in terms of memory usage than 95% of C implementations with a memory usage
 * of 6.3 MB.
 *
 * @param chars char* The character array to be parsed (note: NOT a string)
 * @param charsSize int The number of characters in the array
 * @return n int The size of the compressed array (aabbcccc -> a2b2c4 -> 6)
 */
int compress(char * chars, int charsSize) {

  // Declarations
  unsigned short int i, n, o;
  char c;

  // Edge case: no modifications necessary
  if (charsSize == 1) {
    return 1;
  }

  for (i = 0, c = '\0', n = 0, o = 0; i < charsSize; i++) {

    // If we have encountered a different character...
    if (chars[i] != c) {

      // If isn't first char and if multiple encounters w/ previous
      if (i != 0 && o > 1) {

        // Add counter for previous char before moving to new one
        addCounter(o, chars, &n);
      }

      // Set new character
      chars[n++] = chars[i];

      // This counts as 1 new encounter
      o = 1;

      // Set this character as our current character
      c = chars[i];
    } else {

      // If yet another encounter, increment counter only
      o++;
    }

    // Make sure counter for final character is included before loop exit
    if (i == charsSize - 1 && o > 1) {
      addCounter(o, chars, &n);
    }
  }

  return n;
}

/**
 * @brief This implementation is an alternate version of the main
 * <code>compress</code> function, developed to make use of no helper function
 * and instead handle the two separate inclusions of the character counter in
 * one place in the code. Despite its more compact design, it is significantly
 * slower and less memory efficient than the main implementation and was
 * included simply for documentation's sake.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 90% of all C implementations with a runtime of 8 ms and more efficient
 * in terms of memory usage than 40% of C implementations with a memory usage
 * of 6.5 MB.
 *
 * @param chars char* The character array to be parsed (note: NOT a string)
 * @param charsSize int The number of characters in the array
 * @return n int The size of the compressed array (aabbcccc -> a2b2c4 -> 6)
 */
int compress2(char * chars, int charsSize) {

  // Declarations
  unsigned short int i, x, n, o;
  unsigned char j, nonZeroes;
  char c;

  // Edge case: no modifications necessary
  if (charsSize == 1) {
    return 1;
  }

  for (i = 0, c = '\0', n = 0, o = 0; i <= charsSize; i++) {
    if (o > 1 && ((i == charsSize) || (chars[i] != c && i != 0))) {

      // Adding counter, same as addCounter() above
      for (x = 1000, nonZeroes = 0; x > 0; x /= 10) {
        j = (o / x) % 10;
        if (j != 0 || nonZeroes > 0) {
          chars[n++] = j + '0';
          nonZeroes++;
        }
      }  
    }

    // Only increment and mutate if not last loop iteration
    if (i < charsSize) {

      // If we've encountered a new character
      if (chars[i] != c) {
        chars[n++] = chars[i];
        o = 1;
        c = chars[i];
      } else {
        o++;
      }
    }
  }

  return n;
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

  char testCase1[] = {'a','a','b','b','c','c','c'},
       testCase2[] = {'a'},
       testCase3[] = {'a','b','b','b','b','b','b','b','b','b','b','b','b'},
       testCase4[] = {'a','a','a','b','b','a','a'},
       testCase5[] = {'a', 'b', 'c'},
       testCase6[] = {'o','o','o','o','o','o','o','o','o','o'};

  printf("Expected: %d\nOutput: %d\n", 6, compress(testCase1, 7));
  printf("Expected: %d\nOutput: %d\n", 1, compress(testCase2, 1));
  printf("Expected: %d\nOutput: %d\n", 4, compress(testCase3, 13));
  printf("Expected: %d\nOutput: %d\n", 6, compress(testCase4, 7));
  printf("Expected: %d\nOutput: %d\n", 3, compress(testCase5, 3));
  printf("Expected: %d\nOutput: %d\n", 3, compress(testCase6, 10));
  
  return 0;
}
