#include<iostream>
#include<string>
#include"util.hpp"
#include<ctemplate/template.h>
#include"DBoperate.hpp"
void HttpResponse(const std::string& body){
    std::cout<<"Content-Type: text/html"<<"\n";
    std::cout<<"Content-Length:"<<body.size()<<"\n";
    std::cout<<"\n";
    std::cout<<body;
}

void Error(const char* str_error){
    ctemplate::TemplateDictionary dict("error");
    dict.SetValue("ERROEMESS",str_error);
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/error.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
}
bool SetCookie(const char* name){
    std::string sessid=CookieUtil::GetCookie(name);
    if(cookieupdate(name)){
        if(cookieinsert(name,sessid.c_str())){
            std::cout<<"Set-Cookie:SESSID="<<sessid<<"\n";
            return true;
        }else{
            return false;
        }
    }else{
        return false;
    }
}

bool loginfun(std::string username){
    if(!SetCookie(username.c_str())){
        return false;
    }

    //用来处理已经验证成功的情况
    std::vector<std::vector<std::string> > table1;
    std::vector<std::vector<std::string> > table2;
    std::vector<std::vector<std::string> > table3;
    //将信息读到一个字符串数组中
    table1=resumeselect(username.c_str());
    table2=noteselect(username.c_str());
    table3=projectselect(username.c_str());
    int len1=table1.size();
    int len2=table2.size();
    int len3=table3.size();
    //开始将信息填入模板中
    ctemplate::TemplateDictionary dict("personal");
    //将姓名读入标题
    dict.SetValue("USERNAME",username.c_str());
    //字符串数组输出
    //个人简历模块
    for(int i=0;i<len1;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("RESUME");
        p->SetValue("value1",table1[i][0].c_str());
        p->SetValue("value2",table1[i][1].c_str());
        p->SetValue("value3",table1[i][2].c_str());
        p->SetValue("value4",table1[i][3].c_str());
    }
    if(1){
       dict.ShowSection("RESUME"); 
    }

    dict.SetValue("UPMESS","请上传PDF格式的文件");

    for(int i=0;i<len1;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("DELFILE");
        p->SetValue("value1",table1[i][0].c_str());
    }
    if(1){
       dict.ShowSection("DELFILE"); 
    }

    dict.SetValue("DELFMESS","建议下载之后，再删除文件");

    for(int i=0;i<len1;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("MODIMESS");
        p->SetValue("value1",table1[i][0].c_str());
    }
    if(1){
       dict.ShowSection("MODIMESS"); 
    }

    dict.SetValue("MESSMESS","简介字数少于20");

    //学习笔记模块
    for(int i=0;i<len2;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("NOTES");
        p->SetValue("value1",table2[i][0].c_str());
        p->SetValue("value2",table2[i][1].c_str());
        p->SetValue("value3",table2[i][2].c_str());
        p->SetValue("value4",table2[i][3].c_str());
        p->SetValue("value5",table2[i][4].c_str());
    }
    if(1){
       dict.ShowSection("NOTES"); 
    }

    for(int i=0;i<len2;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("DELNOTE");
        p->SetValue("value1",table2[i][0].c_str());
    }
    if(1){
       dict.ShowSection("DELNOTE"); 
    
    }

    dict.SetValue("DELNMESS","建议保存之后，再删除内容");

    //项目练习模块
    for(int i=0;i<len3;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("PROJECT");
        p->SetValue("value1",table3[i][0].c_str());
        p->SetValue("value2",table3[i][1].c_str());
        p->SetValue("value3",table3[i][2].c_str());
        p->SetValue("value4",table3[i][3].c_str());
        p->SetValue("value5",table3[i][4].c_str());
        p->SetValue("value6",table3[i][5].c_str());
    }
    if(1){
       dict.ShowSection("PROJECT"); 
    }


    for(int i=0;i<len3;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("DELPROJ");
        p->SetValue("value1",table3[i][0].c_str());
    }
    if(1){
       dict.ShowSection("DELPROJ"); 
    }

    dict.SetValue("DELPMESS","建议保存之后，再删除内容");

    for(int i=0;i<len1;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("SETRESU");
        p->SetValue("value1",table1[i][0].c_str());
    }
    if(1){
       dict.ShowSection("SETRESU"); 
    }


    for(int i=0;i<len3;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("SETPROJ");
        p->SetValue("value1",table3[i][0].c_str());
    }
    if(1){
       dict.ShowSection("SETPROJ"); 
    }

    dict.SetValue("SETMESS","将根据你的设置进行展示内容");

    //将所有内容输出到标准输出
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/personal.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
    return true;
}

int main(){

   const char* method=getenv("REQUEST_METHOD");
   if(method == NULL){
       Error("No Env Method");
       return 0;
   }

   StringUtil::UrlParam parmas;
   if(std::string(method)=="GET"){
        Error("GET方法 无法登陆");
        return 0;
   }
   else if(std::string(method)=="POST"){
       char buf[1024*10];
       read(0,buf,sizeof(buf)-1);
       StringUtil::ParseUrlParan(buf,&parmas);
   }

   std::string username,password;
   username=parmas["username"];
   password=parmas["password"];
    

    //判断参数,如果两者任意一个为空，就结束
    ctemplate::TemplateDictionary dict("login");
    if(username.empty()||password.empty()){
        if(username.empty())
            dict.SetValue("usermess","用户名为空");
        if(password.empty())
            dict.SetValue("passmess","密码为空");
        goto END;
    }

    //两者都有值
    if(userselect(username.c_str())){
        //用户名存在
        if(userselectpass(username.c_str(),password.c_str())){
            if(loginfun(username)){
                return 0;
            }else{
                Error("ctemplate error");
                return 0;
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
