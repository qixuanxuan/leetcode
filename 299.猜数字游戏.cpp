class Solution {
public
    string getHint(string secret, string guess) {
		map<char,int> um;
		int ANums = 0;
		int BNums = 0;
		for(int i=0;i<secret.size();i++){
			um[secret[i]] += 1;
			if(secret[i]==guess[j]) ANums++;
		}
		for(auto &c:guess){
			BNums = BNums + (um[c]-->0);
		}
		BNums = BNums - ANums;
		return to_string(ANums) + "A" + to_string(BNums) + "B";
    }
};