//复杂链表的复制
//解决思路
//主要是将链表复制的节点连接在每个节点后面
//然后复制节点的特殊指针，指向的就是被复制节点的特殊指针的next
//需要注意链表为空的情况
//最后拆分时一个节点一个节点的拆
#include<iostream>
#include<vector>
#include<stack>

struct RandomListNode {
    int label;
    struct RandomListNode *next, *random;
    RandomListNode(int x) :
        label(x), next(NULL), random(NULL) {
        }
};

class Solution {
public:
    RandomListNode* Clone(RandomListNode* pHead)
    {
        //首先将链表复制
        if(pHead==NULL){
            return NULL;
        }
        RandomListNode* p=pHead;
        RandomListNode* newnode=NULL;
        while(p!=NULL){
            newnode=new RandomListNode((*p).label);
            newnode->next=p->next;
            p->next=newnode;
            p=newnode->next;
        }
        //改变特殊指针
        p=pHead;
        while(p!=NULL){
            newnode=p->next;
            if(p->random)
                newnode->random=p->random->next;
            p=newnode->next;
        }
        RandomListNode* ret=NULL;
        ret=pHead->next;
        p=pHead;
        while(p->next!=NULL){
            newnode=p->next;
            p->next=newnode->next;
            p=newnode;
        }
        return ret;
    }

};
