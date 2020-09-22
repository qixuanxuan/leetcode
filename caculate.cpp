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
    string shortestPalindrome(string s) {
        int left = 0;
        int right =0;
        int mux = 1;
        int base = 131;
        int mod = 1000000007;
        int best;
        int n = s.size();
        for (int i = 0; i < s.size(); i++) {
            left = ((long long) left * base + s[i]) % mod;
            right = (right + (long long)mux * s[i]) % mod;
            if (left == right) {
                best = i;
            }
            mux = ((long long) base * mux) % mod;
        }
        string add = (best == s.size() - 1) ? "" : s.substr(best + 1, n);
        reverse(add.begin(), add.end());
        return add + s;
    }
};

int main ()
{
    Solution M;
    int res = M.calculate(" 3+5 / 2 ");
    cout << res << endl;
    return 0;
}
