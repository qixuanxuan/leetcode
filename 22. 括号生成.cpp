class Solution {
public:
    vector<string> generateParenthesis(int n) {
        vector<string> result;
		GePa(result,"",n,0,0);
		return result;
    }
    void GePa(vector<string>& result,string path,int n,int L,int R) {
        if(L>n || R>n || R>L) return;
		if(L==n && L==R){
			result.push_back(path);
			return;
		} 
		GePa(result,path+'(',n,L+1,R); 
		GePa(result,path+')',n,L,R+1); 
    }
	
};



