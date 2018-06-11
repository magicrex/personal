#include<iostream>


struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
     };
class Solution {
public:
    ListNode *addTwoNumbers(ListNode *l1, ListNode *l2) {
        if(l1==NULL)
            return l2;
        if(l2==NULL)
            return l1;
        int count=0;
        ListNode* newhead=new ListNode(-1);
        ListNode* p=newhead;

        while(l1!=NULL||l2!=NULL||count!=0){
            if(l1!=NULL){
                count+=l1->val;
                l1=l1->next;
            }
            if(l2!=NULL){
                count+=l2->val;
                l2=l2->next;
            }

            ListNode* newnode=new ListNode(count%10);
            p->next=newnode;
            p=p->next;
            count=count/10;
        }
        return newhead->next;
    }
};
int main(){
    ListNode* n1=new ListNode(1);
    ListNode* n2=new ListNode(2);
    ListNode* n3=new ListNode(3);
    ListNode* n4=new ListNode(4);
    ListNode* n5=new ListNode(5);
    n1->next=n2;
    n2->next=n3;
    ListNode* m1=new ListNode(1);
    ListNode* m2=new ListNode(2);
    ListNode* m3=new ListNode(3);
    ListNode* m4=new ListNode(4);
    ListNode* m5=new ListNode(5);
    m1->next=m2;
    m2->next=m3;
    m3->next=m4;
    Solution* s=new Solution();
    ListNode* ret=s->addTwoNumbers(n1,m1);
    while(ret!=NULL){
        std::cout<<ret->val<<" ";
        ret=ret->next;
    }
    std::cout<<std::endl;
    return 0;
}
