class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& T) {
		stack<int> s;	
		int len = T.size();
		vector<int> result(len,0);
		if(len==1) return result;
		result[len-1] = 0;
		s.push(len-1);
		for(int i=len-2;i>=0;i--){
			while(1){
				if(s.empty()){
					result[i] = 0;
					s.push(i);
					break;
				}
				else{
					if(T[i]<T[s.top()]){
						result[i] = s.top()-i;
						s.push(i);
						break;
					}
					else{
						s.pop();
					}
				}

			}
		}
		return result;
	}
};