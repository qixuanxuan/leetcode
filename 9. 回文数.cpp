class Solution {
public:
    bool isPalindrome(int x) {
        string xstr = tostring(x);
		if(xstr[0]=='-') return false;
		else{
			int64_t temp = 0;
			for(int i=xstr.size()-1;i>=0;i--){
				temp = temp*10+xstr[i]-'0';
			}
			if(temp==x) return true;
			else return false;
		}
    }
};