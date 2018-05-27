/*************************************************************************
     > File Name: httpserver.h
      > Author:fuxing
      > Mail: 374195407@qq.com 
      > Created Time: Sun 15 Apr 2018 02:10:48 PM CST
 ************************************************************************/

#include<iostream>
#include<sstream>
#include<vector>
#include<sys/socket.h>
#include<unordered_map>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<unistd.h>
#include<stdlib.h>
#include<string.h>
//命名空间
namespace httpserver{
//用来存放请求的结构体
typedef struct sockaddr sockaddr;
typedef struct sockaddr_in sockaddr_in;
typedef std::unordered_map<std::string,std::string> Headlers;
typedef struct Request{
	std::string method;
	std::string url;
	std::string url_path;
	std::string url_argu;
	//std::string version;
	Headlers headler;
	std::string body;
}Request;
//用来存放响应的结构体
typedef struct Response{
	//std::string version;
	int state;
	std::string message;
	Headlers headler;
	std::string body;
}Response;
//用来存放上下文，随时可以拓展的结构体
typedef struct Context{
	Request request;
	Response  response;
	int fd;
	sockaddr_in addr;


}Context;


class http_server{

public:
	//start server
	int start(int argc,char* argv[]);
    void PrintRequest(Context* context);
private:
	//read request
    int Parseline(std::string first_line,std::string* method,std::string* url);
    int Parseurl(std::string*  url,std::string* url_argu,std::string* url_path);
    int ParseHeadler(std::string* eadler_line,std::string* headler);
	int readrequest(Context* context);
	//write response
	int writeresponse(Context* context);
	//deal request
	int Handlerrequest(Context* context);
	
	void ThreadEntry(void* con);
    void process404(Context* context);
};


}//end pair
