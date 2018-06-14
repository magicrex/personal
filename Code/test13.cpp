#include<iostream>



struct ListNode {
    int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
     };
class Solution {
public:
    ListNode *partition(ListNode *head, int x) {
        if(head==NULL)
            return NULL;
        ListNode* small=new ListNode(-1);
        ListNode* big=new ListNode(-1);
        ListNode* psmall=small;
        ListNode* pbig=big;
        ListNode* p=head;

        while(p!=NULL){
            if(p->val <  x){
                psmall->next=p;
                psmall=psmall->next;
                p=p->next;
            }else{
                pbig->next=p;
                pbig=pbig->next;
                p=p->next;
            }
        }
        pbig->next=NULL;
        //如果链表的最后一个值时小于x的话，pbig的next并没有置空
        psmall->next=big->next;

        return small->next;

    }

};
int main(){
    ListNode* n1=new ListNode(1);
    ListNode* n2=new ListNode(2);
    ListNode* n3=new ListNode(3);
    ListNode* n4=new ListNode(4);
    ListNode* n5=new ListNode(5);
    n2->next=n3;
    n3->next=n4;
    n4->next=n5;
    Solution* s=new Solution();
    ListNode* ret=s->partition(n1,0);
    while(ret!=NULL){
        std::cout<<ret->val<<" ";
        ret=ret->next;
    }
    std::cout<<std::endl;
    return 0;
}
