class Solution {
public:
    string longestCommonPrefix(vector<string>& strs) {
        int len = strs.size();
		if(len==0) return "";
		if(len==1) return strs[0];
		string dp = strs[0];
		int SameLen = dp.size();
		for(int i=1;i<len;i++){
			while(1){
				if(strs[i].substr(0,SameLen)==dp.substr(0,SameLen)){
					break;
				}
				else{
					SameLen--;
					if(SameLen==0)
						return "";
				}
			}
		}
		return dp.substr(0,SameLen);
		
    }
};