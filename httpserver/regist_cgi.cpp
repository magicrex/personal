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

   std::string username,email,password;
   username=parmas["username"];
   email=parmas["email"];
   password=parmas["password"];
    
//**********************************************
//*************测试使用*************************
//**********************************************
//        std::string username,email,password;
//        std::cin>>username;
//        std::cin>>email;
//        std::cin>>password;
//**********************************************

    //判断参数,如果两者任意一个为空，就结束
    ctemplate::TemplateDictionary dict("login");
    if(username.empty()||password.empty()||email.empty()){
        if(username.empty())
            dict.SetValue("usermess","用户名为空");
        if(email.empty())
            dict.SetValue("emailmess","邮箱为空");
        if(password.empty())
            dict.SetValue("passmess","密码为空");
        goto END;
    }

    //判断姓名密码长度不超过20
    if(username.size()>20||password.size()>20||email.size()>20){
        if(username.size()>20)
            dict.SetValue("usermess","用户名长度超出范围");
        if(email.size()>20)
            dict.SetValue("emailmess","邮箱长度超出范围");
        if(password.size()>20)
            dict.SetValue("passmess","密码长度超出范围");
        goto END;
    }
    
    //两者都有值
    if(selectmessage(username.c_str())){
        //用户名存在
        dict.SetValue("usermess","用户已存在");
    }else{
        if(insertmessage(username.c_str(),password.c_str())){
            if(createtable(username.c_str())){
                if(DirUtil::CreateDir(username))
                    dict.SetValue("usermess","注册成功");
                else
                    dict.SetValue("usermess","未知错误");
            }else{
                dict.SetValue("usermess","用户已存在");
            }
        }else{
            dict.SetValue("usermess","未知错误");
        }
    }
END:
    ctemplate::Template* tpl=ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/regist_cgi.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
    return -1;
}
