class Solution {
public:
    vector<vector<int>> queensAttacktheKing(vector<vector<int>>& queens, vector<int>& king) {
		vector<vector<int>> result(8);
		vector<int> dis(8,INT_MAX);
		int len = queens.size();
		int left,right;
		for(int i=0;i<len;i++){
			left = queens[i][0] - king[0];
			right = queens[i][1] - king[1];
			if(left==0 && right<0){
				if(left-right<dis[0]){
					result[0] = queens[i];
					dis[0] = left-right;
				}
			}
			else if(left==0 && right>0){
				if(left+right<dis[1]){
					result[1] = queens[i];
					dis[1]= left+right;
				}				
			}
			else if(left>0 && right==0){
				if(left<dis[2]){
					result[2] = queens[i];
					dis[2] = left;
				}				
			}
			else if(left<0 && right==0){
				if(-left<dis[3]){
					result[3] = queens[i];
					dis[3] = -left;
				}				
			}
			else if(left<0 && right>0 && -left==right){
				if(-left+right<dis[4]){
					result[4] = queens[i];
					dis[4] = -left+right;
				}				
			}		
			else if(left<0 && right<0 && -left==-right){
				if(-left-right<dis[5]){
					result[5] = queens[i];
					dis[5] = -left-right;
				}				
			}
			else if(left>0 && right>0 && left==right){
				if(left+right<dis[6]){
					result[6] = queens[i];
					dis[6] = left+right;
				}				
			}
			else if(left>0 && right<0 && left==-right){
				if(left-right<dis[7]){
					result[7] = queens[i];
					dis[7] = left-right;
				}				
			}	
			else{
				continue;
			}
		}
		int j=0;
		for(int i=0;i<8;i++){
			if(dis[i]==INT_MAX){
				result.erase(result.begin()+i-j);
				j++;
			}
		}
		return result;
    }
};