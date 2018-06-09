#include<iostream>
//快慢指针第一次相遇之后
//fast重新指向开始
//两者都是以一步的速度走相遇之后就是入口节点
 struct ListNode {
     int val;
         struct ListNode *next;
             ListNode(int x) :
                     val(x), next(NULL) {
                         }
                         };
class Solution {
public:
        ListNode* EntryNodeOfLoop(ListNode* pHead)
        {
            if(pHead==NULL||pHead->next==NULL){
                return NULL;

            }
            ListNode* pfast=pHead;
            ListNode* pslow=pHead;
            while(pfast->next!=NULL&&pfast->next->next!=NULL){
                pslow=pslow->next;
                pfast=pfast->next->next;
                if(pslow==pfast){
                    pfast=pHead;
                    while(pfast!=pslow){
                        pfast=pfast->next;
                        pslow=pslow->next;

                    }
                    return pfast;
                }
            }
            return NULL;
        }
};


int main(){
    ListNode* n1=new ListNode(1);
    ListNode* n2=new ListNode(2);
    ListNode* n3=new ListNode(3);
    ListNode* n4=new ListNode(4);
    ListNode* n5=new ListNode(5);
    ListNode* n6=new ListNode(4);
    ListNode* n7=new ListNode(5);
    ListNode* n8=new ListNode(6);
    ListNode* n9=new ListNode(6);
    n1->next=n2;
    n2->next=n3;
    n3->next=n4;
    n4->next=n5;
    n5->next=n3;
    n6->next=n7;
    n7->next=n8;
    n8->next=n9;
    Solution* s=new Solution();
    s->EntryNodeOfLoop(n1);
}
