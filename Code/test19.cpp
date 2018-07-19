#include<iostream>

struct TreeNode {
        int val;
        TreeNode *left;
        TreeNode *right;
        TreeNode(int x) : val(x), left(NULL), right(NULL) {}
    };
   
class Solution {
public:
    bool Tree(TreeNode* root,int& maxvalue,int& minvalue){
        if(root==NULL)
            return true;
        if()
        return true;
    }
    bool isValidBST(TreeNode *root) {
        if(root==NULL)
            return true;
        TreeNode* pre=NULL;
        return Tree(root,pre);

    }

};
