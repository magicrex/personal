#include<iostream>
#include"hello.pb.h"
using namespace std;
int main(){
    hello::Request request;
    request.set_method("GET");
    return 0;
}

