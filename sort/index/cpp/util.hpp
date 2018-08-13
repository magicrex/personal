#pragma once
#include<string>
#include<vector>
#include<boost/algorithm/string.hpp>
#include<unordered_set>
#include<ifstream>
namespace common{

class StringUtil{
public:
    static void Split(std::string input,std::vector<std::string>* output,const std::string& split_char){
        boost::split(*output,input,boost::is_any_of(split_char),boost::token_compress_off);
    }
};//end StringUtil

class DictUtil{
public:
    bool Load(const std::string& path){
        std::ifstream file(path.c_str());
        if(!file.is_open()){
            return false;
        }
        std::string line;
        while(std::getline(file,line)){
            set_.insert(line);
        }
        return true;
    }

    bool Find(const std::string& key) const{
        return set_.find(key) != set_.end();

    }
private:
    std::unordered_set<std::string> set_;
};//end DictUtil

}//end common
