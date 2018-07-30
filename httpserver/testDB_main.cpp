#include<iostream>
//#include"testDB.hpp"
#include"DBoperate.hpp"
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
//    cout<<insertcookie("root","SESSID=asdfghjkl")<<endl;
//    cout<<selectcookie("SESSID=asdfghjkl")<<endl;
//    cout<<updatecookie("root")<<endl;
    if(insertaddr("root","3.9.Linux进程间关系和守护进程.pdf","heeekeke","无","个人简历")){
        cout<<"true"<<endl;
    }else
        cout<<"false"<<endl;
    return 0;

}
