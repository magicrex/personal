#include<iostream>
#include<vector>
#include<stack>
class Solution {
public:
    bool IsPopOrder(std::vector<int> pushV,std::vector<int> popV) {
        if(pushV.size()==0)
            return true;
        //使用一个辅助栈，当出栈顺序遍历结束后，如果栈为空说明成功
        //当栈顶元素与出栈值相等就出栈，出栈序列后移，如果不等就
        //继续讲入栈链表入栈
        std::stack<int>  s;
        for(int i=0,j=0;i<(int)pushV.size();){
            if(s.empty()||s.top()!=popV[j]){
                s.push(pushV[i]);
                ++i;
            }
            while(!s.empty()&&s.top()==popV[j]){
                s.pop();
                ++j;
            }
        }
        return s.empty();
    }

};
