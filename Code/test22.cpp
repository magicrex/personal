#include<iostream>
using namespace std;
#include<vector>
struct TreeNode {
         int val;
         TreeNode *left;
         TreeNode *right;
         TreeNode(int x) : val(x), left(NULL), right(NULL) {}
     };
class Solution {
public:
    int Findpos(vector<int> array,int value,int svin,int evin){
        int pos=0;
        for(pos=svin;pos<=evin;pos++){
            if(array[pos]==value)
                break;
        }
        return pos;
    }

    TreeNode*  constructtree(vector<int> pre,int spre,int epre,vector<int> vin,int svin,int evin){
        if(spre>epre){
            return NULL;
        }
        int value=pre[spre];
        TreeNode* root = new TreeNode(value);
        int pos=Findpos(vin,value,svin,evin);
        int leftlen=pos-svin;
        int rightlen=evin-pos;
        root->left=constructtree(pre,spre+1,spre+leftlen,vin,svin,pos-1);
        root->right=constructtree(pre,spre+leftlen+1,epre,vin,pos+1,evin);
        return root;
    } 

    TreeNode* reConstructBinaryTree(vector<int> pre,vector<int> vin) {
        if(pre.size()==0)
            return NULL;
        if(vin.size()==0)
            return NULL;
        int len=pre.size();
        TreeNode* proot=constructtree(pre,0,len-1,vin,0,len-1);
        return proot;
    }

};
