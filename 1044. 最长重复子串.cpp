class Solution {
public:
    string longestDupSubstring(string S) {
        int N = S.size();
		unsigned int modulus = UINT_MAX ;
		int a = 26;
		vector<int> nums(N);
		for(int i=0;i<N;i++){
			nums[i] = S[i] - 'a';
		}
		int left = 1;
		int right = N;
		int L;
		while(left!=right){
			L = left + (right-left)/2;
			if(isRepeat(L,N,modulus,a,nums)!=-1) left = L+1;
			else right = L;
			
		}
		int start = isRepeat(left-1,N,modulus,a,nums);
		return start != -1 ? S.substr(start, left - 1) : "";
		
    }
private:
	int isRepeat(int L,int N, unsigned int modulus,int a,vector<int> nums){
		unsigned int h = 0;
		unordered_set<unsigned int> RepeatSet;
		for(int i=0;i<L;i++){
			h = (h*a) % modulus +  nums[i]; 
		}
		RepeatSet.insert(h);
		unsigned int aL = 1;
		for(int i=1;i<=L;i++) aL = (aL*a) % modulus;
		for(int start=1;start<N-L+1;start++){
			h = h * a % modulus - nums[start - 1] * aL % modulus + nums[start + L - 1];
			if(RepeatSet.find(h)!=RepeatSet.end()) return start;
			RepeatSet.insert(h);
		}
		return -1;
		
	}
};