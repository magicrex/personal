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

void Error(std::string message){
    std::string body;
    body="<html><head><meta charset=\"utf8\"><title>Error</title></head><body><h1>"+message+"</h1></body></html>";
    HttpResponse(body);
}

void showfun(std::string username){
    //用来处理已经验证成功的情况
    std::vector<std::vector<std::string> > table1;
    std::vector<std::vector<std::string> > table2;
    std::vector<std::vector<std::string> > table3;
    //将信息读到一个字符串数组中
    table1=setselect(username.c_str());
    table2=resumeselect(username.c_str());
    table3=projectselect(username.c_str());
    int len1=table1.size();
    int len2=table2.size();
    int len3=table3.size();
    //开始将信息填入模板中
    ctemplate::TemplateDictionary dict("personal");
    //将姓名读入标题
    dict.SetValue("USERNAME",username.c_str());
    //字符串数组输出
    std::string title;
    for(int i=0;i<len1;i++){
        if(table1[i][1]=="resume"){
            title=table1[i][0];
            break;
        }
    }
    //个人简历模块
    Log(ERROR)<<title.c_str()<<"\n";
    std::string resume=resumeselecturl(username.c_str(),title.c_str());
    Log(ERROR)<<resume.c_str()<<"\n";
    dict.SetValue("FILEURL",resume.c_str());
    //学习笔记模块
    for(int i=0;i<len2;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("NOTES");
        p->SetValue("value1",table2[i][0].c_str());
        p->SetValue("value2",table2[i][1].c_str());
        p->SetValue("value3",table2[i][2].c_str());
        p->SetValue("value4",table2[i][3].c_str());
    }
    if(1){
       dict.ShowSection("NOTES"); 
    }
    //项目练习模块
    for(int i=0;i<len1;i++){
        if(table1[i][1]=="project"){
            for(int j=0;j<len3;j++){
                if(table1[i][0]==table3[j][0]){
                    ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("PROJECT");
                    p->SetValue("value1",table3[j][0].c_str());
                    p->SetValue("value2",table3[j][1].c_str());
                    p->SetValue("value3",table3[j][2].c_str());
                    p->SetValue("value4",table3[j][3].c_str());
                    p->SetValue("value5",table3[j][4].c_str());
                    p->SetValue("value6",table3[j][5].c_str());
                }
            }
        }
    }
    if(1){
        dict.ShowSection("PROJECT"); 
    }
    //将所有内容输出到标准输出
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/show.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
}

int main(){

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
        Error("POST 失败");
        return 0;
    }

    std::string username;
    username=parmas["username"];
    if(username.empty()){
        Error("用户名为空");
        return 0;

    }
    if(userselect(username.c_str())){
        //用户名存在
        showfun(username);
        return 0;
    }else{
        Error("用户名不存在");
        return 0;
    }
    return 0;
}
