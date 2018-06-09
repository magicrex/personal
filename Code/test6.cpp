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
            std::stack<TreeNode> v;
            v.push(*pleft);
            while(pleft->left!=NULL){
                pleft=pleft->left;
                v.push(*pleft);
            }
            TreeNode* head=&v.top();
            TreeNode* pre=NULL;
            while(!v.empty()){
               TreeNode* tmp=&v.top(); 
               if(tmp->left==NULL&&tmp->right==NULL){
                    v.pop();
                    TreeNode* pnext=&v.top();
                    tmp->left=pre;
                    tmp->right=pnext;
               }else{
                    if(tmp->right!=NULL){
                        pre=tmp;
                        v.pop();
                        TreeNode* pnew=tmp->right;
                        v.push(*pnew);
                        while(pnew->left!=NULL){
                            pnew=pnew->left;
                            v.push(*pnew);
                        }
                        pnew=&v.top();
                        pnew->left=tmp;
                    }else{
                        v.pop();
                    
                        TreeNode* pnew=&v.top();
                        tmp->right=pnew;

                    }
               }
            }

            return head;
        }

};

