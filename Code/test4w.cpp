//2018-5-25 字符串的旋转
//字符串的左旋
//剑指offer 面试题42
//首先将所有字符串进行旋转再将部分旋转
//网上测试能过的基本是调用了函数
//错误：两个指针一个向后一个向前
#include<string>
#include<iostream>
using namespace std;
class StringRotation{
public:
    std::string rotateString(std::string A,int n,int p){
        int begin=0,end=A.size()-1;
        while(begin<end){
            char c=A[begin];
            A[begin]=A[end];
            A[end]=c;
            ++begin;
            --end;
        }
        int pos=n-p-1;
        begin=0;
        end=pos-1;
        while(begin<end){
            char c=A[begin];
            A[begin]=A[end];
            A[end]=c;
            ++begin;
            --end;
        }
        begin=pos;
        end=A.size()-1;
        while(begin<end){
            char c=A[begin];
            A[begin]=A[end];
            A[end]=c;
            ++begin;
            --end;
        }
        return A;
    }
};


int main(){
   StringRotation s;
   string b;
   b=s.rotateString("ABCDEFGH",8,4);
   cout<<b<<endl;
}
