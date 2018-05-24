/*************************************************************************
        > File Name: chat_server.h
      > Author:fuxing
      > Mail: 374195407@qq.com 
      > Created Time: 2018年04月22日 星期日 16时00分47秒
 ************************************************************************/

#pragma once
#include<unordered_map>
#include<iostream>
#include<sys/socket.h>
#include"block_queue.hpp"
typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
namespace server{

class ChatServer{
	public:
		int Start(const std::string& ip,short port);
		//接收消息
		int RecvMsg();
		//广播消息
		int BroadCast();
	private:
		void* Producer(void* arg);
		void* Consumer(void* arg);
		//key内容用户身份标识 IP+昵称
		//value ip+端口号（sockaddr_in)
		std::unordered_map<std::string,sockaddr_in> online_friend_list_;
		BlockQueue<std::string> queue_; 
		//TODO 实现一个队列作为交易场所 
		int sock_;//服务器进行绑定的文件描述符

};


}//end pair
