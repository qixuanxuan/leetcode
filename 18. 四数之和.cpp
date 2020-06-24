class Solution {
public:
    vector<vector<int>> fourSum(vector<int>& nums, int target) {
		sort(nums.begin(),nums.end());
		vector<vector<int>> result;
		int len = nums.size();
		if(len<4) return result;
		if(len==4){
			if(accumulate(nums.begin(),nums.end(),0)==target){
				result.push_back(nums);
				return result;				
			}
			else{
				return result;
			}
		}
		int TargetTemp;
		int n3,n4;
		for(int n1=0;n1<=len-4;n1++){
			if(n1>0 && nums[n1]==nums[n1-1])
				continue;//确保nums[n1] 改变了
			for(int n2=n1+1;n2<=len-3;n2++){
				if(n2>n1+1 && nums[n2]==nums[n2-1])
					continue;//确保nums[n2] 改变了
				TargetTemp = target - nums[n1] - nums[n2];
				n3 = n2+1;
				n4 = len-1;
				while(n3<n4){
					if(nums[n3]+nums[n4]<TargetTemp) n3++;
					else if(nums[n3]+nums[n4]>TargetTemp) n4--;
					else{
						result.push_back({nums[n1],nums[n2],nums[n3],nums[n4]});
						while(n3<n4 && nums[n3]==nums[n3+1])
							n3++;//确保nums[n3] 改变了
						n3++;
						while(n3<n4 && nums[n4]==nums[n4-1])
							n4--;//确保nums[n4] 改变了
						n4--;
					}
				}
			}
		}
        return result;
    }
};