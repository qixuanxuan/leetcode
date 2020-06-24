class Solution {
public:
    bool checkPossibility(vector<int>& nums) {
		int count = 0;
		if(nums.size()==1) return true;
		for(int i=0;i<nums.size()-1;i++){
			if(nums[i]>nums[i+1]){
				if(i==0){
					count++
				}
				else if(i==nums.size()-2){
					count++
				}
				else{
					if(nums[i-1]<=nums[i+1] || nums[i]<=nums[i+2])
						count++
					else
						return false;
				}
			}
			
			if(count>1) return false;
		}
        return true;
    }
};