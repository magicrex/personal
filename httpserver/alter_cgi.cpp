
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

   std::string username,oldpass,newpass;
   username=parmas["username"];
   oldpass=parmas["oldpass"];
   newpass=parmas["newpass"];
    
//**********************************************
//*************测试使用*************************
//**********************************************
//        std::string username,password;
//        std::cin>>username;
//        std::cin>>password;
//**********************************************

    //判断参数,如果两者任意一个为空，就结束
    ctemplate::TemplateDictionary dict("login");
    if(username.empty()||password.empty()){
        if(username.empty())
            dict.SetValue("usermess","用户名为空");
        if(oldpass.empty())
            dict.SetValue("oldpass","旧密码为空");
        if(newpass.empty())
            dict.SetValue("newpass","新密码为空");
        goto END;
    }

    //三者都有值
    if(selectmessage(username.c_str())){
        //用户名存在
        if(selectpassword(username.c_str(),password.c_str())){
            if(loginfun(username)){
                return 0;
            }else{
                Log(ERROR)<<"login false"<<"\n";
            }
        }else{
            dict.SetValue("passmess","密码错误");
        }
    }else{
        dict.SetValue("usermess","用户不存在");
    }
END:
    ctemplate::Template* tpl=ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/login_cgi.tpl",ctemplate::DO_NOT_STRIP);

    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
    return -1;
}
