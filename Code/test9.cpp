//2018-5-29 正则表达式匹配
#include<iostream>
//只匹配字符

class Solution{
public:
    bool match(char* str,char* pattren){
        char* p1=str;
        char* p2=pattren;
        while(*p1!='\0'&&*p2!='\0'){
            if(*p1=='.'||*p2=='.'){

            }else if(*p1=='*'||*p2=='*'){

            }else{

            }
        }

        return true;
    }
};
