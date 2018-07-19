
#include<iostream>
#include<string>
#include"util.hpp"
#include<ctemplate/template.h>
#include"DBoperate.hpp"
    
int main(){
    //用来处理已经验证成功的情况
    std::vector<std::vector<std::string> > table1;
    table1=selectcontent(username.c_str(),"个人简历");
    int len=table1.size();
    ctemplate::TemplateDictionary dict("personal");
    dict.SetValue("USERNMAE",username.c_str());
    ctemplate::TemplateDictionary* p1=dict.AddSectionDictionary("RESUME");
    p1->SetValue("value1","标题");
    p1->SetValue("value2","备注");
    p1->SetValue("value3","标题");
    p1->SetValue("value4","时间");
    p1->SetValue("value5","下载");
    return true;
}
