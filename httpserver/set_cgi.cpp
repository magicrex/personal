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

    std::vector<std::vector<std::string> > table1;
    std::vector<std::vector<std::string> > table3;
    //将信息读到一个字符串数组中
    table1=resumeselect(username.c_str());
    table3=projectselect(username.c_str());
    int len1=table1.size();
    int len3=table3.size();
    //开始将信息填入模板中
    ctemplate::TemplateDictionary dict("personal");
    //将姓名读入标题

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

    dict.SetValue("SETMESS",message);

    //将所有内容输出到标准输出
    ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/set_cgi.tpl",ctemplate::DO_NOT_STRIP);
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

    if(!setdelete(username.c_str())){
        Error("未知数据表");
        return 0;
    }
    if(!setcreate(username.c_str())){
        Error("数据表创建失败");
        return 0;
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
        int outlen=output.size();
        for(int i=0;i<outlen;i++){
            if(i==0){
                output[0].pop_back();
                output[0].pop_back();
                if(setinsert(username.c_str(),output[0].c_str(),"resume")){
                    
                }else{
                    std::stringstream ss;
                    ss<<i;
                    ss<<"set 数据库 未知错误";
                    Error(ss.str().c_str());
                    return 0;
                }
            }else{
                output[i].pop_back();
                output[i].pop_back();
                if(setinsert(username.c_str(),output[i].c_str(),"project")){
                    
                }else{
                    std::stringstream ss;
                    ss<<i;
                    ss<<"set 数据库 未知错误";
                    ss<<output[i].c_str();
                    Error(ss.str().c_str());
                    return 0;
                }
            }
        }
        Info(username.c_str(),"设置成功");
        return 0;
    }
    return 0;
}
