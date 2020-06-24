class Solution {
public:
    int findBestValue(vector<int>& arr, int target) {
		sort(arr.begin(),arr.end());
		int len = arr.size();
		if(len==1){
			if(arr[0]>=target) return target;
			else return arr[0];
		}
		int start = arr[0];
		int TempSum = len*start;
		int AbsDis;
		int dp;
		if(TempSum<=target) dp = arr[0];
		else{
			while(1){
				AbsDis = abs(TempSum - target); 
				start--;
				TempSum = len*start;
				if(abs(TempSum - target)>AbsDis){
					return ++start;
				}
				
			}
		}
		
		for(int i=1;i<len;i++){
			start = arr[i];
			TempSum = dp + (len-i)*start;
			if(TempSum<=target){
				dp = dp + arr[i];
			}
			else{
				while(1){
					AbsDis = abs(TempSum - target);
					start--;
					if(start==arr[i-1]){
						TempSum = dp-arr[i-1] + (len-i+1)*start;
					}
					else{
						TempSum = dp + (len-i)*start;
					}
					if(abs(TempSum - target)>AbsDis){
						return ++start;
					}	
				}

			}			
		}
		return arr[len-1];
    }
};