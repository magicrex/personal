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

    dict.SetValue("UPMESS",message);

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

//    //将所有内容输出到标准输出
   ctemplate::Template* tpl = ctemplate::Template::GetTemplate("/home/master/Git/httpserver/wwwroot/resume_cgi.tpl",ctemplate::DO_NOT_STRIP);
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
    //根据sessid读取对应的文件
    std::string cachepath("./wwwroot/cache/");
    cachepath=cachepath+sessid;
    std::ifstream pread(cachepath.c_str(),std::ios::in);
    std::string filepath("./wwwroot/AllFile/");
    filepath=filepath+username+"/";
    //读取整个文件的内容
    char c='\0';
    int flag=0;
    std::string firstring,filename;
    while(!pread.eof()){
        c=pread.get();
        //如果dflag为4来就是文件内容
        if(flag>4){
            Error("文件解析出错");
            return 0;
        }else if(flag==4){
            std::ofstream pin(filepath.c_str(),std::ofstream::out);
            pin << c;
            while(!pread.eof()){
                c=pread.get();
                pin << c;
            }
            pin.close();
            std::string testfile;
            testfile="./wwwroot/AllFile/"+username+"/"+filename;
            if(access(testfile.c_str(),F_OK)!=0){
                Error("文件不存在");
                return 0;
            }
            filepath="http://192.168.16.129:9090/AllFile/"+username+"/"+filename;
            if(resumeinsert(username.c_str(),filename.c_str(),filepath.c_str(),"无")){
                Info(username,"上传成功");
               // HttpResponse("上传成功");
                return 0;
            }else{
                std::string e("上传失败，文件已存在");
                Error(e.c_str());
                return 0;
            }
        }else if(flag<4&&c=='\r'){
            //第零行和第三行不处理
            if(flag==1){
                //第一行进行;解析，取出filename
                std::vector<std::string> output;
                std::string tmp;
                StringUtil::Split(firstring,";=\"",&output);
                filename=output[(int)output.size()-2];
                filepath=filepath+filename;
            }else if(flag==2){
                //第二行进行/解析取出文件类型
                std::vector<std::string> output;
                std::string tmp;
                StringUtil::Split(firstring,"/",&output);
                tmp=output[1];
                std::string type("pdf");
                int compareret=tmp.compare(0,3,"pdf");
                if(compareret!=0){
                    Info(username,"文件格式错误");
                    return 0;
                }
            }
            firstring.clear();
            ++flag;
        }else{
            firstring.push_back(c);
        }
    }
    return 0;
}
