#include<iostream>
#include<string>
#include"util.hpp"
        
void HttpResponse(const std::string& body){
    std::cout<<"Content-Length:"<<body.size()<<"\n";
    std::cout<<"\n";
    std::cout<<body;
}


int main(int argc,char* argv[],char* env[]){

    //
    //先获取到 method
    //如果是 GET  请求，从QUERY_STRING 读取请求差数
    //如果是 POST 请求，读取CONTENT_LENGTH 和从标准输入读取body主体中的内容
    //解析请求参数 或者 body中的参数
    //根据业务请求，计算a+b的值
    //根据计算结果，构造响应的数据，写回到标准输出
    const char* method=getenv("REQUEST_METHOD");
    if(method == NULL){
        HttpResponse("No ENV METHOD");
        return -1;
    }

    StringUtil::UrlParam parmas;
    if(std::string(method)=="GET"){
        const char* query_string=getenv("QUERY_STRING");
        Log(DEBUG)<<" 参数"<< query_string<<"\n";
        StringUtil::ParseUrlParan(query_string,&parmas);
    }else if(std::string(method) == "POST"){
       // const char* content_length=getenv("CONTENT_LENGTH");
        char buf[1024*10];
        read(0,buf,sizeof(buf)-1);
        Log(DEBUG)<<" 参数"<< buf<<"\n";
        StringUtil::ParseUrlParan(buf,&parmas);
    }
    
    int a=std::stoi(parmas["a"]);
    int b=std::stoi(parmas["b"]);
    int result=a+b;

    std::stringstream ss;
    ss<< "<h1> result =" << result << "</h1>" ;
    HttpResponse(ss.str());

    
    return 0;
}
