



# 动态规划

## 基本框架

**明确 base case -> 明确「状态」-> 明确「选择」 -> 定义 dp 数组/函数的含义**。

按上面的套路走，最后的结果就可以套这个框架：

* 框架1

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

* 框架2


	```c++
	dict memo();
	dp(状态1，状态2，...)
	{
		if (memo[状态1，状态2，...] 存在)：
			return memo[状态1，状态2，...]
		for 选择 in 选择列表：
			res = 求最值(dp--选择1，dp--选择2...)
		memo(状态1，状态2，...) = res;
		return res;
	}
	```


​	

## [ 分割等和子集](https://leetcode-cn.com/problems/partition-equal-subset-sum/)

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

# 哈希表---获取无序元素存储位置

[ 两数之和](https://leetcode-cn.com/problems/two-sum/)

给定一个整数数组 `nums` 和一个目标值 `target`，请你在该数组中找出和为目标值的那 **两个** 整数，并返回他们的数组下标。

你可以假设每种输入只会对应一个答案。但是，数组中同一个元素不能使用两遍。

**示例:**

```c++
给定 nums = [2, 7, 11, 15], target = 9

因为 nums[0] + nums[1] = 2 + 7 = 9
所以返回 [0, 1]
```

* 解答

  ```c++
  using namespace std;
  class Solution {
  public:
      vector<int> twoSum(vector<int>& nums, int target) {
          unordered_multimap<int, int> index;
          // 最重要的是用数值为key用下标索引为value
          for (int i = 0; i < nums.size(); i++) {
              index.insert({nums[i], i});
          }
          for (int iter = 0; iter < nums.size(); iter++) {
              int deByTarget = target - nums[iter];
              if (deByTarget == nums[iter]) {
                  auto pr = index.equal_range(nums[iter]);
                  while (pr.first != pr.second) {
                      if (pr.first->second != iter) {
                          return {iter,pr.first->second};
                      }
                      pr.first++;
                  }
              } else {
                  if (index.count(deByTarget) != 0) {
                      return {iter,index.find(deByTarget)->second};
                  }
              }
          }
          return {-1,-1};
      }
  };
  ```

# 位操作

  

```c++
# 大小写转小写
('a' | ' ') = 'a'
('A' | ' ') = 'a'
# 小写转大写
('a' & '_') = 'A'
('A' & '_') = 'A'
# 大小写转换
('d' ^ ' ') = 'D'
('D' ^ ' ') = 'd'
# 消除最后一个1    
n & (n - 1) 
# 异或操作 
a ^ a = 0
a ^ 0 = a
```



# LCU缓存

很多编程语言都有内置的哈希链表或者类似 LRU 功能的库函数，但是为了帮大家理解算法的细节，我们先自己造轮子实现一遍 LRU 算法，然后再使用 Java 内置的 `LinkedHashMap` 来实现一遍。

首先，我们把双链表的节点类写出来，为了简化，`key` 和 `val` 都认为是 int 类型：



```java
class Node {
    public int key, val;
    public Node next, prev;
    public Node(int k, int v) {
        this.key = k;
        this.val = v;
    }
}
```

然后依靠我们的 `Node` 类型构建一个双链表，实现几个 LRU 算法必须的 API：



```java
class DoubleList {  
    // 头尾虚节点
    private Node head, tail;  
    // 链表元素数
    private int size;

    public DoubleList() {
        // 初始化双向链表的数据
        head = new Node(0, 0);
        tail = new Node(0, 0);
        head.next = tail;
        tail.prev = head;
        size = 0;
    }

    // 在链表尾部添加节点 x，时间 O(1)
    public void addLast(Node x) {
        x.prev = tail.prev;
        x.next = tail;
        tail.prev.next = x;
        tail.prev = x;
        size++;
    }

    // 删除链表中的 x 节点（x 一定存在）
    // 由于是双链表且给的是目标 Node 节点，时间 O(1)
    public void remove(Node x) {
        x.prev.next = x.next;
        x.next.prev = x.prev;
        size--;
    }

    // 删除链表中第一个节点，并返回该节点，时间 O(1)
    public Node removeFirst() {
        if (head.next == tail)
            return null;
        Node first = head.next;
        remove(first);
        return first;
    }

    // 返回链表长度，时间 O(1)
    public int size() { return size; }

}
```

到这里就能回答刚才「为什么必须要用双向链表」的问题了，因为我们需要删除操作。删除一个节点不光要得到该节点本身的指针，也需要操作其前驱节点的指针，而双向链表才能支持直接查找前驱，保证操作的时间复杂度 O(1)。

**注意我们实现的双链表 API 只能从尾部插入，也就是说靠尾部的数据是最近使用的，靠头部的数据是最久为使用的**。

有了双向链表的实现，我们只需要在 LRU 算法中把它和哈希表结合起来即可，先搭出代码框架：



```java
class LRUCache {
    // key -> Node(key, val)
    private HashMap<Integer, Node> map;
    // Node(k1, v1) <-> Node(k2, v2)...
    private DoubleList cache;
    // 最大容量
    private int cap;

    public LRUCache(int capacity) {
        this.cap = capacity;
        map = new HashMap<>();
        cache = new DoubleList();
    }
```

先不慌去实现 LRU 算法的 `get` 和 `put` 方法。由于我们要同时维护一个双链表 `cache` 和一个哈希表 `map`，很容易漏掉一些操作，比如说删除某个 `key` 时，在 `cache` 中删除了对应的 `Node`，但是却忘记在 `map` 中删除 `key`。

**解决这种问题的有效方法是：在这两种数据结构之上提供一层抽象 API**。

说的有点玄幻，实际上很简单，就是尽量让 LRU 的主方法 `get` 和 `put` 避免直接操作 `map` 和 `cache` 的细节。我们可以先实现下面几个函数：



```java
/* 将某个 key 提升为最近使用的 */
private void makeRecently(int key) {
    Node x = map.get(key);
    // 先从链表中删除这个节点
    cache.remove(x);
    // 重新插到队尾
    cache.addLast(x);
}

/* 添加最近使用的元素 */
private void addRecently(int key, int val) {
    Node x = new Node(key, val);
    // 链表尾部就是最近使用的元素
    cache.addLast(x);
    // 别忘了在 map 中添加 key 的映射
    map.put(key, x);
}

/* 删除某一个 key */
private void deleteKey(int key) {
    Node x = map.get(key);
    // 从链表中删除
    cache.remove(x);
    // 从 map 中删除
    map.remove(key);
}

/* 删除最久未使用的元素 */
private void removeLeastRecently() {
    // 链表头部的第一个元素就是最久未使用的
    Node deletedNode = cache.removeFirst();
    // 同时别忘了从 map 中删除它的 key
    int deletedKey = deletedNode.key;
    map.remove(deletedKey);
}
```

这里就能回答之前的问答题「为什么要在链表中同时存储 key 和 val，而不是只存储 val」，注意 `removeLeastRecently` 函数中，我们需要用 `deletedNode` 得到 `deletedKey`。

也就是说，当缓存容量已满，我们不仅仅要删除最后一个 `Node` 节点，还要把 `map` 中映射到该节点的 `key` 同时删除，而这个 `key` 只能由 `Node` 得到。如果 `Node` 结构中只存储 `val`，那么我们就无法得知 `key` 是什么，就无法删除 `map` 中的键，造成错误。

上述方法就是简单的操作封装，调用这些函数可以避免直接操作 `cache` 链表和 `map` 哈希表，下面我先来实现 LRU 算法的 `get` 方法：



```java
public int get(int key) {
    if (!map.containsKey(key)) {
        return -1;
    }
    // 将该数据提升为最近使用的
    makeRecently(key);
    return map.get(key).val;
}
```

`put` 方法稍微复杂一些，我们先来画个图搞清楚它的逻辑：

![img](https://gblobscdn.gitbook.com/assets%2F-LrtQOWSnDdXhp3kYN4k%2Fsync%2Fca580eb634d27ec2a8f22714f741bbaf56c2b6d1.jpg?alt=media)

这样我们可以轻松写出 `put` 方法的代码：

```java
public void put(int key, int val) {
    if (map.containsKey(key)) {
        // 删除旧的数据
        deleteKey(key);
        // 新插入的数据为最近使用的数据
        addRecently(key, val);
        return;
    }

    if (cap == cache.size()) {
        // 删除最久未使用的元素
        removeLeastRecently();
    }
    // 添加为最近使用的元素
    addRecently(key, val);
}
```

# 字符串的乘除运算

```
class Solution {
public:
    bool IsDigital(char x) {
        if (x >= '0' && x <= '9') {
            return true;
        } else {
            return false;
        }
    }
    int calculate(string s) {
    	// 去除空字符串
        s.erase(s.find_last_not_of(' ') + 1);
        s.erase(0, s.find_first_not_of(' '));
        char sign = '+';
        int num = 0;
        vector<int> stackNum;
        for (int i = 0; i < s.size(); i++) {

            if (IsDigital(s[i])) {
                num = num * 10 + (s[i] - '0');
            }
             if (!IsDigital(s[i]) && s[i] != ' ' || i == s.size() - 1){
                int tmp;
                switch (sign)
                {
                    case '+':
                        stackNum.push_back(num);
                        break;
                    case '-':
                        stackNum.push_back(-num);
                        break;
                    case '*':
                        tmp = stackNum.back();
                        stackNum.pop_back();
                        stackNum.push_back(tmp * num);
                        break;
                    case '/':
                        tmp = stackNum.back();
                        stackNum.pop_back();
                        stackNum.push_back(tmp / num);
                        break;
                }
                sign = s[i];
                num = 0;
            }
        }
        int res = 0;
        while (!stackNum.empty()) {
            res += stackNum.back();
            stackNum.pop_back();
        }
        return res;
    }
};
```

# 随机洗牌

```c++
// 得到一个在闭区间 [min, max] 内的随机整数
int randInt(int min, int max)
{
	srand(time(0));
	return rand() % (max - min + 1) + min;
}

// 第一种写法
void shuffle(int[] arr) {
    int n = arr.length();
    /******** 区别只有这两行 ********/
    for (int i = 0 ; i < n; i++) {
        // 从 i 到最后随机选一个元素
        int rand = randInt(i, n - 1);
        /*************************/
        swap(arr[i], arr[rand]);
    }
}
```

# 二分法

## 基本框架

```c
int binary_search(int[] nums, int target) {
    int left = 0, right = nums.length - 1; 
    while(left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1; 
        } else if(nums[mid] == target) {
            // 直接返回
            return mid;
        }
    }
    // 直接返回
    return -1;
}
​
int left_bound(int[] nums, int target) {
    int left = 0, right = nums.length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] == target) {
            // 别返回，锁定左侧边界
            right = mid - 1;
        }
    }
    // 最后要检查 left 越界的情况
    if (left >= nums.length || nums[left] != target)
        return -1;
    return left;
}
​
​
int right_bound(int[] nums, int target) {
    int left = 0, right = nums.length - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (nums[mid] < target) {
            left = mid + 1;
        } else if (nums[mid] > target) {
            right = mid - 1;
        } else if (nums[mid] == target) {
            // 别返回，锁定右侧边界
            left = mid + 1;
        }
    }
    // 最后要检查 right 越界的情况
    if (right < 0 || nums[right] != target)
        return -1;
    return right;
}
```

# 双指针

## 是否有环形

```c
boolean hasCycle(ListNode head) {
    ListNode fast, slow;
    fast = slow = head;
    while (fast != null && fast.next != null) {
        fast = fast.next.next;
        slow = slow.next;
​
        if (fast == slow) return true;
    }
    return false;
}
```

## 已知链表中含有环，返回这个环的起始位置

```c
ListNode detectCycle(ListNode head) {
    ListNode fast, slow;
    fast = slow = head;
    while (fast != null && fast.next != null) {
        fast = fast.next.next;
        slow = slow.next;
        if (fast == slow) break;
    }
    // 上面的代码类似 hasCycle 函数
    slow = head;
    while (slow != fast) {
        fast = fast.next;
        slow = slow.next;
    }
    return slow;
}
```

## 寻找中点

```c
while (fast != null && fast.next != null) {
    fast = fast.next.next;
    slow = slow.next;
}
// slow 就在中间位置
return slow;
```

## 寻找链表的倒数第 k 个元素

```
ListNode slow, fast;
slow = fast = head;
while (k-- > 0) 
    fast = fast.next;
​
while (fast != null) {
    slow = slow.next;
    fast = fast.next;
}
return slow;
```

# 滑动窗口

## 基本框架

```
int left = 0, right = 0;
​
while (right < s.size()) {`
    // 增大窗口
    window.add(s[right]);
    right++;
​
    while (window needs shrink) {
        // 缩小窗口
        window.remove(s[left]);
        left++;
    }
}
```

## [最小覆盖子串](https://leetcode-cn.com/problems/minimum-window-substring/)

给你一个字符串 S、一个字符串 T 。请你设计一种算法，可以在 O(n) 的时间复杂度内，从字符串 S 里面找出：包含 T 所有字符的最小子串。 

**示例：**

```
输入：S = "ADOBECODEBANC", T = "ABC"
输出："BANC"
```

* **解答**

```c++
class Solution {
public:
    string minWindow(string s, string t) {
        int M = s.size();
        int N = t.size();
        unordered_map<char, int> scount;
        unordered_map<char, int> tcount;
        // left and right means [left, right] of s
        // count means the same chars of s[left, right] with t
        int left = 0, right = 0, count = 0;
        int minLen = INT_MAX;
        string res;
        for (char c : t)
            ++tcount[c];
        while (right < M) {
            char c = s[right];
            scount[c] += 1;
            if (tcount.count(c) && scount[c] <= tcount[c]) {
                count += 1;
            }
            while (left <= right && count == N) {
                if (minLen > right - left + 1) {
                    minLen = right - left + 1;
                    res = s.substr(left, minLen);
                }
                char l = s[left];
                scount[l] -= 1;
                if (tcount.count(l) && scount[l] < tcount[l])
                    count -= 1;
                ++left;
            }
            ++right;
        }
        return res;
    }
};
```



# 回溯算法

## 基本框架

```c
result = []
def backtrack(路径, 选择列表):
    if 满足结束条件:
        result.add(路径)
        return
​
    for 选择 in 选择列表:
        做选择
        backtrack(路径, 选择列表)
        撤销选择
```

# BFS

## 基本框架

```c
// 计算从起点 start 到终点 target 的最近距离
int BFS(Node start, Node target) {
    Queue<Node> q; // 核心数据结构
    Set<Node> visited; // 避免走回头路
​
    q.offer(start); // 将起点加入队列
    visited.add(start);
    int step = 0; // 记录扩散的步数
​
    while (q not empty) {
        int sz = q.size();
        /* 将当前队列中的所有节点向四周扩散 */
        for (int i = 0; i < sz; i++) {
            Node cur = q.poll();
            /* 划重点：这里判断是否到达终点 */
            if (cur is target)
                return step;
            /* 将 cur 的相邻节点加入队列 */
            for (Node x : cur.adj())
                if (x not in visited) {
                    q.offer(x);
                    visited.add(x);
                }
        }
        /* 划重点：更新步数在这里 */
        step++;
    }
}
```

# Union-find

## 基本框架

```c
class UF {
    // 连通分量个数
    private int count;
    // 存储一棵树
    private int[] parent;
    // 记录树的“重量”
    private int[] size;
​
    public UF(int n) {
        this.count = n;
        parent = new int[n];
        size = new int[n];
        for (int i = 0; i < n; i++) {
            parent[i] = i;
            size[i] = 1;
        }
    }
​
    public void union(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        if (rootP == rootQ)
            return;
​
        // 小树接到大树下面，较平衡
        if (size[rootP] > size[rootQ]) {
            parent[rootQ] = rootP;
            size[rootP] += size[rootQ];
        } else {
            parent[rootP] = rootQ;
            size[rootQ] += size[rootP];
        }
        count--;
    }
​
    public boolean connected(int p, int q) {
        int rootP = find(p);
        int rootQ = find(q);
        return rootP == rootQ;
    }
​
    private int find(int x) {
        while (parent[x] != x) {
            // 进行路径压缩
            parent[x] = parent[parent[x]];
            x = parent[x];
        }
        return x;
    }
​
    public int count() {
        return count;
    }
}
```

# 单调栈

## 基本框架

```c
class Solution {
public:
    vector<int> nextGreaterElement(vector<int>& nums1) {
        myStack.push_back(nums1[0]);// 初始位置入栈
        while (i++ < nums1.size()) {
            while (!myStack.empty() && nums1[i] > myStack.back()) {
                出栈前的处理。。。
                myStack.pop_back();
            }
            myStack.push_back(nums2[i]);// 单调递减或者递增入栈
        }
        return nums1;
    }
};
	
```

# 贪心算法

## 基本框架

**不知道读者有没有发现，有关动态规划的问题，大多是让你求最值的**，比如最长子序列，最小编辑距离，最长公共子串等等等。这就是规律，因为动态规划本身就是运筹学里的一种求最值的算法。

那么贪心算法作为特殊的动态规划也是一样，一般也是让你求个最值。这道题表面上不是求最值，但是可以改一改：



## [跳跃游戏](https://leetcode-cn.com/problems/jump-game/)

给定一个非负整数数组，你最初位于数组的第一个位置。

数组中的每个元素代表你在该位置可以跳跃的最大长度。

判断你是否能够到达最后一个位置。

**示例 1:**

```
输入: [2,3,1,1,4]
输出: true
解释: 我们可以先跳 1 步，从位置 0 到达 位置 1, 然后再从位置 1 跳 3 步到达最后一个位置。
```

**示例 2:**

```
输入: [3,2,1,0,4]
输出: false
解释: 无论怎样，你总会到达索引为 3 的位置。但该位置的最大跳跃长度是 0 ， 所以你永远不可能到达最后一个位置。
```

* 解答

	```c++
	class Solution {
	public:
	    bool canJump(vector<int>& nums) {
	        int maxFast = 0; //表示当前能跳到的最大位置
			for (int i = 0; i < nums.size() - 1; i++) {
	            maxFast = max(maxFast, i + nums[i]);
	            // 最远位置还比当前位置小  肯定完蛋
	            if (maxFast <= i) {
	                return false;
	            }
	        }
	        return (maxFast >= (nums.size() - 1));
	    }
	};
	```

	## [跳跃游戏 II](https://leetcode-cn.com/problems/jump-game-ii/)

	给定一个非负整数数组，你最初位于数组的第一个位置。

	数组中的每个元素代表你在该位置可以跳跃的最大长度。

	你的目标是使用最少的跳跃次数到达数组的最后一个位置。

	**示例:**

	```
	输入: [2,3,1,1,4]
	输出: 2
	解释: 跳到最后一个位置的最小跳跃数是 2。
	     从下标为 0 跳到下标为 1 的位置，跳 1 步，然后跳 3 步到达数组的最后一个位置。
	```

* 解答

	**动态规划**

	说说动态规划的思路，采用自顶向下的递归动态规划，可以这样定义一个`dp`函数：

	```c++
	// 定义：从索引 p 跳到最后一格，至少需要 dp(nums, p) 步
	int dp(vector<int>& nums, int p);
	```

	我们想求的结果就是`dp(nums, 0)`，base case 就是当`p`超过最后一格时，不需要跳跃：

	```
	if (p >= nums.size() - 1) {
	    return 0;
	}
	```

	通过备忘录`memo`消除重叠子问题，取其中的最小值最为最终答案：

	```c
	vector<int> memo;
	// 主函数
	int jump(vector<int>& nums) {
	    int n = nums.size();
	    // 备忘录都初始化为 n，相当于 INT_MAX
	    // 因为从 0 调到 n - 1 最多 n - 1 步
	    memo = vector<int>(n, n);
	    return dp(nums, 0);
	}
	
	int dp(vector<int>& nums, int p) {
	    int n = nums.size();
	    // base case
	    if (p >= n - 1) {
	        return 0;
	    }
	    // 子问题已经计算过
	    if (memo[p] != n) {
	        return memo[p];
	    }
	    int steps = nums[p];
	    // 你可以选择跳 1 步，2 步...
	    for (int i = 1; i <= steps; i++) {
	        // 穷举每一个选择
	        // 计算每一个子问题的结果
	        int subProblem = dp(nums, p + i);
	        // 取其中最小的作为最终结果
	        memo[p] = min(memo[p], subProblem + 1);
	    }
	    return memo[p];
	}
	```

	该算法的时间复杂度是 递归深度 × 每次递归需要的时间复杂度，即 O(N^2)，在 LeetCode 上是无法通过所有用例的，会超时。

	**贪心算法比动态规划多了一个性质：贪心选择性质**。我知道大家都不喜欢看严谨但枯燥的数学形式定义，那么我们就来直观地看一看什么样的问题满足贪心选择性质。

	刚才的动态规划思路，不是要穷举所有子问题，然后取其中最小的作为结果吗？核心的代码框架是这样：

	```c
	    for (int i = 1; i <= steps; i++) {
	        // 穷举每一个选择
	        // 计算每一个子问题的结果
	        int subProblem = dp(nums, p + i);
	        // 取其中最小的作为最终结果
	        memo[p] = min(memo[p], subProblem + 1);
	    }
	```

	for 循环中会陷入递归计算子问题，这是动态规划时间复杂度高的根本原因。

	但是，真的需要「递归地」计算出每一个子问题的结果，然后求最值吗？**直观地想一想，似乎不需要递归，只需要判断哪一个选择最具有「潜力」即可**：

	![image-20200918172911362](C:\Users\q00580359\AppData\Roaming\Typora\typora-user-images\image-20200918172911362.png)

	比如上图这种情况从开始位置应该跳到多少呢？

	显然应该跳 2 步调到索引 2，**因为`nums[2]`的可跳跃区域涵盖了索引区间`[3..6]`**，比其他的都大。如果想求最少的跳跃次数，那么往索引 2 跳必然是最优的选择。

	你看，**这就是贪心选择性质，我们不需要「递归地」计算出所有选择的具体结果然后比较求最值，而只需要做出那个最有「潜力」，看起来最优的选择即可**。

	绕过这个弯儿来，就可以写代码了：

	**贪心算法**

	```c
	class Solution {
	public:
	int jump(vector<int>& nums) {
	    int n = nums.size();
	    if (n == 1) {
	        return 0;
	    }
	    int end = 0, farthest = 0;
	    int jumps = 0;
	    for (int i = 0; i < n; i++) {
	        farthest = max(nums[i] + i, farthest);
	        if (farthest >= (n - 1) ) {
	            jumps ++;
	            return jumps;
        }
	        if (end == i) {
            jumps++;
	            end = farthest;
        }
	    }
    return 0;
	}
};
	```

	结合刚才那个图，就知道这段短小精悍的代码在干什么了：

	![image-20200918173341247](C:\Users\q00580359\AppData\Roaming\Typora\typora-user-images\image-20200918173341247.png)

	`i`和`end`标记了可以选择的跳跃步数，`farthest`标记了所有可选择跳跃步数`[i..end]`中能够跳到的最远距离，`jumps`记录了跳跃次数。

	本算法的时间复杂度 O(N)，空间复杂度 O(1)，可以说是非常高效，动态规划都被吊起来打了。

	## [ 灌溉花园的最少水龙头数目](https://leetcode-cn.com/problems/minimum-number-of-taps-to-open-to-water-a-garden/)

	在 x 轴上有一个一维的花园。花园长度为 `n`，从点 `0` 开始，到点 `n` 结束。

	花园里总共有 `n + 1` 个水龙头，分别位于 `[0, 1, ..., n]` 。

	给你一个整数 `n` 和一个长度为 `n + 1` 的整数数组 `ranges` ，其中 `ranges[i]` （下标从 0 开始）表示：如果打开点 `i` 处的水龙头，可以灌溉的区域为 `[i - ranges[i], i + ranges[i]]` 。
	
	请你返回可以灌溉整个花园的 **最少水龙头数目** 。如果花园始终存在无法灌溉到的地方，请你返回 **-1** 。
	
	 
	
	**示例 1：**
	
	![img](https://assets.leetcode-cn.com/aliyun-lc-upload/uploads/2020/01/19/1685_example_1.png)
	
	```
	输入：n = 5, ranges = [3,4,1,1,0,0]
输出：1
	解释：
点 0 处的水龙头可以灌溉区间 [-3,3]
	点 1 处的水龙头可以灌溉区间 [-3,5]
	点 2 处的水龙头可以灌溉区间 [1,3]
	点 3 处的水龙头可以灌溉区间 [2,4]
	点 4 处的水龙头可以灌溉区间 [4,4]
	点 5 处的水龙头可以灌溉区间 [5,5]
只需要打开点 1 处的水龙头即可灌溉整个花园 [0,5] 。
	```

	**示例 2：**
	
	```
	输入：n = 3, ranges = [0,0,0,0]
输出：-1
	解释：即使打开所有水龙头，你也无法灌溉整个花园。
	```
```
	
	**示例 3：**
	
```
输入：n = 7, ranges = [1,2,1,0,2,1,0,1]
	输出：3
```
	
	**示例 4：**
	
```
输入：n = 8, ranges = [4,0,0,0,0,0,0,0,4]
	输出：2
```
	
	**示例 5：**
	
```
	输入：n = 8, ranges = [4,0,0,0,4,0,0,0,4]
	输出：1
	```
	
	**提示：**
	
	- `1 <= n <= 10^4`
	- `ranges.length == n + 1`
	- `0 <= ranges[i] <= 100`

* **解答**

	**贪心算法**

	```c
	bool Compare(pair<int, int> &a, pair<int, int> &b) {
	    return a.first < b.first;
	}
	class Solution {
	public:
	    int minTaps(int n, vector<int>& ranges) {
	        vector<pair<int, int>> range;
	        for (int i = 0; i < ranges.size(); i++) {
	            range.push_back({i - ranges[i], i + ranges[i]});
	        }
	        sort(range.begin(), range.end(),Compare);
	        int right = 0;
	        int nextMaxRight;
	        int res = 0;
	        int i = 0;
	        while (right < n) {
	            nextMaxRight = right;
	            while (i < range.size() && range[i].first <= right) {
	                nextMaxRight = max(nextMaxRight, range[i].second);
	                i++;
	            }
	            if (nextMaxRight <= right) {
	                return -1;
	            }
	            right = nextMaxRight;
	            res++;
	        }
	        return res;
	    }
	};
	```

# 字符串

## [反转字符串](https://leetcode-cn.com/problems/reverse-string/)--双指针

编写一个函数，其作用是将输入的字符串反转过来。输入字符串以字符数组 `char[]` 的形式给出。

不要给另外的数组分配额外的空间，你必须**[原地](https://baike.baidu.com/item/原地算法)修改输入数组**、使用 O(1) 的额外空间解决这一问题。

你可以假设数组中的所有字符都是 [ASCII](https://baike.baidu.com/item/ASCII) 码表中的可打印字符。

**示例 1：**

```
输入：["h","e","l","l","o"]
输出：["o","l","l","e","h"]
```

**示例 2：**

```
输入：["H","a","n","n","a","h"]
输出：["h","a","n","n","a","H"]
```

* **解答**----双指针

  ```c
  class Solution {
  public:
      void Swap(int &a, int &b)
      {
          int tmp;
          tmp = a;
          a = b;
          b = tmp;
      }
      void reverseString(vector<char>& s) 
      {
          int left = 0;
          int right = s.size() - 1;
          while (left <= right) {
              swap(s[left], s[right]);
              left++;
              right--;
          }
      }
  };
  ```

## 字符串的匹配

实现 [strStr()](https://baike.baidu.com/item/strstr/811469) 函数。

给定一个 haystack 字符串和一个 needle 字符串，在 haystack 字符串中找出 needle 字符串出现的第一个位置 (从0开始)。如果不存在，则返回 **-1**。

**示例 1:**

```
输入: haystack = "hello", needle = "ll"
输出: 2
```

**示例 2:**

```
输入: haystack = "aaaaa", needle = "bba"
输出: -1
```

* **解答**

  ```c++
  // find 函数
  class Solution {
  public:
      int strStr(string haystack, string needle) {
          return haystack.find(needle);
      }
  };
  // 正则表达
  class Solution {
  public:
      int strStr(string haystack, string needle) {
          smatch re;
          if (haystack.size() == 0 && needle.size() == 0) return 0;
          regex_search(haystack, re, regex(needle));
          if (re.position() >= haystack.size()) {
              return -1;
          }
          return re.position();
      }
  };
  
  ```

## 回文字符串验证--双指针

  ```c++
  class Solution {
  public:
      bool isPalindrome(string s) {
          string sgood;
          for (char ch: s) {
              // man isalnum可以查看函数的用法
              if (isalnum(ch)) {
                  sgood += tolower(ch);
              }
          }
          int n = sgood.size();
          int left = 0, right = n - 1;
          while (left < right) {
             if (sgood[left] != sgood[right]) {
                  return false;
              }
              ++left;
              --right;
          }
          return true;
      }
  };
  ```

## 字符串匹配--[KMP](https://www.bilibili.com/video/BV1S64y1u74P?from=search&seid=7029455513078182732)

  ```c++
  // 暴力解法
  int IndexKmpMinums(string chang, string duan)
  {
      int c = 0;
      int d = 0;
      while (c < chang.size() && d < duna.size()) {
          if (chang[c] == duan[d]) { //匹配
              c++;
              d++;
          } else { // 不匹配
              c = c - d + 1;
              d = 0;
          }
      }
      return d == duan.size() ? c - d : -1;
  }
  
  //KMP
  int IndexKmpMinums(string chang, string duan)
  {
      int c = 0;
      int d = 0;
      vector<int> next = GetNext(duan);
      while (c < chang.size() && d < duna.size()) {
          if (d == -1 || chang[c] == duan[d]) { //匹配
              c++;
              d++;
          } else { // 不匹配
              d = next[d];
          }
      }
      return d == duan.size() ? c - d : -1;
  }
  
  vector<int> GetNext(string duan)
  {
      int c = 0;
      int d = -1;
      vector<int> next(duan.size(), -1);
      while (c < duna.size() - 1) {
          if (d == -1 || duan[c] == duan[d]) { //匹配
              c++;
              d++;
              next[c] = d;
          } else { // 不匹配
              d = next[d];
          }
      }
      return next;
  }
  ```

##   字符串乘法

```java
class Solution {
    public String multiply(String num1, String num2) {
        /**
        num1的第i位(高位从0开始)和num2的第j位相乘的结果在乘积中的位置是[i+j, i+j+1]
        例: 123 * 45,  123的第1位 2 和45的第0位 4 乘积 08 存放在结果的第[1, 2]位中
          index:    0 1 2 3 4  
              
                        1 2 3
                    *     4 5
                    ---------
                          1 5
                        1 0
                      0 5
                    ---------
                      0 6 1 5
                        1 2
                      0 8
                    0 4
                    ---------
                    0 5 5 3 5
        这样我们就可以单独都对每一位进行相乘计算把结果存入相应的index中        
        **/
        
        int n1 = num1.length()-1;
        int n2 = num2.length()-1;
        if(n1 < 0 || n2 < 0) return "";
        int[] mul = new int[n1+n2+2];
        
        for(int i = n1; i >= 0; --i) {
            for(int j = n2; j >= 0; --j) {
                int bitmul = (num1.charAt(i)-'0') * (num2.charAt(j)-'0');      
                bitmul += mul[i+j+1]; // 先加低位判断是否有新的进位
                
                mul[i+j] += bitmul / 10;
                mul[i+j+1] = bitmul % 10;
            }
        }
        
        StringBuilder sb = new StringBuilder();
        int i = 0;
        // 去掉前导0
        while(i < mul.length-1 && mul[i] == 0) 
            i++;
        for(; i < mul.length; ++i)
            sb.append(mul[i]);
        return sb.toString();
    }
}
```

https://www.cnblogs.com/liuzhen1995/p/12044241.html

## [最短回文串](https://leetcode-cn.com/problems/shortest-palindrome/)

给定一个字符串 ***s***，你可以通过在字符串前面添加字符将其转换为回文串。找到并返回可以用这种方式转换的最短回文串。

**示例 1:**

```
输入: "aacecaaa"
输出: "aaacecaaa"
```

**示例 2:**

```
输入: "abcd"
输出: "dcbabcd"
```



```c
class Solution {
public:
    string shortestPalindrome(string s) {
        int left = 0;
        int right =0;
        int mux = 1;
        int base = 131;
        int mod = 1000000007;
        int best = -1;
        int n = s.size();
        for (int i = 0; i < s.size(); i++) {
            left = ((long long) left * base + s[i]) % mod;
            right = (right + (long long)mux * s[i]) % mod;
            if (left == right) {
                best = i;
            }
            mux = ((long long) base * mux) % mod;
        }
        string add = (best == s.size() - 1 ? "" : s.substr(best + 1, n));
        reverse(add.begin(), add.end());
        return add + s;
    }
};
```

## [最长特殊序列 II](https://leetcode-cn.com/problems/longest-uncommon-subsequence-ii/)

给定字符串列表，你需要从它们中找出最长的特殊序列。最长特殊序列定义如下：该序列为某字符串独有的最长子序列（即不能是其他字符串的子序列）。

**子序列**可以通过删去字符串中的某些字符实现，但不能改变剩余字符的相对顺序。空序列为所有字符串的子序列，任何字符串为其自身的子序列。

输入将是一个字符串列表，输出是最长特殊序列的长度。如果最长特殊序列不存在，返回 -1 。

 

**示例：**

```
输入: "aba", "cdc", "eae"
输出: 3
```

 

**提示：**

1. 所有给定的字符串长度不会超过 10 。
2. 给定字符串列表的长度将在 [2, 50 ] 之间。

**解题思路**

1.按照长度大小排序
2.对字符串进行出现个数统计
3.如果该字符串只出现过1次，且不是前面字符串的子串，则它是最大的。

字符串子串判定函数，需要使用双指针；

```c
class Solution {
public:
    static bool mycmp(string &a,string &b){

        if(a.size() == b.size()){
            return a < b;
        }

        return a.size() > b.size();
    }

    bool isSubSeq(string &a,string &b){
        int i = 0, j = 0;
        for (i = 0, j = 0; i < a.size() && j < b.size();i++){
            if(a[i] == b[j] ){
                j++;
            }
        }

        if(j == b.size()){
            return true;
        }

        return false;
    }

    int findLUSlength(vector<string>& strs) {

        unordered_map<string, int> countmap;
        sort(strs.begin(), strs.end(), mycmp);

        for(auto &s:strs){
            countmap[s]++;
        }

        for (int i = 0; i < strs.size();i++){
            if(countmap[strs[i]] == 1){
                int flag = false;
                int j = 0;
                for (j = 0; j < i;j++){
                    if(isSubSeq(strs[j],strs[i])){
                        flag = true;
                        break;
                    }
                }

                if(flag == false){
                    return strs[i].size();
                }
            }
        }

        return -1;
    }
};
```

## 计算器

```c
def calculate(s: str) -> int:
    def helper(s: List) -> int:
        stack = []
        sign = '+'
        num = 0

        while len(s) > 0:
            c = s.pop(0)
            if c.isdigit():
                num = 10 * num + int(c)
			if (c == '('):
				num = help(s)
            if (not c.isdigit() and c != ' ') or len(s) == 0:
                if sign == '+':
                    stack.append(num)
                elif sign == '-':
                    stack.append(-num)
                elif sign == '*':
                    stack[-1] = stack[-1] * num
                elif sign == '/':
                    # python 除法向 0 取整的写法
                    stack[-1] = int(stack[-1] / float(num))                    
                num = 0
                sign = c
			if (c == ')'):
				break
        return sum(stack)
    # 需要把字符串转成列表方便操作
    return helper(list(s))
```

## [通配符匹配](https://leetcode-cn.com/problems/wildcard-matching/)

给定一个字符串 (`s`) 和一个字符模式 (`p`) ，实现一个支持 `'?'` 和 `'*'` 的通配符匹配。

```
'?' 可以匹配任何单个字符。
'*' 可以匹配任意字符串（包括空字符串）。
```

两个字符串**完全匹配**才算匹配成功。

**说明:**

- `s` 可能为空，且只包含从 `a-z` 的小写字母。
- `p` 可能为空，且只包含从 `a-z` 的小写字母，以及字符 `?` 和 `*`。

**示例 1:**

```
输入:
s = "aa"
p = "a"
输出: false
解释: "a" 无法匹配 "aa" 整个字符串。
```

**示例 2:**

```
输入:
s = "aa"
p = "*"
输出: true
解释: '*' 可以匹配任意字符串。
```

**示例 3:**

```
输入:
s = "cb"
p = "?a"
输出: false
解释: '?' 可以匹配 'c', 但第二个 'a' 无法匹配 'b'。
```

**示例 4:**

```
输入:
s = "adceb"
p = "*a*b"
输出: true
解释: 第一个 '*' 可以匹配空字符串, 第二个 '*' 可以匹配字符串 "dce".
```

**示例 5:**

```
输入:
s = "acdcb"
p = "a*c?b"
输出: false
```

![image-20200922215809807](C:\Users\q00580359\AppData\Roaming\Typora\typora-user-images\image-20200922215809807.png)

![image-20200922215721438](C:\Users\q00580359\AppData\Roaming\Typora\typora-user-images\image-20200922215721438.png)

```c
class Solution {
public:
    bool isMatch(string s, string p) {
        int m = s.size();
        int n = p.size();
        vector<vector<int>> dp(m + 1, vector<int>(n + 1));
        dp[0][0] = true;
        for (int i = 1; i <= n; ++i) {
            if (p[i - 1] == '*') {
                dp[0][i] = dp[0][i - 1];
            }
            else {
                break;
            }
        }
        for (int i = 1; i <= m; ++i) {
            for (int j = 1; j <= n; ++j) {
                if (p[j - 1] == '*') {
                    dp[i][j] = dp[i][j - 1] | dp[i - 1][j];
                }
                else if (p[j - 1] == '?' || s[i - 1] == p[j - 1]) {
                    dp[i][j] = dp[i - 1][j - 1];
                }
            }
        }
        return dp[m][n];
    }
};
```

## 正则

#### 具有特殊意义的元字符

`\`：`\字符`能够改变`字符`原本的含义

`^`：`^字符`指示字符串的头，且要求字符串以`字符`开头，不占位。`\^`表示一个真正的^符号。

`$`：`$字符`指示字符串的尾，且要求字符串以`字符`结尾，不占位。`\$`表示一个真正的$符号。

`()`：分组，大正则中包含小正则。可以改变默认的优先级。在模式中可以使用`\1`来表示第一组已然捕获到的东西。

`\b`：指示字符串的边界（头/尾/空格左/空格右），`字符\b`要求边界的左边是`字符`，`\b字符`要求边界的右边是`字符`。

`.`：表示一个除了`\n`以外的任意一个字符。`\.`表示一个真正的.符号。

`|`：`字符串1|字符串2`表示一个**字符串**，该字符串是字符串1、字符串2中的一个。`|`在正则中的优先级比较混乱，所以建议加上足够多的括号来分组。

`[]`：`[字符1字符2字符3...]`表示一个字符，该字符是字符1、字符2、字符3……中的某一个。中括号中出现的所有字符都是代表本身意思的字符（没有特殊含义），如`[.]`只能匹配`.`符号，而不能匹配任意符号。

`[^字符1字符2字符3...]`表示一个字符，该字符不是字符1、字符2、字符3……中的任何一个

`[a-z]`表示一个字符，该字符是a、b、c……z中的某一个

`[^a-z]`表示一个字符，该字符不是a、b、c……z中的任何一个

`\w`：表示一个字符，该字符是数字、字母、下划线中的某一个。等价于`[(0-9)(a-z)(A-Z)(_)]

`\W`：表示一个字符，该字符不是数字、字母、下划线中的任何一个。等价于[]

`\d`表示一个字符，该字符是0、1、2……9中的某一个

`\D`表示一个字符，该字符不是0、1、2……9中的任何一个

`\s`表示一个字符，该字符是空白符（空格、制表符、换页符）2、代表出现次数的

#### 量词元字符

`*`：`字符*`要求`字符`出现0到多次

`+`：`字符+`要求`字符`出现1到多次

`?`：`字符?`要求`字符`出现0次或1次

`{n}`：`字符{n}`要求`字符`出现n次

`{n,}`：`字符{n,}`要求`字符`出现n到多次

`{n,m}`：`字符{n,m}`要求`字符`出现n到m次、

## [ 验证IP地址](https://leetcode-cn.com/problems/validate-ip-address/)

编写一个函数来验证输入的字符串是否是有效的 IPv4 或 IPv6 地址。

- 如果是有效的 IPv4 地址，返回 `"IPv4"` ；
- 如果是有效的 IPv6 地址，返回 `"IPv6"` ；
- 如果不是上述类型的 IP 地址，返回 `"Neither"` 。

**IPv4** 地址由十进制数和点来表示，每个地址包含 4 个十进制数，其范围为 0 - 255， 用(".")分割。比如，`172.16.254.1`；

同时，IPv4 地址内的数不会以 0 开头。比如，地址 `172.16.254.01` 是不合法的。

**IPv6** 地址由 8 组 16 进制的数字来表示，每组表示 16 比特。这些组数字通过 (":")分割。比如, `2001:0db8:85a3:0000:0000:8a2e:0370:7334` 是一个有效的地址。而且，我们可以加入一些以 0 开头的数字，字母可以使用大写，也可以是小写。所以， `2001:db8:85a3:0:0:8A2E:0370:7334` 也是一个有效的 IPv6 address地址 (即，忽略 0 开头，忽略大小写)。

然而，我们不能因为某个组的值为 0，而使用一个空的组，以至于出现 (::) 的情况。 比如， `2001:0db8:85a3::8A2E:0370:7334` 是无效的 IPv6 地址。

同时，在 IPv6 地址中，多余的 0 也是不被允许的。比如， `02001:0db8:85a3:0000:0000:8a2e:0370:7334` 是无效的。

 

**示例 1：**

```
输入：IP = "172.16.254.1"
输出："IPv4"
解释：有效的 IPv4 地址，返回 "IPv4"
```

**示例 2：**

```
输入：IP = "2001:0db8:85a3:0:0:8A2E:0370:7334"
输出："IPv6"
解释：有效的 IPv6 地址，返回 "IPv6"
```

**示例 3：**

```
输入：IP = "256.256.256.256"
输出："Neither"
解释：既不是 IPv4 地址，又不是 IPv6 地址
```

**示例 4：**

```
输入：IP = "2001:0db8:85a3:0:0:8A2E:0370:7334:"
输出："Neither"
```

**示例 5：**

```
输入：IP = "1e1.4.5.6"
输出："Neither"
```

 

```c++
class Solution {
public:
    string validIPAddress(string IP) {
        vector<string> ipList;
        string tmp;
        for (auto iter : IP) {
            if (iter == '.' || iter == ':') {
                ipList.push_back(tmp);
                tmp = "";
            } else {
                tmp += iter;
            }   
        }
        ipList.push_back(tmp);
        if (IP.find('.') != string::npos) {
            if (ipList.size() != 4) return "Neither";
            for (auto iter : ipList) {
                if (iter.size() == 0 || iter.size() > 3) return "Neither";
                for (auto iterC : iter) {
                    if (!isdigit(iterC)) {
                        return "Neither";
                    }
                }
                if (iter.size() != 1 && iter[0] == '0') return "Neither";
                int tmp = stoi(iter);
                if (tmp < 0 || tmp > 255) {
                    return "Neither";
                }
            }
            return "IPv4";
        } else {
            if (ipList.size() != 8) return "Neither";
            for (auto iter : ipList) {
                if (iter.size() == 0 || iter.size() > 4) return "Neither";
                for (auto iterC : iter) {
                    char tmp = tolower(iterC);
                    if (!isdigit(iterC) && (tmp < 'a' || tmp > 'f')) {
                        return "Neither";
                    }
                }
            }
            return "IPv6";
        }
    }
};

```

- - 时间复杂度 O(N)*O*(*N*) ：遍历一遍字符串 `s`；
	- 空间复杂度 O(N)*O*(*N*) ：各行字符串共占用 O(N)*O*(*N*) 额外空间。

## [Z 字形变换](https://leetcode-cn.com/problems/zigzag-conversion/)

将一个给定字符串根据给定的行数，以从上往下、从左到右进行 Z 字形排列。

比如输入字符串为 `"LEETCODEISHIRING"` 行数为 3 时，排列如下：

```
L   C   I   R
E T O E S I I G
E   D   H   N
```

之后，你的输出需要从左往右逐行读取，产生出一个新的字符串，比如：`"LCIRETOESIIGEDHN"`。

请你实现这个将字符串进行指定行数变换的函数：

```
string convert(string s, int numRows);
```

**示例 1:**

```
输入: s = "LEETCODEISHIRING", numRows = 3
输出: "LCIRETOESIIGEDHN"
```

**示例 2:**

```
输入: s = "LEETCODEISHIRING", numRows = 4
输出: "LDREOEIIECIHNTSG"
解释:

L     D     R
E   O E   I I
E C   I H   N
T     S     G
```

```c++
class Solution {
public:
    string convert(string s, int numRows) {
        vector<string> res(numRows,"");
        string result;
        int flag = 1;
        int rows = 0;
        if (numRows == 1) {
            return s;
        }
        for (auto &iter : s) {
            if (rows == numRows - 1 && flag == 1) {
                flag = -flag;
            }
            if (rows == 0 && flag == -1) {
                flag = -flag;
            }
            res[rows] += iter;
            rows += flag;
        }
        for (auto iter : res) {
            result += iter;
        }
        return result;
    }
};
```

<<<<<<< HEAD
## [括号生成](https://leetcode-cn.com/problems/generate-parentheses/)

数字 *n* 代表生成括号的对数，请你设计一个函数，用于能够生成所有可能的并且 **有效的** 括号组合。

**示例：**

```
输入：n = 3
输出：[
       "((()))",
       "(()())",
       "(())()",
       "()(())",
       "()()()"
     ]
```

```c++
class Solution {
public:
    void  dfs(vector<string> &res, string &tmp, int left, int right, int n)
    {
        if (tmp.size() == 2 * n) {
            res.push_back(tmp);
        }
        if (left < n) {
            tmp.push_back('(');
            dfs(res, tmp, left + 1, right, n);
            tmp.pop_back();
        }
        if (right < left) {
            tmp.push_back(')');
            dfs(res, tmp, left, right + 1, n);
            tmp.pop_back();
        }
    }
    vector<string> generateParenthesis(int n) {
        vector<string> res;
        string tmp;
        dfs(res, tmp, 0, 0, n);
        return res;
=======
# 区间合并

```
bool compare(vector<int>& a, vector<int>& b)
{
    if (a[0] < b[0]) {
        return true;
    }
    else if (a[0] == b[0]) {
        if (a[1] > b[1]) {
            return true;
        } else {
            return false;
        }
    } else {
        return false;
    }
}
class Solution {
public:
    int videoStitching(vector<vector<int>>& clips, int T)
    {
        sort(clips.begin(), clips.end(), compare);
        if (clips.size() == 0) return -1;
        if (clips.size() == 1) {
            if (clips[0][0] <= 0 && clips[0][1] >= T) {
                return 1;
            } else {
                return -1;
            }
        }
        if (clips[0][0] <=0 && clips[0][1] >= T) return 1;
        if (clips[0][0] > 0) return -1;
        int end = clips[0][1];
        int farthest = clips[0][1];
        int count = 1;
        for (int i = 1; i < clips.size(); i++) {
            if (clips[i][0] > end) {
                if (clips[i][0] > farthest) return -1;
                count++;
                end = farthest;
            }

            farthest = max(clips[i][1], farthest);
            if (farthest >= T) {
                count++;
                return count;
            }

        }
        return -1;
>>>>>>> 3148c9c4411681c3cb4cd32703841fb8d30fb82c
    }
};
```



# Vscode使用

* 可以使用cmake先编译出可执行文件，然后再配置launch.json

```json
  {
      "configurations": [
      {
          "name": "(gdb) 启动",
          "type": "cppdbg",
          "request": "launch",
		//注意这里的路径包含${workspaceFolder}才能通过
          "program": "${workspaceFolder}/bin/Debug/test",
          "args": [],
          "stopAtEntry": false,
          "cwd": "${workspaceFolder}",//表示当前工作文件夹
          "environment": [],
          "externalConsole": false,
          "MIMode": "gdb",
          "setupCommands": [
              {
                  "description": "为 gdb 启用整齐打印",
                  "text": "-enable-pretty-printing",
                  "ignoreFailures": true
              }
          ]
      }
      ]
  }
```
qixuanxuan
  ff

