/**
 * solution.cpp
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @version 1.0
 */
#include <iostream>

class Solution {
 public:

  /**
   * Though the author's first attempts at this problem involved the use of
   * involved data structures like <code>map</code>s and <code>vector</code>s to
   * produce a clunky working model, he discovered that he could reduce the time
   * complexity considerably by simply making use of an <code>int</code> array
   * in which each index is associated with a specific alphabetical character.
   * <br />
   * <br />
   * At the time of its submission, this implementation was found to be faster
   * than 86% of C++ implementations with a runtime of 24ms and more efficient
   * in terms of memory usage than 68% of C++ implementations. 
   *  
   * @param s <code>std::string</code> input string
   * @return <code>int</code>, index of the first unique character 
   */
  int firstUniqChar(std::string s) {

    // Declarations
    int i, len;
    int occurrences[26];
    char letter;

    // Instantiate new array containing zeroes only
    occurrences[26] = {0};

    // Cache input string length
    len = (int) s.length();

    // Iterate over string's chars, keeping track of instances of each
    for (i = 0; i < len; i++) {
      letter = s[i];
      occurrences[letter - 'a'] = occurrences[letter - 'a'] + 1;
    }

    // Check to see which unique character comes first in the string
    for (i = 0; i < len; i++) {
      if (occurrences[s[i] - 'a'] == 1) {
        return i;
      }
    }

    // Return -1 if no unique characters exist in the string
    return -1; 
  }
};

/**
 * <code>main</code> serves as the example driver for the exercise and runs a
 * few of the test cases supplied on the LeetCode website to permit the solution
 * to be tested offsite.
 *
 * @return <code>int</code>
 */
int main() {

  // Declarations
  int i, len;

  // Instantiate new Solution class instance
  Solution solution;

  // Define test cases
  std::string testCases[] = {
    "leetcode",
    "loveleetcode",
    "aabb"
  };

  // Number of test cases
  len = sizeof(testCases) / sizeof(*testCases);

  // Run test cases and print to console on individual lines 
  for (i = 0; i < len; i++) {
    std::cout << solution.firstUniqChar(testCases[i]) << std::endl;
  }

  return 0;
}
