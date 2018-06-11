#include<iostream>

 struct ListNode {
         int val;
         ListNode *next;
         ListNode(int x) : val(x), next(NULL) {}
     };


 struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     };

class Solution {
public:

    TreeNode* to(ListNode* left){
        if(left->next==NULL){
            TreeNode* newnode=new TreeNode(left->val);
            return newnode;
        }
        ListNode* fast=left;
        ListNode* slow=left;
        while(fast->next!=NULL&&fast->next->next!=NULL&&fast->next->next->next!=NULL){
            fast=fast->next->next;
            slow=slow->next;
        }

        ListNode* ret=slow->next;
        TreeNode* newnode=new TreeNode(ret->val);
        
        slow->next=NULL;
        newnode->left=to(left);

        if(ret->next!=NULL){
            fast=ret->next;
            ret->next=NULL;
            newnode->right=to(fast);
        }

        return newnode;
    }
    TreeNode *sortedListToBST(ListNode *head) {
        TreeNode* root=to(head);
        return root;

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
    Solution* s=new Solution();
    TreeNode* ret=s->sortedListToBST(n1);
    return 0;
}
