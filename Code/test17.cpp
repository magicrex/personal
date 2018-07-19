#include<iostream>
#include<stack>

using namespace std;

class Solution
{
public:
    void push(int node) {
        if(!stack1.empty()){
            stack1.push(node);
            return;
        }
        stack2.push(node);
    }

    int pop() {
        if(stack1.empty()){
            while(!stack2.empty()){
                int node=stack2.top();
                stack1.push(node);
                stack2.pop();
            }
            if(!stack1.empty()){
                int node=stack1.top();
                stack1.pop();
                return node;
            }
        }
        if(stack2.empty()){
            while(!stack1.empty()){
                int node=stack1.top();
                stack2.push(node);
                stack1.pop();
            }
            if(!stack2.empty()){
                int node=stack2.top();
                stack2.pop();
                return node;
            }
        }
        return stack1.top();
    }

private:
    stack<int> stack1;
    stack<int> stack2;

};
