#include<iostream>
#include"testDB.hpp"
using namespace std;


int main(){
    cout<<insertmessage("test2","fff")<<endl;
    cout<<deleteaddr("message","test")<<endl;
    cout<<updatemessage("root","fuxing")<<endl;;
    cout<<createtable("fuxing");
    return 0;
}
