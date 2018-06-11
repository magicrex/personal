#include<iostream>
#include<stack>

  struct TreeNode {
   int val;
       struct TreeNode *left;
           struct TreeNode *right;
               TreeNode(int x) :
                           val(x), left(NULL), right(NULL) {
                               }
                               };
class Solution {
public:
        TreeNode* Convert(TreeNode* pRootOfTree)
        {
            if(pRootOfTree==NULL||(pRootOfTree->left==NULL&&pRootOfTree->right==NULL))
                return pRootOfTree;
            TreeNode* pleft=pRootOfTree;
            std::stack<TreeNode*> v;
            v.push(pleft);
            while(pleft->left!=NULL){
                pleft=pleft->left;
                v.push(pleft);
            }
            TreeNode* head=v.top();
            TreeNode* pre=NULL;
            while(!v.empty()){
               TreeNode* tmp=v.top();
               TreeNode* pnext=NULL;
               if(tmp->right==NULL){
                    v.pop();
                    if(!v.empty())
                    pnext=v.top();
               }else{
                   v.pop();
                   pnext=tmp->right;
                   v.push(pnext);
                   while(pnext->left!=NULL){
                       pnext=pnext->left;
                       v.push(pnext);
                   }
               }
               tmp->left=pre;
               tmp->right=pnext;
               pre=tmp;
            }
            return head;
        }
};


int main(){
    TreeNode* n1=new TreeNode(1);
    TreeNode* n2=new TreeNode(2);
    TreeNode* n3=new TreeNode(3);
    TreeNode* n4=new TreeNode(4);
    TreeNode* n5=new TreeNode(5);
    TreeNode* n6=new TreeNode(6);
    TreeNode* n7=new TreeNode(7);
    TreeNode* n8=new TreeNode(8);
    n5->left=n4;
    n5->right=n7;
    n4->left=n2;
    n2->left=n1;
    n2->right=n3;
    n7->left=n6;
    n7->right=n8;
    Solution* s=new Solution();

    TreeNode* p=s->Convert(n5);
    while(p!=NULL){
        std::cout<<p->val<<" ";
        p=p->right;
    }
    std::cout<<std::endl;
    return 0;

}
