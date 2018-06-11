#include<iostream>

struct ListNode {
    int val;
    ListNode *next;
    ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode *rotateRight(ListNode *head, int k) {

        if(head==NULL||head->next==NULL){
            return head;
        }
        ListNode* p=head;
        ListNode* ret=head;
        int len=1;
        while(p->next!=NULL){
            len++;
            p=p->next;
        }
        p->next=head;
        int n=len-k%len;
        //边界值当n值为零时，表示没有移动
        for (int i = 0; i < n; ++i) {
            p = p->next;
        }
        ret=p->next;
        p->next=NULL;
        return ret;
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
    n3->next=n4;
    n4->next=n5;
    Solution* s=new Solution();
    ListNode* ret=s->rotateRight(n1,5);
    while(ret!=NULL){
        std::cout<<ret->val<<" ";
        ret=ret->next;
    }
    std::cout<<std::endl;
    return 0;
}
