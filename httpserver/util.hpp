#pragma once

#include<iostream>
#include<sys/time.h>

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

