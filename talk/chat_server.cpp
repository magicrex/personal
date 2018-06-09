/*************************************************************************
        > File Name: chat_server.cpp
      > Author:fuxing
      > Mail: 374195407@qq.com 
      > Created Time: 2018年04月22日 星期日 17时33分47秒
 ************************************************************************/

#include"chat_server.h"
#include"util.hpp"
namespace server{

int ChatServer::RecvMsg(){
    Log(DEBUG)<<"进入RecvMsg函数"<<"\n";
    char buf[1024*5]={0};
    sockaddr_in client_addr;
    socklen_t len=sizeof(client_addr);

    ssize_t read_size=recvfrom(sock_,buf,sizeof(buf)-1,0,(sockaddr*)&client_addr,&len);
    if(read_size<0){
        perror("read");
        return -1;
    }
    buf[read_size]='\0';
    queue_.PushBack(buf);
    Log(DEBUG)<<"退出RecvMsg函数"<<"\n";
    return 1;
}

int ChatServer::BroadCast(){
    Log(DEBUG)<<"进入BroadCast函数"<<"\n";
    //读取元素
    std::string str;
    queue_.PopFront(&str);
    //反序列化
    //根据消息更新好友列表，没有则添加，下线则删除
    //遍历在线好友列表把消息发送给每个人

    Log(DEBUG)<<"退出Broadcast函数"<<"\n";
}

void* ChatServer::Product(void* arg){
    Log(DEBUG)<<"进入生产者线程"<< "\n";

    ChatServer* server=reinterpret_cast<ChatServer*>(arg);
    while(true){
        server->RecvMsg();

    }
    Log(DEBUG)<<"退出生产者线程"<< "\n";
}

void* ChatServer::Consume(void* arg){
    Log(DEBUG)<<"进入消费者线程"<< "\n";

    ChatServer* server=reinterpret_cast<ChatServer*>(arg);
    while(true){
        server->BroadCast();
    }

    Log(DEBUG)<<"退出消费者线程"<< "\n";
}

int ChatServer::Start(const std::string& ip,short port)
{
    Log(DEBUG)<< "服务器开始"<<"\n";
    sock_=socket(AF_FILE,SOCK_DGRAM,0);
    if(sock_<0){
        perror("socket");
        return -1;
    }
    Log(DEBUG)<<"创建socket成功"<<"\n";
    sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr(ip.c_str());
    server_addr.sin_port=htons(port);
    int ret=bind(sock_,(sockaddr*)&server_addr,sizeof(server_addr));
    if(ret<0){
        perror("bind");
        return -1;
    }
    Log(DEBUG)<<"绑定成功"<<"\n";
    pthread_t productor,consumer;
    pthread_create(&productor,NULL,Product,this);
    pthread_create(&consumer,NULL,Consume,this);
    pthread_join(productor,NULL);
    pthread_join(consumer,NULL);
    Log(DEBUG)<< "服务器结束"<<"\n";
    return 1;
}//end start
}//end pair
