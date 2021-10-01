/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 1 October 2021
 * @brief A C-based solution to LeetCode question 75
 */

#include <stdio.h>

/**
 * @brief This implementation constitutes the author's first attempt at solving
 * the problem. Though not necessarily an inefficient or slow approach, it is
 * needlessly complicated, a result of the author's overthinking of the problem.
 * The subsequent implementation, which ended up being just as fast but slightly
 * more memory efficient, more readily took advantage of a hackier approach than
 * that evidenced here.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 100% of all C implementations with a runtime of 0 ms and more efficient
 * in terms of memory usage than 47% of C implementations with a memory usage
 * of 6.0 MB.
 *
 * @param nums int* Pointer to the first element in the input nums array
 * @param numsSize int Number of elements in input array
 * @return void
 */
void sortColors2(int * nums, int numsSize) {
  
  // Declarations
  int t;
  char i, j, k;

  // Handle edge cases requiring no in-place adjustments
  if (numsSize == 1) {
    return;
  }

  for (i = 0, j = 0, k = numsSize - 1; i <= k; i++) {
    if (nums[i] == 0) {
      t = nums[i];
      nums[i] = nums[j];
      nums[j++] = t;
    } else if (nums[i] == 2) {
      t = nums[i];
      nums[i--] = nums[k];
      nums[k--] = t;
    }
  }
}

/**
 * @brief This implementation constitutes the author's second approach to
 * solving this problem in a fashion that better takes advantage of "hacky
 * thinking." Rather than iterating along the array shifting elements as needed,
 * this approach takes advantage of the fact that only 0, 1, and 2 will appear
 * as input, and creates a de facto map out of a size-3 array to keep track of
 * occurrences. It then iterates once along the array, switching values in
 * accordance with the map data and a positional marker.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 100% of all C implementations with a runtime of 0 ms and more efficient
 * in terms of memory usage than 96.25% of C implementations with a memory usage
 * of 5.9 MB.
 *
 * @param nums int* Pointer to the first element in the input nums array
 * @param numsSize int Number of elements in input array
 * @return void
 */
void sortColors(int * nums, int numsSize) {

  // Handle edge cases requiring no in-place adjustments
  if (numsSize == 1) {
    return;
  }

  // Declarations
  char i, pos;

  // De facto map to store occurrences
  int map[3] = {0};

  // Establish number of occurrences of each 0, 1, 2
  for (i = 0; i < numsSize; i++) {
    map[nums[i]]++;
  }

  // Run over nums once, changing via positional marker
  for (i = 0, pos = 0; i < 3; i++) {
    while (map[i]--) {
      nums[pos++] = i;
    }
  }
}

/**
 * @brief This function serves simply as a helper function used by
 * <code>main</code> for the purposes of printing the test case array post-sort
 * in stdout without hastle. This allows for determining if the implementation
 * in question worked properly.
 *
 * @param testCase int* Pointer to the first element in the test case array
 * @param testCaseSize int Number of elements in the test case array
 * @return void
 */
void formatPrint(int * testCase, int testCaseSize) {
  unsigned char i;

  printf("[");
  for (i = 0; i < testCaseSize; i++) {
    if (i == testCaseSize - 1) {
      printf("%d", testCase[i]);
    } else {
      printf("%d,", testCase[i]);
    }
  }
  printf("]\n");
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

  // Define test cases
  int testCase1[] = {2,0,2,1,1,0};
  int testCase2[] = {2,0,1};
  int testCase3[] = {0};
  int testCase4[] = {1};
  int testCase5[] = {2};
  int testCase6[] = {2,2};

  // Perform sort in place
  sortColors(testCase1, 6);
  sortColors(testCase2, 3);
  sortColors(testCase3, 1);
  sortColors(testCase4, 1);
  sortColors(testCase5, 1);
  sortColors(testCase6, 2);

  // Print the formatted results
  formatPrint(testCase1, 6);
  formatPrint(testCase2, 3);
  formatPrint(testCase3, 1);
  formatPrint(testCase4, 1);
  formatPrint(testCase5, 1);
  formatPrint(testCase6, 2);

  return 0;
}
