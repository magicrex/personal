/*************************************************************************
        > File Name: httpserver_main.cpp
      > Author:fuxing
      > Mail: 374195407@qq.com 
      > Created Time: 2018年04月16日 星期一 09时36分08秒
 ************************************************************************/

#include"httpserver.h"

int main(int argc,char* argv[])
{
    std::cout<<"*********************************"<<std::endl;
    std::cout<<"*************服务器运行**********"<<std::endl;
    std::cout<<"*********************************"<<std::endl;
    std::cout<<"*********************************"<<std::endl;
	httpserver::http_server server;
	server.start(argc,argv);
	return 0;
}

