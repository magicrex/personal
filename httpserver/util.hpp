#include<iostream>
#include<sys/time.h>
#include<fstream>
#include<boost/algorithm/string.hpp>
#include<boost/filesystem.hpp>
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


#define Log(level) Log(level,__FILE__,__LINE__)

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
           if(read_size <= 0){
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
        return -1;
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
};//ens=d StringUtil


