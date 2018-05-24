/*************************************************************************
        > File Name: httpserver.cpp
      > Author:fuxing
      > Mail: 374195407@qq.com 
      > Created Time: 2018年04月15日 星期日 15时01分57秒
 ************************************************************************/

#include"httpserver.h"
#include"util.hpp"
namespace httpserver{

int Parseline(Context* context)
{
	Request* req=&context->request;
	std::string 
	while(1)
	{

	}
}

int readrequest(Context* context)
{
	//读取数据采用recv可以设置为每次读一个，socket中的数据读取之后就会删除
	//从文件描述符中读取一行数据作为首行,从中获取到方法
	//以\r或者\r\n结尾，\n结尾。
	//解析首行并存入对应的类成员
	//？作为分隔符
	//接下来循环按行读取
	//存入哈希表中，空行结束
	//判断如果方法为post而且map中存在content-length就继续读取body
	//否则就不读了
	int ret =0;
	ret = Parseline(context);
	if(ret<0)
	{
		Log(INFO)<<"request"<<std::endl;
		return -1;
	}
	ret = ParseHeadler(context);
	if(ret<0)
	{
		Log(INFO)<<"request"<<std::endl;
		return -1;
	}
	if((*context).request.method=="GET")
	{
		return 1;
	}
	else if((*context).request.method=="POST")
	{
		ret=ReadBody(context);
		if(ret<0)
		{
			Log(INFO)<<"request"<<std::endl;
			return -1;
		}
		else
		{
			return 1;
		}
	}
	else
	{
		return -1;
	}
}//end readrequest

int writeresponse(Context* context)
{

}

int Handlerrequest(Context* context)
{

}
int process404(Context* context)
{

}

void PrintRequest(Context* context)
{
	Request* r=context->request;
	std::cout<<r->method<<" "<<r->url_path<<"?"<<r->url_argu<<" HTTP/1.1"<<std::endl;

	
}

void ThreaEntry(void* con)
{
	Context* context =reinterpret_cast<Context*>(&con);
	int ret=readrequest(context);
	if(ret<0)
	{
		process404(context);
		goto END;
	}
	PrintRequest(context);
	Handlerrequest(context);
END:
	writeresponse(context);
	delete context;
	close(context->fd);
	return ;
}

int start(int argc,char* argv[])
{
	if(argc!=3)
	{
		std::cout<<"user IP Port"<<std::endl;
		return -1;
	}

	int fd=socket(AF_INET,SOCK_STREAM,0);
	if(fd<0)
	{
		Log(CAITICAL)<<"socket"<<std::endl;
		return 2;
	}
	sockaddr_in server_sock;
	server_sock.sin_family=AF_INET;
	server_sock.sin_port=htons(atoi(argv[2]));
	server_sock.sin_addr.s_addr=inet_addr(argv[1]);

	int ret=bind(fd,(sockaddr*)&server_sock,sizeof(server_sock));
	if(ret<0)
	{
		Log(CAITICAL)<<"bind"<<std::endl;
		return 3;
	}

	if(listen(fd,5)<0)
	{
		Log(CAITICAL)<<"listen"<<std::endl;
		return 4;
	}
	while(1)
	{
		sockaddr_in client_addr;
		socklen_t len=sizeof(client_addr);
		ret =accept(fd,(sockaddr*)&client_addr,&len);
		if(ret<0)
		{
			Log(INFO)<<"accept"<<std::endl;
			continue;
		}
		pthread_t tid;
		Context* context=new Context();
		context->addr =client_addr;
		context->fd=fd;
		pthread_create(&tid,NULL,ThreaEntry,reinterpret_cast<void*>(context));
		pthread_detach(&tid);
	}
	close(fd);
	return 0;
}//end start

}//end pair
