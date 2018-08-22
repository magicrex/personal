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

//用来处理错误
void Error(const char* str_error){
    ctemplate::TemplateDictionary dict("error");
    dict.SetValue("ERROEMESS",str_error);
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/error.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
}

//正确输出
void Info(std::string username,const char* message){

    std::vector<std::vector<std::string> > table2;
    //将信息读到一个字符串数组中
    table2=noteselect(username.c_str());
    int len2=table2.size();
    //开始将信息填入模板中
    ctemplate::TemplateDictionary dict("personal");
    dict.SetValue("ADDNOTE",message);
    //字符串数组输出

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

    //将所有内容输出到标准输出
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/note_cgi.tpl",ctemplate::DO_NOT_STRIP);
    std::string output;
    tpl->Expand(&output,&dict);
    HttpResponse(output);
    ctemplate::Template::ClearCache();
}
int main(){
    const char* method=getenv("REQUEST_METHOD");
    if(method == NULL){
        Error("No Env Method");
        return 0;
    }
    //检查是否是POST
    if(std::string(method)!="POST"){
        Error("非POST方法 无法上传");
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
    //读取长度
    const char* contlen=getenv("CONTENT_LENGTH");
    std::string con(contlen);
    if(con.empty()){
        Error("未知Content-Length");
        return 0;
    }
    //进行contenttype检查
    const char* str_conttype=getenv("CONTENT_TYPE");
    std::string conttype(str_conttype);
    std::string dtype("multipart/form-data");
    if(conttype.empty()){
        Error("Content-Type不存在");
        return 0;
    }else{
        if(conttype.c_str()!=dtype){
            Error("Content-Type错误");
            return 0;
        }
    }

    //读取分割符
    const char* str_boundry=getenv("BOUNDRY");
    std::string boundry(str_boundry);
    if(boundry.empty()){
        Error("");
        return 0;
    }else{
        boundry="--"+boundry;
    }

    //读取文件内容
    std::string cachepath("./wwwroot/cache/");
    cachepath=cachepath+sessid;
    std::ifstream pread(cachepath.c_str(),std::ios::in);
    char c= '\0';
    std::string qbody;
    while(!pread.eof()){
        c=pread.get();
        qbody.push_back(c);
    }
    if(qbody.empty()){
        Error("");
        return 0;
    }else{
        std::vector<std::string> input;
        StringUtil::Split_Regex(qbody,boundry,&input);
        int len=input.size()-1;
        std::vector<std::string> output;
        for(int i=1;i<len;i++){
            int flag=0;
            std::string tmp;
            std::string::iterator it=input[i].begin();
            while(it!=input[i].end()){
                c=*it;
                if(flag<3){
                    if(c=='\n'){
                        it++;
                        flag++;
                    }else{
                        it++;
                    }
                }else{
                    tmp.push_back(c);
                    it++;
                }
            }
            output.push_back(tmp);
        }
        std::string title(output[0]);
        title.pop_back();
        title.pop_back();
        std::string message(output[1]);
        std::string classn(output[2]);
        std::string urln(output[3]);
        if(noteinsert(username.c_str(),title.c_str(),message.c_str(),classn.c_str(),urln.c_str())){
            Info(username.c_str(),"插入成功");
            return 0;
        }else{
            Error("note 数据库 未知错误");
            return 0;
        }
    }
    return 0;
}
