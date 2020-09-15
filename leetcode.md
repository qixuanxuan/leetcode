# 动态规划

## 基本框架

**明确 base case -> 明确「状态」-> 明确「选择」 -> 定义 dp 数组/函数的含义**。

按上面的套路走，最后的结果就可以套这个框架：

```c++
# 初始化 base case
dp[0][0][...] = base
# 进行状态转移
for 状态1 in 状态1的所有取值：
    for 状态2 in 状态2的所有取值：
        for ...
            for 选择 in 选择列表：
            	dp[状态1][状态2][...] = 求最值(选择1，选择2...)
```

### [416. 分割等和子集](https://leetcode-cn.com/problems/partition-equal-subset-sum/)

给定一个**只包含正整数**的**非空**数组。是否可以将这个数组分割成两个子集，使得两个子集的元素和相等。

**注意:**

1. 每个数组中的元素不会超过 100
2. 数组的大小不会超过 200

**示例 1:**

```
输入: [1, 5, 11, 5]

输出: true

解释: 数组可以分割成 [1, 5, 5] 和 [11].
```

**示例 2:**

```
输入: [1, 2, 3, 5]

输出: false

解释: 数组不能分割成两个元素和相等的子集.
```

* **解答**

```c++
class Solution {
private:
    vector<vector<bool>> memo; //dp表格
public:
    bool canPartition(vector<int>& nums) {
      int sum = 0;
      for (auto iter : nums) { sum += iter;};
      if (sum % 2 != 0) {
        return false;
      }
      int target = sum / 2;

      memo = vector<vector<int>>(nums.size() + 1, 
              vector<int>(target + 1, -1)); //初始化memo
      // memo的basecase的情况
      for (int i = 0; i<= target; i++) {
        memo[0][i] = 0;
      }
      for (int i = 0; i <= nums.size(); i++) {
        memo[i][0] = 1;
      }
      
      return dp(nums.size() - 1, target, nums);
    }
    
    bool dp(int K, int target, vector<int>& nums) 
    {
      if (memo[K + 1][target + 1] != -1) {
        return memo[K + 1][target + 1];
      }
      bool res;
      //这里是选择
      if (nums[K] > target) {
        res =  dp(K - 1, target, nums);
      } else {
         //状态转移
        res = dp(K - 1, target, nums) || dp(K - 1, target - nums[K], nums);
      }
      memo[K + 1][target + 1] = res;
      return res;
    }
};
```

