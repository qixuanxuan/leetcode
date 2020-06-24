class Solution {
public:
    int translateNum(int num) {
		string snum = to_string(num);
		int len = snum.size();
		if(len==0) return 0;
		if(len==1) return 1;
		string StrEndOf2 = snum.substr(len-2,2);
		string StrEndOf1;
		int temp = atoi(StrEndOf2.c_str());
		StrEndOf2 = snum.substr(0,len-2);
		StrEndOf1 = snum.substr(0,len-1);
		if(temp<=25)
			return translateNum(atoi(StrEndOf2.c_str()))+translateNum(atoi(StrEndOf1.c_str()));
		else
			return translateNum(atoi(StrEndOf1.c_str()));
    }
};