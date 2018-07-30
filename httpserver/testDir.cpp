#include<iostream>
#include<sys/stat.h>
#include<sys/types.h>

int CreateDir(std::string name){
    std::string prepath=("./wwwroot/AllFile/");
    prepath=prepath+name;
    return mkdir(prepath.c_str(),S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
}


int main(){
    std::string name("root");
    int ret=CreateDir(name);
    std::cout<<ret<<std::endl;
    return 0;
}
