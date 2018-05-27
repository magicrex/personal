/*************************************************************************
        > File Name: httpserver.cpp
      > Author:fuxing
      > Mail: 374195407@qq.com 
      > Created Time: 2018年04月15日 星期日 15时01分57秒
 ************************************************************************/

#include"httpserver.h"
#include"util.hpp"

namespace httpserver{
    void PrintRequest(const Context* context);
    int Parseline(std::string first_line,std::string* method,std::string* url){
        //解析第一行函数
        //通过调用函数进行切割
        std::vector<std::string> output;
        StringUtil::Split(first_line," ",&output);
        method=output[0];
        url=output[1];
        return 1;
    }

    int Parseurl(const std::string  url,std::string* url_argu,std::string* url_path){
        //解析url
        //以？为分割符，直接找到其对应位置，然后分别赋值给url_argu和url_path
        return 1;
    }

    int ParseHeadler(const std::string Headler_line , httpserver::Headlers*  headler){
        //以冒号为分割符
        //然后存进req->headler
        //判断冒号加二的位置，既value的起始位置没有值，也是一个错误
        return 1;
        
    }
    int http_server::readrequest(Context* context)
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
        Request* req=&context->request;
        std::string first_line;
        int ret =0;
        ret=FileUtil::Readline(context->fd,&first_line);//读取第一行
        if(ret<0){
            Log(ERROR)<<"requset Readline error"<<std::endl;
            return -1;
        }
        ret = httpserver::Parseline(first_line,&req->method,&req->url);//解析第一行
        if(ret<0)
        {
            Log(INFO)<<"request Parseline error"<<std::endl;
            return -1;
        }
        ret=Parseurl(&req->url,&req->url_argu,&req->url_path);//解析url
        if(ret<0){
            Log(INFO)<<"request Parseurl error"<<std::endl;
            return -1;
        }
        std::string headler_line;
        while(1){
            //循环读取headler
            ret=FileUtil::Readline(context->fd,&headler_line);
            //如果为空行就退出，不为空进行解析
            if(headler_line.empty()){
                break;
            }  
            ret=ParseHeadler(&headler_line,&req->headler);
            if(ret<0){

            }
        }
        if(req->method=="GET")
        {
            return 1;
        }
        else if(req->method=="POST")
        {
            Headlers::iterator it;
            it =req->headler.find("Content-Length");//取到长度传给ReadN函数
            if(true){
                //有Content-Length
                int n=0;
                ret=FileUtil::ReadN(context->fd,n,&req->body);//从输入中读取一个指定长度的字符串
            }else{
                //没有Content-Length
            }   
        }
        else
        {
            return -1;
        }
    }//end readrequest

    int http_server::writeresponse(Context* context)
    {
        return 1;

    }

    int http_server::Handlerrequest(Context* context)
    {
        return 1;

    }
    void http_server::process404(Context* context)
    {
        Response* resp=&context->response;//定义一个指针指向response对象的内存
        resp->state=404;//状态码
        resp->message="Not Found";
        resp->body="<h1>页面出错</h1>";
        std::stringstream ss;//使用stringstream来进行一个字符串转换
        ss << resp->body.size();
        std::string size;
        ss >> size;

        resp->headler["Content-Length"]=size;//给Content-Length的存的是body的长度值

    }


    void http_server::ThreadEntry(void* con)
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
        //收尾工作
        writeresponse(context);
        delete context;
        close(context->fd);
        return ;
    }

    int http_server::start(int argc,char* argv[])
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
        //给socket加一个参数使得文件描述符重用，不至于出现大量的timw_wait
        int opt=1;
        setsockopt(fd,SOL_SOCKET,SO_REUSEADDR,&opt,sizeof(opt));
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
            pthread_create(&tid,NULL,ThreadEntry,reinterpret_cast<void*>(context));
            pthread_detach(&tid);
        }
        return 0;
    }//end start

    //打印request
    void PrintRequest(const Context* context)
    {
        std::cout<<context->request.method<<" "<<context->request.url_path<<"?"<<context->request.url_argu<<" HTTP/1.1"<<std::endl;
        //使用迭代器将healders打印出来
        auto it=context->request.headler.begin();
        for(;it!=context->request.headler.end();it++){
            std::cout<<<<std::endl;
        }

    }
}//end namespace
