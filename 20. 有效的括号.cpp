class Solution {
public:
    bool isValid(string s) {
		stack<char> p;
		int len = s.size();
		if(len==0){
			return true;
		}
		if(len%2==1)
			return false;
		p.push(s[0]);
		for(int i=1;i<len;i++){
			if(isLeft(s[i]))
				p.push(s[i]);
			else{
				if(isSame(p.top(),s[i])) p.pop();
				else{
					return false;
				}
			}	
		}
		if(p.empty()) return true;
		else return false;	
    }
	bool isLeft(char s){
		switch(s){
			case '{': return true;
			case '[': return true;
			case '(': return true;
			default : return false;
		}
	}
    bool isSame(char a,char b){
        switch(a){
            case '{': return b=='}';
            case '[': return b==']';
            case '(': return b==')';
            default : return false;
        }
    }
};