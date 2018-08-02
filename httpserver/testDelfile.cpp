#include<iostream>
#include<unistd.h>
using namespace std;

int main(){
    int ret=unlink("./1.pdf");
    cout<<ret<<endl;
    return 0;
}
