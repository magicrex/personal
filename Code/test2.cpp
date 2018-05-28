//2018-5-23 字符串替换，将空格替换为%20
#include<iostream>
#include<stdlib.h>
using namespace std;

//class Replacement{
//public:
//    string replaceSpace(string iniString,int length){
//        string str;
//        string::iterator it=iniString.begin();
//        while(it!=iniString.end()){
//            if((*it)!=' '){
//                str.push_back(*it);
//                it++;
//                length--;
//            }else{
//                str.push_back('\%');
//                char a=2+'0';
//                str.push_back(a);
//                str.push_back('0');
//                it++;
//                length--;
//            }
//        }
//        while(length!=0){
//            str.push_back('\%');
//            char a=2+'0';
//            str.push_back(a);
//            str.push_back('0');
//            length--; 
//        }
//        return str;
//    }
//};
//////////////////////////////////////////////////////////////////
//将空格替换为%20,因为时间复杂度，所以替换是从后往前替换
//错误一两个指针同时向前移
//错误二必修将最后一个置为'\0'
////////////////////////////////////////////////////////////////////

class Replacement{
public:
    void replaceSpace(char *iniString,int length){
    //首先遍历整个数组，计算出替换之后的大小
    int NewSize=0;
    for(int i=0;i<length;i++){
        if(iniString[i]==' '){
            NewSize+=3;
        }else{
            NewSize+=1;
        }
    }
    iniString[NewSize]='\0';
    NewSize--;
    for(int i=length-1;i>=0&&i!=NewSize;i--){
        if(iniString[i]==' '){
            iniString[NewSize]='0';
            NewSize--;
            iniString[NewSize]='2';
            NewSize--;
            iniString[NewSize]='%';
            NewSize--;
        }else{
            iniString[NewSize]=iniString[i];
            NewSize--;
        }
    }
    }
};

int main(){
    char s[]="hello Wrold";
    Replacement r;
    cout<<s<<endl;
    r.replaceSpace(s,11);
    cout<<s<<endl;
    return 0;
}
