#include <vector>
#include <iostream>
#include <unordered_set>


namespace FirstRecurringCharacter
{

class Solution {
public:

    /**
     * UsingHashSet
     * - Time complexity: O(n)
     * - Space complexity: O(n)
    */
    int getFirstRecurringCharacter_HashSet(const std::vector<int>& nums) {

        if (nums.empty() || nums.size() == 1) {
            return -1;
        }

        std::unordered_set<int> numsCopy;
        for (int num : nums) {
            // Check if element is already available in the HashSet
            if (numsCopy.count(num) > 0) {
                return num;
            }
            numsCopy.emplace(num);
        }

        return -1;
    }

    /**
     * UsingHashSet
     * - Time complexity: O(n^2)
     * - Space complexity: O(1)
    */
    int getFirstRecurringCharacter_BruteForce(const std::vector<int>& nums) {

        if (nums.empty() || nums.size() == 1) {
            return -1;
        }

        int length = static_cast<int>(nums.size());
        
        // first: num
        // second: distance 
        std::pair<int, int> firstRecurringCharacter = {0, -1};

        for (int i=0; i< length; i++) {
            int numBase = nums[i];
            for (int j=i+1; j<length; j++) {
                int num = nums[j];
                if (numBase == num) {
                    int distance = j-i;
                    if ((firstRecurringCharacter.first > distance) || (firstRecurringCharacter.first == 0)) {
                        firstRecurringCharacter = {distance, num};
                    }
                // std::cout << "num: " << firstRecurringCharacter.second << " distance to duplicate: " << firstRecurringCharacter.first << std::endl;
                }
            }
        }

        return firstRecurringCharacter.second;
    }


};

/**
 * Google question
 * Given an array = [2, 5, 1, 2, 3, 5, 1, 2, 4]
 * It should return 2
 * 
 * Given an array = [2, 1, 1, 2, 3, 5, 1, 2, 4]
 * It should return 1
 * 
 * Given an array = [2, 3, 4, 5]
 * It should return -1
 * 
 */
void test() {

    Solution sol;

    std::vector<int> array1 = {2, 5, 1, 2, 3, 5, 1, 2, 4};
    std::vector<int> array2 = {2, 1, 1, 2, 3, 5, 1, 2, 4};
    std::vector<int> array3 = {2, 3, 4, 5};


    std::cout << "HashSet solution:" << std::endl;
    std::cout << "- array1 -> " << sol.getFirstRecurringCharacter_HashSet(array1) << std::endl;
    std::cout << "- array2 -> " << sol.getFirstRecurringCharacter_HashSet(array2) << std::endl;
    std::cout << "- array3 -> " << sol.getFirstRecurringCharacter_HashSet(array3) << std::endl;    

    std::cout << "Brute force solution:" << std::endl;
    std::cout << "- array1 -> " << sol.getFirstRecurringCharacter_BruteForce(array1) << std::endl;
    std::cout << "- array2 -> " << sol.getFirstRecurringCharacter_BruteForce(array2) << std::endl;
    std::cout << "- array3 -> " << sol.getFirstRecurringCharacter_BruteForce(array3) << std::endl;  

}

}