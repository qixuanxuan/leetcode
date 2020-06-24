class Solution {
public:
int maxFreq(string s, int maxLetters, int minSize, int maxSize) {
        
    unordered_map<string, int> occur;
    unordered_map<char, int> temp;
	int OccurNums = 0,result=0;
	for(int i=0;i<minSize;i++){
		temp[s[i]]++;
		if(temp[s[i]]==1) OccurNums++;
	}
	if(OccurNums<=maxLetters){
		occur[s.substr(0,minSize)]++;
		result = max(result,occur[s.substr(0,minSize)]);
	}
	int i = 0;
	int j = minSize;
	while(j<s.size()){
		temp[s[i]]--;
		if(temp[s[i]]==0) OccurNums--;
		temp[s[j]]++;
		if(temp[s[j]]==1) OccurNums++;
		if(OccurNums<=maxLetters){
			occur[s.substr(i+1,minSize)]++;
			result = max(result,occur[s.substr(i+1,minSize)]);
		}
		i++;
		j++;
	}
	return result;
}
};

