#include<iostream>
#include<gflags/gflags.h>


//定义命令行参数之后可以为其定义一个检查函数
//需要自己定义一个检查函数，然后通过库方法进行检查
static bool ValidatePort(const char* flagname,gflags::int32 value){
    if(value > 0 && value < 32768)   // value is ok
             return true;
    std::cout<<"Invalid value for --"<<flagname<<":"<<(int)value<<std::endl;
          return false;
}

//命令行参数名 参数的默认值 参数的提示信息
DEFINE_bool(isvip,false,"If Is VIP");
DEFINE_string(ip,"127.0.0.1","connect ip");
DEFINE_int32(port,80,"listen port");
static const bool port_dummy = gflags::RegisterFlagValidator(&FLAGS_port, &ValidatePort);
//当在文件中使用另一个文件中的命令行参数，不包括头文件
DECLARE_int32(port);

int main(int argc,char* argv[]){
    //初始化
    //第三个参数
    //如果设为true，则该函数处理完成后，argv中只保留argv[0]，argc会被设置为1
    //如果为false，则argv和argc会被保留，但是注意函数会调整argv中的顺序。
    google::ParseCommandLineFlags(&argc,&argv,true);
    std::cout<<FLAGS_port<<std::endl;
    return 0;
}

