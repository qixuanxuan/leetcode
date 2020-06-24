/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    // 小根堆的回调函数
    struct cmp{  
       bool operator()(ListNode *a,ListNode *b){
          return a->val > b->val;
		}
    };

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        priority_queue<ListNode*, vector<ListNode*>, cmp > pri_queue;
        // 建立大小为k的小根堆
        for(auto elem : lists){
            if(elem) pri_queue.push(elem);
        }
        // 可以使用哑节点/哨兵节点
        ListNode dummy(-1);
        ListNode* p = &dummy;
        // 开始出队
        while(!pri_queue.empty()){
            ListNode* top = pri_queue.top(); pri_queue.pop();
            p->next = top; p = top;
            if(top->next) pri_queue.push(top->next);
        }
        return dummy.next;  
    }
};


