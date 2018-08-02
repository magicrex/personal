#include<iostream>
#include<string>
#include"util.hpp"
#include<ctemplate/template.h>
//#include"DBoperate.hpp"
#include"testDB.hpp"

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

void Info(std::string uername,std::string message){

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
        username=selectcookie(sessid.c_str());
        if(username.empty()){
            Error("Cookie不存在");
            return 0;
        }else{
            bool m=selectcookiestatus(sessid.c_str());
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
        }
    }else{
        std::string e;
        e="文件不存在"+file_path;
        Error(e.c_str());
        return 0;
    }

    //删除数据库
    deleteaddr(username.c_str(),filename.c_str());
    
    //删除文件
    int ret=unlink(file_path.c_str());
    if(ret!=0){
        Error("删除文件出错");
        return 0;
    }
    std::string message("删除成功");
    Info(username,message);
    return 0;
}
