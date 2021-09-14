/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 14 September 2021
 * @brief A C-based solution to LeetCode question 1684
 */

#include <stdio.h>
#include <stdbool.h>

/**
 * @brief This (pretty standard) implementation of the problem varied widely
 * in terms of both speed and memory usage, ranging from 40 ms to 103 ms and
 * 12.1 to 12.3 MB. Despite the author's attempts to reduce memory usage below
 * 12 MB by allocating space for as few variables as possible, the function
 * still ran sluggishly slow and inefficiently.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 89% of all C implementations with a runtime of 40 ms and more efficient
 * in terms of memory usage than 97% of C implementations with a memory usage
 * of 12.1 MB.
 *
 * @param allowed char* A string denoting permissible chars
 * @param words char** An array of strings to be checked against listing
 * @param wordsSize int Size of the <code>words</code> array
 * @return n int The number of strings containing only permissible characters
 */
int countConsistentStrings(char * allowed, char ** words, int wordsSize) {

  // Declarations
  unsigned short int i, n;
  bool hasErrors;

  // Create alphabet-sized array containing 0s
  unsigned char a[26] = {0};

  // Increment indices associated with permissible letters
  while (*allowed) a[*allowed++ - 'a']++;

  for (i = 0, n = 0; i < wordsSize; i++) {
    hasErrors = false;

    // Iterate along current word and check if this is a permissible letter
    while (*words[i]) {
      if (a[*words[i]++ - 'a'] == 0) {
        hasErrors = true;
        break;
      }
    }

    // Current word is permissible if no errors encountered
    if (!hasErrors) n++;
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
  char * words1[] = {"ad","bd","aaab","baa","badab"},
       * words2[] = {"a","b","c","ab","ac","bc","abc"},
       * words3[] = {"cc","acd","b","ba","bac","bad","ac","d"};

  printf("%d\n", countConsistentStrings("ab", words1, 5));
  printf("%d\n", countConsistentStrings("abc", words2, 7));
  printf("%d\n", countConsistentStrings("cad", words3, 8));

  return 0;
}
