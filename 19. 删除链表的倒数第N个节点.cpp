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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        ListNode* p1;
		ListNode* p2;
		int i = 1;
		
		p1 = head;//p1指针
		p2 = head;//p2指针
		while(i<n && p2->next != NULL){
			i++;
			p2 = p2->next;
		}//p2指针比p1指针快n-1步
			
		if(p2->next == NULL && i<n) return head;//链表长度小于n
		if(p2->next == NULL && i==n) return head->next;//链表长度恰好等于n
		//p2指针比p1指针快n步,以此来获取删除节点的前一节点的指针
		p2 = p2->next;
		while(p2->next!=NULL){
			p1 = p1->next;
			p2 = p2->next;
		}
		p1->next = p1->next->next;
		return head;
    }
};