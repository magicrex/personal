#include<iostream>
using namespace std;
#include<stack>
class Solution
{
public:
    void push(int node) {
        stack1.push(node); 
    }

    int pop() {
        if(stack1.size()==0)
            return stack1.top();
        while(stack1.size()!=0){
            int tmp=stack1.top();
            stack2.push(tmp);
            stack1.pop();
        }
        int num=stack2.top();
        stack2.pop();
        while(stack2.size()!=0){
            int tmp=stack2.top();
            stack1.push(tmp);
            stack2.pop();
        }
        return num;
    }

private:
        stack<int> stack1;
        stack<int> stack2;

};
