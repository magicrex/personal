#include<iostream>

struct ListNode {
    int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
     };
class Solution {
public:
    ListNode* mysort(ListNode* left){
        if(left->next==NULL)
            return left;
        ListNode* fast=left;
        ListNode* slow=left;
        while(fast->next!=NULL&&fast->next->next!=NULL){
            fast=fast->next->next;
            slow=slow->next;
        }

        fast=slow->next;
        slow->next=NULL;
        ListNode* first=mysort(left);
        ListNode* second=mysort(fast);

        ListNode* newhead=new ListNode(-1);
        newhead->next=first;
        ListNode* p=newhead;
        while(first!=NULL&&second!=NULL){
            if(first->val <= second->val){
                p->next=first;
                p=p->next;
                first=first->next;
            }else{
                p->next=second;
                p=p->next;
                second=second->next;
            }
        }
        if(first==NULL){
            p->next=second;
        }else{
            p->next=first;
        }
        return newhead->next;
    }
    ListNode *sortList(ListNode *head) {
       if(head==NULL)
           return NULL;
        ListNode* ret=mysort(head);
        return ret;
    }

};
int main(){
    ListNode* n1=new ListNode(2);
    ListNode* n2=new ListNode(1);
    ListNode* n3=new ListNode(3);
    ListNode* n4=new ListNode(4);
    ListNode* n5=new ListNode(5);
    n1->next=n2;
    n3->next=n4;
    n4->next=n5;
    Solution* s=new Solution();
    ListNode* ret=s->sortList(n1);
    while(ret!=NULL){
        std::cout<<ret->val<<" ";
        ret=ret->next;
    }
    std::cout<<std::endl;
    return 0;
}
