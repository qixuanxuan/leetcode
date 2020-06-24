class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {		
		int len= nums.size();
		if(len<=3) return accumulate(nums.begin(),nums.end(),0);
		sort(nums.begin(),nums.end());
		if(accumulate(nums.begin(),nums.begin()+3,0)>=target)
			return accumulate(nums.begin(),nums.begin()+3,0);
		int temp,left,right,DE;
		
		vector<int> result(nums.begin(),nums.begin()+3);
		int MinTemp = abs(target-accumulate(result.begin(),result.begin()+3,0));
		for(int n1=0;n1<=len-3;n1++){
			for(int n2=n1+1;n2<=len-2;n2++){
				temp = target - nums[n1] - nums[n2];
				left = n2+1;
				right = len-1;
				if(nums[left]>temp){
					if((nums[left]-temp)<MinTemp){
						result[0] = nums[n1];
						result[1] = nums[n2];
						result[2] = nums[left];
						MinTemp = nums[left] - temp;
					}
				}
				else if(nums[left]==temp){
					result[0] = nums[n1];
					result[1] = nums[n2];
					result[2] = nums[left];
					return accumulate(result.begin(),result.begin()+3,0);
				}
				else{//nums[left]<temp
					if(nums[right]<temp){
						if(temp - nums[right] < MinTemp){
							result[0] = nums[n1];
							result[1] = nums[n2];
							result[2] = nums[right];
							MinTemp = temp - nums[right];	
						}
					}
					else if(nums[right]==temp){
						result[0] = nums[n1];
						result[1] = nums[n2];
						result[2] = nums[right];
						return accumulate(result.begin(),result.begin()+3,0);
					}
					else{
						while(left<right){
							DE = left+(right-left)/2;
							if(nums[DE]<temp){
								left = DE+1;
							}
							else if (nums[DE]>temp){
								right = DE-1;
							}
							else{
								result[0] = nums[n1];
								result[1] = nums[n2];
								result[2] = nums[DE];
								return accumulate(result.begin(),result.begin()+3,0);
							}
						}
						while(nums[DE]>temp) DE--;
						if(temp - nums[DE]<MinTemp){
							result[0] = nums[n1];
							result[1] = nums[n2];
							result[2] = nums[DE];
							MinTemp = temp - nums[DE];							
						}
						DE++;
						if(nums[DE]-temp<=MinTemp){
							result[0] = nums[n1];
							result[1] = nums[n2];
							result[2] = nums[DE];
							MinTemp = nums[DE] - temp;
						}	
					}
				}
			}
		}
	return accumulate(result.begin(),result.begin()+3,0);	
    }
};


class Solution {
public:
    int threeSumClosest(vector<int>& nums, int target) {		
		int len= nums.size();
		if(len<=3) return accumulate(nums.begin(),nums.end(),0);
		sort(nums.begin(),nums.end());
		if(accumulate(nums.begin(),nums.begin()+3,0)>=target)
			return accumulate(nums.begin(),nums.begin()+3,0);
		int temp,left,right,DE;
		
		vector<int> result(nums.begin(),nums.begin()+3);
		int MinTemp = abs(target-accumulate(result.begin(),result.begin()+3,0));
		for(int n1=0;n1<=len-3;n1++){
			for(int n2=n1+1;n2<=len-2;n2++){
				temp = target - nums[n1] - nums[n2];
				left = n2+1;
				right = len-1;
				if(nums[left]>temp){
					if((nums[left]-temp)<MinTemp){
						result[0] = nums[n1];
						result[1] = nums[n2];
						result[2] = nums[left];
						MinTemp = nums[left] - temp;
					}
				}
				else if(nums[left]==temp){
					result[0] = nums[n1];
					result[1] = nums[n2];
					result[2] = nums[left];
					return accumulate(result.begin(),result.begin()+3,0);
				}
				else{//nums[left]<temp
					if(nums[right]<temp){
						if(temp - nums[right] < MinTemp){
							result[0] = nums[n1];
							result[1] = nums[n2];
							result[2] = nums[right];
							MinTemp = temp - nums[right];	
						}
					}
					else if(nums[right]==temp){
						result[0] = nums[n1];
						result[1] = nums[n2];
						result[2] = nums[right];
						return accumulate(result.begin(),result.begin()+3,0);
					}
					else{
						while(left<right){
							DE = left+(right-left)/2;
							if(nums[DE]<temp){
								left = DE+1;
							}
							else if (nums[DE]>temp){
								right = DE-1;
							}
							else{
								result[0] = nums[n1];
								result[1] = nums[n2];
								result[2] = nums[DE];
								return accumulate(result.begin(),result.begin()+3,0);
							}
						}
						while(nums[DE]>temp) DE--;
						if(temp - nums[DE]<MinTemp){
							result[0] = nums[n1];
							result[1] = nums[n2];
							result[2] = nums[DE];
							MinTemp = temp - nums[DE];							
						}
						DE++;
						if(nums[DE]-temp<=MinTemp){
							result[0] = nums[n1];
							result[1] = nums[n2];
							result[2] = nums[DE];
							MinTemp = nums[DE] - temp;
						}	
					}
				}
			}
		}
	return accumulate(result.begin(),result.begin()+3,0);	
    }
};

