/**
 * solution.cpp
 * @author Andrew Eissen <andrew@andreweissen.com>
 * @version 1.0
 */

#include <iostream>
#include <unordered_map>
#include <vector>

class Solution {
 public:
  /**
   * In accordance with the ancient developers' wisdom "when in doubt, throw a
   * hashmap at the problem," this implementation makes use of a standard
   * <code>unordered_map</code> to keep track of previously encountered
   * <code>int</code>s present in the input vector. This ensures the runtime
   * remains <code>O(n)</code> in total and O(1) for map access.
   * <br />
   * <br />
   * At the time of its submission, this implementation was found to be faster
   * than 95% of C++ implementations with a runtime of 8ms and more efficient in
   * terms of memory usage than 40% of C++ implementations with 10.8 MB. 
   *  
   * @param nums <code>std::vector<int></code> Input vector of ints
   * @param target <code>int</code> The desired number sum
   * @return results <code>std::vector</code> Num indices that form target 
   */
  std::vector<int> twoSum(std::vector<int>& nums, int target) {

    // Declarations
    int i, needed;
    std::unordered_map<int, int> minMap;
    std::vector<int> results;

    for (i = 0; i < nums.size(); i++) {

      // Desired number to form target with presently viewed number
      needed = target - nums[i];

      // Check if this number is in the container map
      if (minMap.find(needed) != minMap.end()) {
        results.push_back(minMap[needed]);
        results.push_back(i);
        break;
      }

      // Add to container map for future O(1) access
      minMap[nums[i]] = i;
    }

    return results;
  }
};
