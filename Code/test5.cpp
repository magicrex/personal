#include<iostream>


struct ListNode {
    int val;
    struct ListNode *next;
    ListNode(int x) :
        val(x), next(NULL) {

        }

};

class Solution {
public:
    void relocateList(struct ListNode* head) {
        if(head==NULL||head->next==NULL||head->next->next==NULL||head->next->next->next==NULL)
            return ;
        struct ListNode* pfast=head;
        struct ListNode* pslow=head;

        while(pfast->next!=NULL&&pfast->next->next!=NULL){
            pfast=pfast->next->next;
            pslow=pslow->next;
        }
        if(pfast->next!=NULL)
            pslow=pslow->next;

        struct ListNode* pleft=head;
        struct ListNode* pright=pslow;
        struct ListNode* pend=pright;
        while(pleft->next!=pend)
        {
            struct ListNode* node=pright;
            pright=pright->next;
            node->next=pleft->next;
            pleft->next=node;
            pleft=node->next;
        }
        pleft->next=pright;
        return ;
    }

};

int main(){
    struct ListNode* n1=new ListNode(1); 
    struct ListNode* n2=new ListNode(2); 
    struct ListNode* n3=new ListNode(3); 
    struct ListNode* n4=new ListNode(4); 
    struct ListNode* n5=new ListNode(5); 
    n1->next=n2;
    n2->next=n3;
    n3->next=n4;
   n4->next=n5;
   Solution* s=new Solution();
   s->relocateList(n1);
   struct ListNode* p=n1;
   while(p!=NULL){
       std::cout<<p->val<<" ";
       p=p->next;
   }
    std::cout<<std::endl;
   return 0;
}
