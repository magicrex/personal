//2018-5-23 字符串替换，将空格替换为%20
#include<iostream>
#include<stdlib.h>
using namespace std;

class Replacement{
public:
    string replaceSpace(string iniString,int length){
        string str;
        string::iterator it=iniString.begin();
        while(it!=iniString.end()){
            if((*it)!=' '){
                str.push_back(*it);
                it++;
                length--;
            }else{
                str.push_back('\%');
                char a=2+'0';
                str.push_back(a);
                str.push_back('0');
                it++;
                length--;
            }
        }
        while(length!=0){
            str.push_back('\%');
            char a=2+'0';
            str.push_back(a);
            str.push_back('0');
            length--; 
        }
        return str;
    }
};
