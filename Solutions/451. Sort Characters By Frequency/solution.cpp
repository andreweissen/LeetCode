/**
 * solution.cpp
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @version 1.0
 */

#include <iostream>
#include <queue>
#include <unordered_map>
#include <utility>
#include <vector>

class Solution {
 public:
  /**
   * The author's original implementation only made use of a <code>vector</code>
   * and an <code>unordered_map</code>, and sorted by means of a
   * <code>static</code> helper function. However, subsequent tests indicated
   * that the use of a <code>priority_queue</code> and exclusion of a helper
   * improved performance considerably on the order of ten ms, though memory
   * perfomance suffered accordingly. 
   * <br />
   * <br />
   * At the time of its submission, this implementation was found to be faster
   * than 97% of C++ implementations with a runtime of 8ms and more efficient in
   * terms of memory usage than 37% of C++ implementations. 
   *  
   * @param s <code>std::string</code> input string
   * @return <code>string</code> constituting the order by letter frequency
   */
  std::string frequencySort(std::string s) {
    
    // Declarations
    int i, len;
    std::string output;

    // Declare HashMap for letter/number-of-appearances-in-string pairs
    std::unordered_map<char, int> letterMap;

    // Lambda for sorting queue entries by frequency with which letter appears
    auto lesser = [](std::pair<char, int> a, std::pair<char, int> b) {
      return a.second < b.second;
    };

    // Declare priority queue sorted by letter frequency
    std::priority_queue<std::pair<char, int>, std::vector<std::pair<char, int>>,
      decltype(lesser)> occurrences(lesser);

    // Definitions
    len = (int) s.length();
    output = "";

    // For each letter in the string, update associated number of appearances
    for (i = 0; i < len; i++) {
      letterMap[s[i]]++;
    }

    // Move letter/appearance pairs into frequency-sorted priority queue
    for (auto letterPair : letterMap) {
      occurrences.push(letterPair);
    }

    // Iterate through queue, adding to output as many of each letter as appear
    while (!occurrences.empty()) {
      for (i = 0; i < occurrences.top().second; i++) {
        output += occurrences.top().first;
      }

      occurrences.pop();
    }

    return output;
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
    "tree",
    "cccaaa",
    "Aabb"
  };

  // Number of test cases
  len = sizeof(testCases) / sizeof(*testCases);

  // Run test cases and print to console on individual lines
  for (i = 0; i < len; i++) {
    std::cout << solution.frequencySort(testCases[i]) << std::endl;
  }

  return 0;
}
