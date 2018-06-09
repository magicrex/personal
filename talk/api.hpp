#pragma once
#include<string>
namespace server{


struct Data{
    std::string name;
    std::string school;
    std::string msg;
    std::string cmd;
    
    void Serialize(std::string* output){
        char buf[1024]={0};
        sprintf(buf,"{name:%s,school:%s,msg:%s,cmd:%s}",
                name.c_str(),school.c_str(),msg.c_str(),cmd.c_str());
        *output=buf;
        return ;
    }

    void UnSerialize(std::string& input){
        return ;
    }


};
};//end namespace server
