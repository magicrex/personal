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

void Error(const char* str_error){
    ctemplate::TemplateDictionary dict("error");
    dict.SetValue("ERROEMESS",str_error);
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/error.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
}

void Info(std::string username,const char* message){

    std::vector<std::vector<std::string> > table1;
    //将信息读到一个字符串数组中
    table1=resumeselect(username.c_str());
    int len1=table1.size();
    //开始将信息填入模板中
    ctemplate::TemplateDictionary dict("personal");
    //将姓名读入标题
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

    dict.SetValue("DELFMESS",message);

    for(int i=0;i<len1;i++){
        ctemplate::TemplateDictionary* p=dict.AddSectionDictionary("MODIMESS");
        p->SetValue("value1",table1[i][0].c_str());
    }
    if(1){
       dict.ShowSection("MODIMESS"); 
    }

    dict.SetValue("MESSMESS","简介字数少于20");

    //将所有内容输出到标准输出
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/resume_cgi.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
}

int main(){
    const char* method=getenv("REQUEST_METHOD");
    if(method == NULL){
        Error("1  No Env Method");
        return 0;
    }
    const char* query_string=getenv("QUERY_STRING");
    if(query_string == NULL){
        Error("1  No Env Method");
        return 0;
    }
    std::string filename;
    std::string querystr(query_string);
    std::vector<std::string> output;
    StringUtil::Split(querystr,"/",&output);
    filename=output[1];
    if(std::string(method)!="DELETE"){
        Error("非DELETE方法");
        return 0;
    }
    //进行Cookie检查
    const char* str_sessid=getenv("COOKIESESSID");
    std::string sessid(str_sessid),username;
    if(sessid.empty()){
        Error("没有Cookie信息");
        return 0;
    }else{
        username=cookieselect(sessid.c_str());
        if(username.empty()){
            Error("Cookie不存在");
            return 0;
        }else{
            bool m=cookieselectstatus(sessid.c_str());
            if(!m){
                Error("请重新登录");
                return 0;
            }
        }
    }
    
    //进行文件是否存在验证
    std::string file_path;
    file_path="./wwwroot/AllFile/"+username+query_string;
    if((access(file_path.c_str(),F_OK))!=-1){
        if((access(file_path.c_str(),X_OK))!=-1){
            Error("文件为可执行文件");
            return 0;
        }else{
            resumedelete(username.c_str(),filename.c_str());
            if(resumselectfile(username.c_str(),filename.c_str())){
                Error("resume数据库 未知错误");
                return 0;
            }

            if((unlink(file_path.c_str()))==0){
                Info(username,"删除成功");
                return 0;
            }else{
                Error("删除文件出错");
                return 0;
            }
        }
    }else{
        std::string e;
        e="文件不存在"+file_path;
        Error(e.c_str());
        return 0;
    }

    return 0;
}
