#include<iostream>
#include<string>
#include"util.hpp"
#include<ctemplate/template.h>
#include"DBoperate.hpp"
void HttpResponse(const std::string& body){
    std::cout<<"Content-Length:"<<body.size()<<"\n";
    std::cout<<"\n";
    std::cout<<body;

}

int main(int argc,char* argv[],char* env[]){

   const char* method=getenv("REQUEST_METHOD");
   if(method == NULL){
       HttpResponse("1  No Env Method");
       return 0;
   }

   StringUtil::UrlParam parmas;
   if(std::string(method)=="GET"){
       const char* query_string=getenv("QUERY_STRING");
       StringUtil::ParseUrlParan(query_string,&parmas);
   }
   else if(std::string(method)=="POST"){
       char buf[1024*10];
       read(0,buf,sizeof(buf)-1);
       StringUtil::ParseUrlParan(buf,&parmas);
   }
}
