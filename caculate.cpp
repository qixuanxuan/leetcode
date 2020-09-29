// regex_search example
#include <iostream>
#include <string>
#include <unordered_map>
#include <regex>
using namespace std;

#include <string>
#include <vector>
#include <sstream>
class Solution {
private:
    vector<string> res;
public:
    bool IsOkIp(string a)
    {
        stringstream tmp;
        if (a.empty()) {
            return false;
        }
        if (a.size() > 1 && a[0] == '0') {
            return false;
        }
        int intA;
        tmp << a;
        tmp >> intA;
        if (intA >= 0 && intA <= 255) {
            return true;
        } else {
            return false;
        }
        
    }
    void dfs(vector<string> &tmp, string s, int start)
    {
        if (tmp.size() == 4) {
            string tmpI;
            for (auto iter : tmp) {
                tmpI += iter;
                tmpI += ".";
            }
            tmpI.pop_back();
            res.push_back(tmpI);
            return;
        }
        for(int i = start; i < s.size(); i++) {
            string sTmp = s.substr(start, i - start + 1);
            if (!IsOkIp(sTmp) || 
                (s.size() - 1 - i) < (4 - res.size())) {
                break;
            }
            tmp.push_back(sTmp);
            dfs(tmp, s, i + 1);
            tmp.pop_back();
        }
    }
    vector<string> restoreIpAddresses(string s) {
        vector<string> tmp;
        dfs(tmp, s, 0);
        return res;
    }
};

int main ()
{
    Solution M;
    vector<string> res = M.restoreIpAddresses("0000");
    for (auto iter : res) {
        cout << iter << endl;
    }
    return 0;
}
