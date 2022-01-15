#include <string>
#include <vector>
#include <iostream>

#include <cctype>

namespace LongestWord
{

/**
 * O(n) solution 
*/ 
const std::string getLongestWord(const std::string& sentence) {

    if (sentence.empty()) { return ""; }

    std::string longestWord = "";

    int length = static_cast<int>(sentence.size());
    int startIdx = -1;
    int counter = 0;

    for (int i=0; i<length; i++) {
        
        bool alNum = std::isalnum(sentence[i]);
        if (alNum) {
            
            startIdx = (startIdx == -1) ? i : startIdx;
            counter++;

            if (i < (length-1)) { continue; }
        }

        // Not a letter neither a number
        if (counter > static_cast<int>(longestWord.size())) {
            longestWord = sentence.substr(startIdx, counter);
        }

        //Reset values
        startIdx = -1;
        counter = 0;
    }

    return longestWord;
}

/**
 * Have the function LongestWord(sen) take the sen parameter
 * being passed and return the longest word in the string. 
 * If there are two or more words that are the same length, 
 * return the first word from the string with that length. 
 * Ignore punctuation and assume sen will not be empty. 
 * Words may also contain numbers, for example "Hello world123 567"
 * 
 * Example 1:
 * - Input: "fun&!! time"
 * - Output: time
 * 
 * Example 2:
 * - Input:"I love dogs"
 * - Output: love
 * 
 */

void test() {

    {
    const std::string sentence = "fun&!! time";
    std::cout << "The longest word is: " << getLongestWord(sentence) << std::endl;
    }

    {
    const std::string sentence = "I love dogs";
    std::cout << "The longest word is: " << getLongestWord(sentence) << std::endl;
    }

}

}