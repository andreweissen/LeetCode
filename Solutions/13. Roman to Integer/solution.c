/**
 * @file solution.c
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @date 10 September 2021
 * @brief A C-based solution to LeetCode question 13
 */

#include <stdio.h>

/**
 * @brief This function serves as an ancillary helper utility function for the
 * <code>romanToInt2</code> function. As its name implies, it evaluates the
 * <code>char</code> Roman numeral passed as an argument and returns the
 * <code>int</code> equivalent. Though the LeetCode question guarantees that
 * input test cases will all be wellformed, the function still makes use of a
 * <code>default</code> case to catch character input that are not Roman
 * numerals.
 *
 * @param numeral char A Roman numeral to be evaluated
 * @return unsigned short int The numeral's associated value
 */
unsigned short int calcValue(char numeral) {
  switch(numeral) {
    case 'M': return 1000;
    case 'D': return 500;
    case 'C': return 100;
    case 'L': return 50;
    case 'X': return 10;
    case 'V': return 5;
    case 'I': return 1;
    default: return 0;
  }
}

/**
 * @brief A revised approach to the author's first submission aimed at both
 * reducing time complexity and memory usage, this implementation makes use of a
 * helper function and dispenses with some of the storage variables used in the
 * first implementation in favor of a clearer, more idiomatic approach. It saves
 * .1 MB of memory over its predecessor, propelling it into the top 7% of C
 * submissions, but takes a millisecond longer than the original approach. 
 * <br />
 * <br />
 * As stated below, in retrospect, a more nuanced and likely faster approach
 * would have been to include a <code>switch</code> in the body of the main
 * functionality loop to determine if the current <code>char</code> and the
 * following <code>char</code> together constitute one of the six edge cases
 * (IV, IX, XL, XC, CD, and CM) that require a different approach. The current
 * approach used in this implementation and the alternate likewise included in
 * the file are a bit less efficient than an approach that explicitly looks for
 * the edge cases from the outset.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 58% of all C implementations with a runtime of 8 ms and more efficient
 * in terms of memory usage than 93% of C implementations with a memory usage
 * of 5.7 MB. 
 *
 * @param s char* The Roman numeral string to be parsed
 * @return int The associated value of the numeral as an <code>int</code>
 */
int romanToInt2(char * s) {

  // Declarations
  unsigned short int len, sum, current, former;
  char * p_s;

  // Definitions
  p_s = s;
  len = 0;

  // Determine string length w/o call to strlen
  while (*p_s) len++, p_s++;

  if (len == 0) {
    return 0;
  } else if (len == 1) {
    return calcValue(*s);
  } else {
    sum = 0;
    p_s = s;

    while (*p_s) {
      current = calcValue(*p_s);
       
      // If the previous numeral is of a lesser value...
      if (p_s != s && (former = calcValue(*(p_s - 1))) < current) {

        // ...subtract from accumulated total...
        sum -= former;

        // ...and subtract from present numeral's value
        current -= former;
      }

      // Add this value to the accumulator
      sum += current;
      p_s++;
    }

    return sum;
  }
}

/**
 * @brief The first of the author's two submitted approaches to the problem,
 * this implementation makes use of a simple <code>for</code>
 * loop/<code>switch</code> statement pairing to determine the value of the
 * current Roman numeral <code>char</code>, adding the associated value to the
 * <code>sum</code> accumulator, and adjusting for any of the six edge cases
 * that require subtraction (IV, IX, XL, XC, CD, and CM). 
 * <br />
 * <br />
 * As stated above, in retrospect, a more nuanced and likely faster approach
 * would have been to include a <code>switch</code> in the body of the main
 * functionality loop to determine if the current <code>char</code> and the
 * following <code>char</code> together constitute one of the six edge cases
 * (IV, IX, XL, XC, CD, and CM) that require a different approach. The current
 * approach used in this implementation and the alternate likewise included in
 * the file are a bit less efficient than an approach that explicitly looks for
 * the edge cases from the outset.
 * <br />
 * <br />
 * At the time of its submission, this implementation was found to be faster
 * than 60% of all C implementations with a runtime of 7 ms and more efficient
 * in terms of memory usage than 61% of C implementations with a memory usage
 * of 5.8 MB. 
 *
 * @param s char* The Roman numeral string to be parsed
 * @return int The associated value of the numeral as an <code>int</code>
 */
int romanToInt(char * s) {

  // Declarations (15 alludes to the question's restriction on input size)
  unsigned short int i, sum, a[15];

  for (i = 0, sum = 0; *s; i++) {
    switch(*s++) {
      case 'M':
        a[i] = 1000;
        break;
      case 'D':
        a[i] = 500;
        break;
      case 'C':
        a[i] = 100;
        break;
      case 'L':
        a[i] = 50;
        break;
      case 'X':
        a[i] = 10;
        break;
      case 'V':
        a[i] = 5;
        break;
      case 'I':
        a[i] = 1;
        break;
      default:
        a[i] = 0;
    }

    // If the previous numeral is of a lesser value...
    if (i != 0 && a[i - 1] < a[i]) {

      // ...subtract from accumulated total...
      sum -= a[i - 1];

      // ...and subtract from present numeral's value
      a[i] -= a[i - 1];
    }

    // Add this value to the accumulator
    sum += a[i];
  }

  return sum;
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
  int i, len;
  char * test;

  // Roman numeral cases (all wellformed per question constraints)
  char * testCases[] = {
    "V",
    "III",
    "IV",
    "IX",
    "LVIII",
    "MCMXCIV"
  };

  len = sizeof(testCases) / sizeof(*testCases);
  for (i = 0; i < len; i++) {
    test = testCases[i];
    printf("Func 1: %d\nFunc 2: %d\n", romanToInt(test), romanToInt2(test));
  }

  return 0;
}
