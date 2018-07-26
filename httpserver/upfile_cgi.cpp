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

//用来处理错误
void Error(const char* str_error){

}

int main(int argc,char* argv[],char* env[]){
   const char* method=getenv("REQUEST_METHOD");
   if(method == NULL){
       HttpResponse("1  No Env Method");
       return 0;
   }
   //检查是否是POST
   char buf[1024*10];
   if(std::string(method)=="POST"){
       read(0,buf,sizeof(buf)-1);
   }else{
       Error("未知错误");
       return 0;
   }
   //进行Cookie检查
   const char* str_sessid=getenv("COOKIESESSID");
   std::string sessid(str_sessid),username;
   if(sessid.empty()){
       Error("未知错误");
       return 0;
   }else{
        username=selectcookie(sessid.c_str());
        if(username.empty()){
            Error("未知错误");
            return 0;
        }else{
            if(selectcookiestatus(sessid.c_str())){
                ;
            }else{
                Error("请重新登录");
                return 0;
            }
        }

   }
   //进行contenttype检查
   const char* str_conttype=getenv("CONTENT_TYPE");
   std::string conttype(str_conttype);
   std::string dtype("multipart/form-data");
   if(conttype.empty()){
       Error("未知错误");
       return 0;
   }else{
       if(conttype.c_str()==dtype){
            ;
       }else{
           Error("未知错误");
           return 0;
       }
   }

   const char* str_boundry=getenv("BOUNDRY");
   std::string boundry(str_boundry);
   if(boundry.empty()){
       Error("未知错误");
       return 0;
   }else{
        boundry="--" + boundry;
   }

   std::vector<std::string> output;
   int ret=StringUtil::Split_Regex(buf)

}
