/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 16 September 2021
 * @brief A C-based solution to LeetCode question 4
 */

#include <stdio.h>

/**
 * @brief Though listed as "hard" in the LeetCode website, this problem could be
 * solved fairly easily by a trivial application of a standard Merge Sort
 * algorithm taught in most CS classes. The approach employed herein merges the
 * two input arrays of <code>int</code>s into one via merge sort, then either
 * returns the middle element in the resultant array if the size is odd or
 * calculates the value of the median by finding the mean of the middle two
 * elements if the size of the resultant array is even.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 97.3% of all C implementations with a runtime of 8 ms and more efficient
 * in terms of memory usage than 99.7% of C implementations with a memory usage
 * of 6.3 MB.
 *
 * @param nums1 int* Array of <code>int</code>s
 * @param nums1Size int Size of <code>nums1</code>
 * @param nums2 int* Array of <code>int</code>s
 * @param nums2Size int Size of <code>nums2</code>
 * @return double The value of the median in <code>double</code> form
 */
double findMedianSortedArrays(int * nums1, int nums1Size, int * nums2,
    int nums2Size) {

  // Declarations
  unsigned short int i, j, k, l;

  // Definitions
  l = nums1Size + nums2Size;
  i = 0;
  j = 0;
  k = 0;

  // New array to store sorted results
  int arr[l];

  // Fairly standard Merge Sort algorithm to compare elements
  while (i < nums1Size && j < nums2Size) {
    if (nums1[i] <= nums2[j]) {
      arr[k++] = nums1[i++];
    } else {
      arr[k++] = nums2[j++];
    }
  }
 
  // Handle remaining elements in num1
  while (i < nums1Size) {
    arr[k++] = nums1[i++];
  }
 
  // Handle remaining elements in num2
  while (j < nums2Size) {
    arr[k++] = nums2[j++];
  }

  // Grab mean of two middle numbers if even or middle number if odd
  return (l % 2 == 0)
    ? (arr[(l - 1) / 2] + arr[l / 2]) / 2.0
    : arr[l / 2];
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
  int test1[] = {1,3,4,8},
      test2[] = {2,5,6,7,9},
      test3[] = {1,2},
      test4[] = {3,4},
      test5[] = {3},
      test6[] = {-2,-1};

  printf("%f\n", findMedianSortedArrays(test1, 4, test2, 5));
  printf("%f\n", findMedianSortedArrays(test3, 2, test4, 2));
  printf("%f\n", findMedianSortedArrays(test5, 1, test6, 2));
  return 0;
}
