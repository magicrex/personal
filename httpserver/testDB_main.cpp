#include<iostream>
#include"testDB.hpp"
using namespace std;


int main(){
// cout<<insertmessage("test2","fff")<<endl;
// cout<<deleteaddr("message","test")<<endl;
// cout<<updatemessage("root","fuxing")<<endl;;
// cout<<createtable("fuxing");
// cout<<selectmessage("root")<<endl;
//cout<<selectpassword("root","fuxing")<<endl;
//    vector<vector<string> > v;
//    v=selectcontent("root","个人简历");
//    for(int i=0;i<3;i++){
//        for(int j=0;j<5;j++){
//            cout<<v[i][j]<<endl;
//        }
//    }
    cout<<insertcookie("root","SESSID=asdfghjkl")<<endl;
    cout<<selectcookie("SESSID=asdfghjkl")<<endl;
    cout<<updatecookie("root")<<endl;
    return 0;

}
