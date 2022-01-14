#include <iostream>
#include <string>

namespace ReverseStringR
{

class ReverseString
{
public:
    ReverseString() :
        reversedStr_({})
    {}

    const std::string reverse(const std::string& str) {
        if (str.empty() || str.size() == 1) {
            return str;
        }

        size_t lastIdx = str.size() - 1;
        const char last = str[lastIdx];
        const std::string substr(str.c_str(), (str.size()-1));

        return last + reverse(substr);
    }

    const std::string reverse2(const std::string& str) {
        if (str.empty()) {
            return str;
        }

        reversedStr_ = {};
        reversedStr_.reserve(str.size());
        int lastIdx = static_cast<int>(str.size());
        reverse2_helper(str, lastIdx);
        const std::string result(reversedStr_.data(), reversedStr_.size());

        return result;
    }

private:
    std::vector<char> reversedStr_;

    void reverse2_helper(const std::string& str, int index) {
        // Not tail call optimization
        if (index < 1) {
            reversedStr_.push_back(str[0]);
            return;
        }

        reversedStr_.push_back(str[index--]);
        // Tail call optimization?
        reverse2_helper(str, index);
    }

};

}