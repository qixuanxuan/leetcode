/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */

class Solution {
public:
    ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
        ListNode* p1;
		ListNode* p2;
		ListNode* result;
		ListNode* temp;
		if(l1==NULL) return l2;
		if(l2==NULL) return l1;
		p1 = l1;
		p2 = l2;
		if(p2->val<=p1->val){
			temp = p2->next;  
			p2->next = p1;
			result = p2;
			p1 = result;
			p2 = temp;
		}
        result = p1;
		while(p1!=NULL && p2!=NULL){
			if(p2->val<p1->val){
                p1 = p1->next;
            } 
			else{
				while( p1->next!=NULL && p2->val >= p1->next->val) p1 = p1->next;
				if(p1->next==NULL){
					
					p1->next = p2;
					break;
				}
				temp = p2->next;
				p2->next = p1->next;
				p1->next = p2;
				p1 = p2;
				p2 = temp;
			}
		}
		return result;
    }
};