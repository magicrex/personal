#include<iostream>
#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<fcntl.h>
using namespace std;

int main(){
    if((access("./upfile_cgi",F_OK))!=-1){
        cout <<"wenjian cunzai"<<endl;
        if((access("./upfile_cgi",X_OK))!=-1){
            cout<<"kezhixing"<<endl;
        }else{
            cout<<"bukezhixing"<<endl;
        }
    }else{
        cout<<"wenjian bucunzai"<<endl;
    }
    if((access("./upfile_cgi.cpp",F_OK))!=-1){
        cout <<"wenjian cunzai"<<endl;
        if((access("./upfile_cgi.cpp",X_OK))!=-1){
            cout<<"kezhixing"<<endl;
        }else{
            cout<<"bukezhixing"<<endl;
        }
    }else{
        cout<<"wenjian bucunzai"<<endl;
    }
    return 0;
}
