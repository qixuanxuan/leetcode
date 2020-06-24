class Solution
{
private:
    int dpmax(vector<int> &SumCols,int k)
    {
        vector<int> dp(SumCols.size(),0);
        int result;
        dp[0] = SumCols[0];
        result = dp[0];
        for(int i=1; i<SumCols.size(); i++)
        {
            dp[i] = max(dp[i-1]+SumCols[i],SumCols[i]);// 动态规划，dp[i]表示以i结尾的最大子序列的和
            result = max(result,dp[i]);
        }
        if(result<=k) return result;
        
        // result不在k的范围内的时候 暴力求解最大子序列的和
        result = INT_MIN;
        for (int l = 0; l < SumCols.size(); l++)
        {
            int sum = 0;
            for (int r = l; r < SumCols.size(); r++)
            {
                sum += SumCols[r];
                if (sum > result && sum <= k) result = sum;
                if (result == k) return k;
            }
        }
        return result;
    }
public:
    int maxSumSubmatrix(vector<vector<int>>& matrix, int k)
    {
        int rows = matrix.size();
        int cols = matrix[0].size();
        int mmax = INT_MIN;
        if(rows==0) return 0;
        if(cols==0) return 0;

        for(int l=0; l<cols; l++)
        {
            vector<int> SumCols(rows,0);
            for(int r=l; r<cols; r++)
            {
                for(int i=0; i<rows; i++)
                {
                    SumCols[i] = SumCols[i] + matrix[i][r];
                }
                int temp = dpmax(SumCols,k);
                if(temp<=k){
                    mmax = max(mmax,temp);
                }
            }
        }
        return mmax;
    }
};
