class Solution {
public:
    string minWindow(string s, string t) {
        unordered_map<char,int> SCount,TCount;
		string res;
		for(auto &c:t) TCount[c]++;
		int LenS = s.size();
		int LenT = t.size();
		int Left = 0,Right = 0,count = 0,QuJianMax = INT_MAX;
		while(Right<=LenS){
            char c = s[Right];
            SCount[c]++;
			if(TCount.count(c) && SCount[c]<=TCount[C]){
				count++;
			}
			while(Left<=Right && count==LenT){
				if(Right-Left+1<QuJianMax){
					QuJianMax = Right - Left + 1;
					res = s.substr(Left,QuJianMax);
				}
				c = s[Left];
				SCount[c]--;
				if(TCount.count(c) && SCount[c]<TCount[c]){
					count--;
				}
				Left++;
			}
			Right++;
		}
		return res;
    }
};