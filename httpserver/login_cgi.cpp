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

bool loginfun(std::string username){
    //用来处理已经验证成功的情况
    std::vector<std::vector<std::string> > table1;
    std::vector<std::vector<std::string> > table2;
    std::vector<std::vector<std::string> > table3;
    //将信息读到一个字符串数组中
    table1=selectcontent(username.c_str(),"个人简历");
    table2=selectcontent(username.c_str(),"学习笔记");
    table3=selectcontent(username.c_str(),"项目练习");
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
        p->SetValue("value5",table1[i][4].c_str());
    }
    if(1){
       dict.ShowSection("RESUME"); 
    }
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
    //项目练习模块
    for(int i=0;i<len3;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("PROJECT");
        p->SetValue("value1",table3[i][0].c_str());
        p->SetValue("value2",table3[i][1].c_str());
        p->SetValue("value3",table3[i][2].c_str());
        p->SetValue("value4",table3[i][3].c_str());
        p->SetValue("value5",table3[i][4].c_str());
    }
    if(1){
       dict.ShowSection("PROJECT"); 
    }
    //将所有内容输出到标准输出
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/personal.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
    return true;
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

   std::string username,password;
   username=parmas["username"];
   password=parmas["password"];
    
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
        if(password.empty())
            dict.SetValue("passmess","密码为空");
        goto END;
    }

    //两者都有值
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
