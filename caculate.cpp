// regex_search example
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
using namespace std;

#include <string>
#include <vector>
class Solution {
public:
    bool IsDigital(char x) {
        if (x >= '0' && x <= '9') {
            return true;
        } else {
            return false;
        }
    }
    int calculate(string s) {
        s.erase(s.find_last_not_of(' ') + 1);
        s.erase(0, s.find_first_not_of(' '));
        char sign = '+';
        int num = 0;
        vector<int> stackNum;
        for (int i = 0; i < s.size(); i++) {

            if (IsDigital(s[i])) {
                num = num * 10 + (s[i] - '0');
            }


             if (!IsDigital(s[i]) && s[i] != ' ' || i == s.size() - 1){
                int tmp;
                switch (sign)
                {
                    case '+':
                        stackNum.push_back(num);
                        break;
                    case '-':
                        stackNum.push_back(-num);
                        break;
                    case '*':
                        tmp = stackNum.back();
                        stackNum.pop_back();
                        stackNum.push_back(tmp * num);
                        break;
                    case '/':
                        tmp = stackNum.back();
                        stackNum.pop_back();
                        stackNum.push_back(tmp / num);
                        break;
                }
                sign = s[i];
                num = 0;
            }
        }
        int res = 0;
        while (!stackNum.empty()) {
            res += stackNum.back();
            stackNum.pop_back();
        }
        return res;
    }
};


int main ()
{
    Solution M;
    int res = M.calculate(" 3+5 / 2 ");
    cout << res << endl;
    return 0;
}
