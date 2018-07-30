#include<iostream>
#include<sys/time.h>
#include<fstream>
#include<boost/algorithm/string.hpp>
#include<boost/regex.hpp>
#include<boost/algorithm/string/regex.hpp>
#include<boost/filesystem.hpp>
#include<time.h>
#include"httpserver.h"
class Timeuti{
	public:
		static int64_t TimeStamp(){
			struct timeval tv;
			gettimeofday(&tv,NULL);
			return tv.tv_sec;
		}
		static int64_t TimeStampUs(){
			struct timeval tv;
			gettimeofday(&tv,NULL);
			return 1000*1000*tv.tv_sec+tv.tv_usec;
		}
		
};

enum loglevel{
	DEBUG,
	INFO,
	WARNING,
	ERROR,
	CAITICAL
};


inline std::ostream& Log(loglevel level,const char* file,int line)
{
	std::string prefix;
	if(level==DEBUG)
		prefix='d';
	else if(level==INFO)
		prefix='i';
	else if(level==WARNING)
		prefix='w';
	else if(level==ERROR)
		prefix='e';
	else if(level==CAITICAL)
		prefix='c';
	else
		prefix='n';
    std::cout<<"["<<prefix<<":"<<Timeuti::TimeStamp()<<"]"<<"["<<file<<":"<<line<<"]"<<":";
	return std::cout;
}

std::ofstream& OpenFile() {
    static std::ofstream file;
    file.open("./log.txt", std::ios::app);
    if (!file.is_open()) {
        // TODO
    }
    return file;
}

inline std::ostream& LogToFile(loglevel level,const char* file,int line)
{
    static std::ofstream* f = NULL;
    if (f == NULL) {
        f = &OpenFile();
    }
	std::string prefix;
	if(level==DEBUG)
		prefix='d';
	else if(level==INFO)
		prefix='i';
	else if(level==WARNING)
		prefix='w';
	else if(level==ERROR)
		prefix='e';
	else if(level==CAITICAL)
		prefix='c';
	else
		prefix='n';
    *f<<"["<<prefix<<":"<<Timeuti::TimeStamp()<<"]"<<"["<<file<<":"<<line<<"]"<<":";
    return *f;
}


#define Log(level) Log(level,__FILE__,__LINE__)
#define LogToFile(level) LogToFile(level,__FILE__,__LINE__)

class FileUtil{
public:
    static int Readline(int fd,std::string* line){
        //以\n \r \r\n为界定标识的
        //返回时不带界定标识符
       line->clear(); 
       line->shrink_to_fit();
       while(true){
           char c='\0';
           ssize_t read_size=recv(fd,&c,1,0);
           if(read_size < 0){
               return -1;
           }
           if(c == '\r'){
               //窥探下一个字符
               recv(fd,&c,1,MSG_PEEK);
               if(c == '\n'){
                   recv(fd,&c,1,0);
               }else{
                   break;
               }
           }
           if(c == '\n'){
               break;
           }
           line->push_back(c);
       }//end while
       return 1;
    }//end Readline
    //写入一个string中，不适用于数据过大
    static int ReadN(int fd,size_t len,std::string* output){
        output->clear();
        output->shrink_to_fit();
        char c='\0';
        while(len--){
            recv(fd,&c,1,0);
            output->push_back(c);
        }
        return 1;
    }//end ReadN
    //上传文件时数据过大，写入缓存文件中
    static int ReadNFile(int fd,size_t len,std::string input){
        std::ofstream cache;
        std::string cachename("./wwwroot/cache/");
        cachename=cachename+input;
        cache.open(cachename,std::ofstream::out);
        char c='\0';
        while(len--){
            recv(fd,&c,1,0);
            cache<<c;
        }
        return 1;
    }//end ReadNFile

    static bool IsDir(const std::string& url){
        return boost::filesystem::is_directory(url);
    }

    static int ReadAll(const std::string& path,std::string* output){
        //读取文件的所有内容
        std::ifstream file(path.c_str());
        if(!file.is_open()){
            Log(ERROR)<<"open file error"<<path<<"\n";
            return -1;
        }
        //调整文件指针的位置
        file.seekg(0,file.end);
        //查询文件指针的位置
        int  length=file.tellg();
        //再次把指针设置到文件开头
        file.seekg(0,file.beg);
        output->resize(length);
        file.read(const_cast<char*>(output->c_str()),length);
        file.close();
        return 1;
    }

    static int ReadAll(int fd,std::string* output){
        while(true){
            char buf[1024*5]={0};
            ssize_t read_size=read(fd,buf,sizeof(buf)-1);
            if(read_size<0){
                Log(ERROR)<<" ReadAll read error"<<"\n";
                return -1;
            }
            if(read_size==0){
                return 1;
            }
            buf[read_size]='\0';
            *output += buf;
        }
        return 1;
    }
};//end FileUtil


class StringUtil{
public:
    static int Split(const std::string& input,const std::string& split_char,std::vector<std::string>* output){
        //参数一输入字符串，参数二用来作为分割的字符，参数三输出一个string的数组
        boost::split(*output,input,boost::is_any_of(split_char),boost::token_compress_off);
        //输出参数的引用，输入参数，分割符可以有多个每个参数都起作用，表示有连续分割符时，是否作为一个空字符。 
        return 1;
    }//end Split

    static int Split_Regex(const std::string& input,const std::string& split_string,std::vector<std::string>* output){
        boost::split_regex(*output,input,boost::regex(split_string.c_str()));
        return 1;
    }
    typedef std::unordered_map<std::string,std::string> UrlParam;
    static int ParseUrlParan(const std::string& input,UrlParam* output){
        std::vector<std::string> parmas;
        Split(input,"&",&parmas);
        for(auto i : parmas){
            std::vector<std::string> kv;
            Split(i,"=",&kv);
            if(kv.size() != 2){
                continue;
                Log(WARNING)<<" ParseUrlParan warning"<<"\n";
            }
            (*output)[kv[0]]=kv[1];
        }
        return 1;
    }
};//end StringUtil

//用来生成一个SESSID
class CookieUtil{
public:
    static std::string GetCookie(const char* username){
        //整个Cookie由用户名和时间组成
        std::string names(username);
        std::string timestring;
        time_t t=time(NULL);
        std::stringstream ss;
        ss << t;
        ss >> timestring;
        return names+timestring;
    }
};//end CookieUtil

class DirUtil{
public:
    static int CreateDir(std::string name){
        std::string prepath=("./wwwroot/AllFile/");
        prepath=prepath+name;
        int ret=mkdir(prepath.c_str(),S_IRWXU|S_IRWXG|S_IROTH|S_IXOTH);
        if(ret==0)
            return 1;
        else
            return 0;
    }
};//end DirUtil
