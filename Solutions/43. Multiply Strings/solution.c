/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 15 September 2021
 * @brief A C-based solution to LeetCode question 43
 */

#include <stdio.h>
#include <stdlib.h>

/**
 * @brief The author originally solved this particular LeetCode problem on the
 * ninth of September, but was dissatisfied enough with the speed and memory
 * usage of that particular implementation to revisit the problem and craft a
 * more efficient approach. The optimal approach would likewise involve the use
 * of bitwise << and >> operators in a Russian peasant multiplication system,
 * but this more straightfoward approach is still fairly quick in comparison to
 * other submissions.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 100% of all C implementations with a runtime of 0 ms and more efficient
 * in terms of memory usage than 91% of C implementations with a memory usage
 * of 5.8 MB.
 *
 * @param num1 char* The first number in string form 
 * @param num2 char* The second number in string form
 * @return s char* The product of the multiplication in string form
 */
char * multiply(char * num1, char * num2) {

  // Declarations
  char * s, * p_s;
  unsigned char t, len1, len2;
  int i, j, sum[500] = {0};

  // Edge cases if one or both operands are 0 (product will always be 0)
  if (num1[0] == '0' || num2[0] == '0') {
    s = malloc(sizeof(char) * 2);
    s[0] = '0';
    s[1] = '\0';
    return s;
  }

  // Definitions
  len1 = 0;
  len2 = 0;

  // Determine size of num1 w/o strlen
  p_s = num1;
  while (*p_s) len1++, p_s++;

  // Determine size of num2 w/o strlen
  p_s = num2;
  while (*p_s) len2++, p_s++;

  for (i = len1 - 1; i >= 0; i--) {
    for (j = len2 - 1; j >= 0; j--) {

      // Convert to ints and perform multiplication
      sum[i + j + 1] += (num1[i] - '0') * (num2[j] - '0');

      // Set previous value with carry
      sum[i + j] += sum[i + j + 1] / 10;

      // Set remainder as this element's value
      sum[i + j + 1] %= 10;
    }
  }

  // Further definitions
  s = malloc(sizeof(char) * (len1 + len2 + 2));
  t = ((sum[0] != 0) ? 0 : 1);

  // Convert integers back to chars and concat to return string
  for (i = t; i < (len1 + len2); i++) {
    s[i - t] = sum[i] + '0';
  }
  s[(len1 + len2) - t] = '\0';

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
  unsigned char i, len;
  char * s, * testCases[] = {
    "12",
    "13",
    "123456789",
    "987654321",
    "2",
    "3",
    "0",
    "0",
    "9133",
    "0"
  };

  len = (sizeof(testCases) / sizeof(*testCases));
  for (i = 0; i < len; i += 2) {
    s = multiply(testCases[i], testCases[i + 1]);
    printf("%s * %s = %s\n", testCases[i], testCases[i + 1], s);
    free(s);
  }
}
