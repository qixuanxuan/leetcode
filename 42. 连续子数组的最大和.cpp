class Solution {
public:
    int maxSubArray(vector<int>& nums) {
		int len = nums.size();
		vector<int> dp(len,nums[0]);
		if(len==1) return nums[0];
		int result = nums[0];
		for(int i=1;i<len;i++){
			dp[i] = max(nums[i],dp[i-1]+nums[i]);
			result = max(result,dp[i]);
		}
		return result;
    }
};