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
        Log(DEBUG)<< " 解析首行开始。"<<"\n";
        std::vector<std::string> output;
        StringUtil::Split(first_line," ",&output);
        *method=output[0];
        *url=output[1];
        Log(DEBUG)<< " 解析首行结束。"<<"\n";
        return 1;
    }

    int Parseurl(const std::string  url,std::string* url_argu,std::string* url_path){
        //解析url
        //以？为分割符，直接找到其对应位置，然后分别赋值给url_argu和url_path
        Log(DEBUG)<< " 解析url开始。"<<"\n";
        int pos=url.find('?');
        if(pos==0){
            return 0;
        }
        (*url_path).assign(url,0,pos-1);
        (*url_argu).assign(url,pos+1,url.size()-pos);
        Log(DEBUG)<< " 解析url结束。"<<"\n";
        return 1;
    }

    int ParseHeadler(const std::string Headler_line , httpserver::Headlers* headler){
        //以冒号为分割符
        //然后存进req->headler
        //判断冒号加二的位置，既value的起始位置没有值，也是一个错误
        Log(DEBUG)<< " 解析键值对开始。"<<"\n";
        size_t pos=Headler_line.find(':');
        if(pos==std::string::npos){
            Log(ERROR)<< " Headlers error"<<Headler_line<<"\n";
            return 0;
        }
        if(pos+2>=Headler_line.size()){
            Log(ERROR)<< " Headlers error"<<Headler_line<<"\n";
            return 0;
        }
        (*headler)[Headler_line.substr(0,pos)]
            = Headler_line.substr(pos+2);
        Log(DEBUG)<< " 解析键值对结束。"<<"\n";
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
        Log(DEBUG)<< " 读取请求开始。"<<"\n";
        Request* req=&context->request;
        context->service->PrintRequest(context);
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
            Log(INFO)<<"request Parseline error"<< first_line<<std::endl;
            return -1;
        }
        ret=httpserver::Parseurl(req->url,&req->url_argu,&req->url_path);//解析url
        if(ret<0){
            Log(INFO)<<"request Parseurl error"<<req->url<<std::endl;
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
            ret=httpserver::ParseHeadler(headler_line,&req->headler);
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
            return 0;
        }
        Log(DEBUG)<< " 读取请求结束。"<<"\n";
        return 0;
    }//end readrequest

    int http_server::writeresponse(Context* context)
    {
        //将response进行序列化
        //转换成一个string类型写回到socket
        Log(DEBUG)<< " 写入响应开始。"<<"\n";
        const Response* resp=&context->response;
        std::stringstream ss;//用于动态数组的 
        ss << "HTTP/1.1 " << resp->state << " "<<resp->message <<"\n";//首行 
        if(resp->cgi_resp==""){
            for(auto item : resp->headler){
                ss<< item.first <<": " <<item.second<<"\n";//键值对
            }
            ss<<"\n";
            ss<<resp->body;//主体部分
        }else{
            ss<<resp->cgi_resp;
        }
        const std::string& str=ss.str();//没有触发深拷贝
        //将ss写入socket中
        write(context->fd,str.c_str(),str.size()); 
        Log(DEBUG)<< " 写入响应结束。"<<"\n";
        return 1;

    }

    void http_server::GetFilePath(std::string url_path,std::string* file_path){
        //加上./wwwroot作为完整路径
        Log(DEBUG)<< " 获取路径开始。"<<"\n";
        *file_path="./wwwroot"+url_path;
        //当完整路径为一个路径，就尝试去找index.html文件
        //判断一个路径是目录还是文件
        //1.linux 的stat函数
        //2.通过boost库的filesystem模块来进行判定
        if(FileUtil::IsDir(file_path->c_str())){
            //当路径后面没有/时 需要加上
            if(file_path->back()!='/'){
                file_path->push_back('/');
            }
            *file_path=(*file_path)+"index.html";
        }
        Log(DEBUG)<< " 获取路径结束。"<<"\n";
        //查找index.html文件

    }

    int http_server::ProcessStaticFile(Context* context){
        //静态处理页面，默认路径为wwwroot文件下的index.html文件
        Log(DEBUG)<< " 静态处理开始。"<<"\n";
        const Request* req=&context->request;
        Response* resp=&context->response;
        //获取静态文件的完整路径
        std::string file_path;
        Log(DEBUG)<< " 获取静态文件路径。"<<"\n";
        GetFilePath(req->url_path,&file_path);
        //打开并读取完整文件
        Log(DEBUG)<< " 读取静态文件。"<<"\n";
        int ret=FileUtil::ReadAll(file_path,&resp->body);
        if(ret<0){
            Log(ERROR)<<"path ERROR"<<file_path<<"\n";
            return -1;
        }
        Log(DEBUG)<< " 静态处理结束。"<<"\n";
        return 1;
    }

    int http_server::ProcessCGI(Context* context){
        //先创建一对匿名管道全双工通信
        Log(DEBUG)<< " 动态处理开始。"<<"\n";
        const Request& req = context->request;
        Response* resp=&context->response;
        int fd1[2],fd2[2];
        pipe(fd1);
        pipe(fd2);
        int father_write = fd1[1];
        int father_read = fd2[0];
        int child_write = fd2[1];
        int child_read = fd1[0];
        //设置环境变量 METHOD请求方法 
        std::string env="METHOD="+req.method;
        putenv(const_cast<char*>(env.c_str()));
        if(req.method=="GET"){
            env="QUERY_STRING"+req.url_argu;
            putenv(const_cast<char*>(env.c_str()));
        }else if(req.method=="POST"){
            Headlers::const_iterator pos=req.headler.find("Content-Length");
            env="Conttent-Lengthi="+pos->second;
            putenv(const_cast<char*>(env.c_str()));
        }
        //GET 方法 QUERY_STRING 请求的参数 
        //POST 请求 CONTENT_LENGTH 长度
        //fork 父子进程流程不同
        //父进程：
        pid_t ret=fork();

        if(ret<0){
            perror("fork");
            goto END;
        }else if(ret > 0){
            Log(DEBUG)<< "进入父进程。"<<"\n";
            //父进程
            close(child_read);
            close(child_write);
            if(req.method=="POST"){
                Log(DEBUG)<< " 写入管道1。"<<"\n";
                write(father_write,resp->body.c_str(),resp->body.size());
            }
            Log(DEBUG)<< " 读取管道2。"<<"\n";
            FileUtil::ReadAll(father_read,&resp->cgi_resp);
            wait(NULL);
        }else{
            Log(DEBUG)<< " 进入子进程。"<<"\n";
            close(father_read);
            close(father_write);
            dup2(child_read,0);
            dup2(child_write,1);
            std::string file_path;
            Log(DEBUG)<< " 获取文件路径。"<<"\n";
            GetFilePath(req.url_path,&file_path);
            Log(DEBUG)<< " 进行程序替换。"<<"\n";
            execl(file_path.c_str(),file_path.c_str(),NULL);
        }
END:
        close(father_read);
        close(father_write);
        close(child_read);
        close(child_write);
        Log(DEBUG)<< " 关闭两个管道。"<<"\n";
        Log(DEBUG)<< " 动态处理结束。"<<"\n";
        return 1;
        //1.如果是POST请求，父进程就要把body写入到管道中
        // 阻塞式对去管道，尝试把子进程的结果读取出来，并放到Respponse中
        // 对子进程进行进程等待
        //2.fork，子进程流程
        // 把标准输入输出进行重定向
        //先获取到要替换的可执行文件
        //由CGI可执行程序完成动态页面的计算，并且写回数据到管道

    }//end ProcessCGI

    int http_server::Handlerrequest(Context* context)
    {
        //进行请求处理
        //分为静态和动态请求两种
        Log(DEBUG)<< " 请求处理开始。"<<"\n";
        const Request* req=&context->request;
        Response* resp=&context->response;
        resp->state=200;//状态码
        resp->message="OK";//状态信息
        Log(DEBUG)<< " 填写状态码，装填信息结束。"<<"\n";
        if(req->method=="GET"&&req->url_path==""){
            //当前方法为GET,且路径为空既默认路径
            Log(DEBUG)<< " 即将进入静态处理。"<<"\n";
            return ProcessStaticFile(context);
        }else if((req->method=="GET"&&req->url_path!="" )
                 || req->method=="POST"){
            Log(DEBUG)<< " 即将进入动态处理。"<<"\n";
            return ProcessCGI(context);//使用CGI来动态生成
        
        }else{
            Log(ERROR)<<"Unsupport Method"<< req->method <<"\n";  
        }
        Log(DEBUG)<< " 请求处理结束。"<<"\n";
        return 0;
    }
    void http_server::process404(Context* context)
    {
        Log(DEBUG)<< " 404出错，填写出错。"<<"\n";
        Response* resp=&context->response;//定义一个指针指向response对象的内存
        resp->state=404;//状态码
        resp->message="Not Found";
        resp->body="<h1>页面出错</h1>";
        std::stringstream ss;//使用stringstream来进行一个字符串转换
        ss << resp->body.size();
        std::string size;
        ss >> size;

        resp->headler["Content-Length"]=size;//给Content-Length的存的是body的长度值
        Log(DEBUG)<< " 404出错，填写出错结束。"<<"\n";

    }


    //打印request
    void http_server::PrintRequest(const Context* context){
        //使用迭代器将healders打印出来
        const Request* req=&context->request;
        std::cout<<"HTTP1.1 "<<req->method<<" "<<req->url<<std::endl;
        Headlers::const_iterator it=req->headler.begin();
        for(;it!=req->headler.end();it++){
            std::cout<<(*it).first<<": "<<(*it).second<<std::endl;
        }
        std::cout<<std::endl;
        std::cout<<req->body<<std::endl;
    }
    int threadcount=1;
    void* http_server::ThreadEntry(void* con)
    {
        Log(DEBUG)<< " 进入线程："<< threadcount<<"\n";
        threadcount++;
        Context* context =reinterpret_cast<Context*>(con);
        int ret=context->service->readrequest(context);
        if(ret<0)
        {
            context->service->process404(context);
            goto END;
        }
        Log(DEBUG)<< " 读取请求成功。"<< threadcount<<"\n";
        Log(DEBUG)<< " 打印请求开始。"<< threadcount<<"\n";
        context->service->PrintRequest(context);
        Log(DEBUG)<< " 打印请求结束。"<< threadcount<<"\n";
        context->service->Handlerrequest(context);
        Log(DEBUG)<< " 处理请求成功。"<< threadcount<<"\n";
END:
        //收尾工作
        context->service->writeresponse(context);
        Log(DEBUG)<< " 回传结果成功。"<< threadcount<<"\n";
        delete context;
        close(context->fd);
        Log(DEBUG)<< " 关闭socket成功。"<< threadcount<<"\n";
        Log(DEBUG)<< " 退出线程："<< threadcount<<"\n";
        return 0;
    }

    int http_server::start(int argc,char* argv[])
    {
        Log(DEBUG) << " 开始。" << "\n";
        Log(DEBUG) << " 服务器启动..." << "\n";
        if(argc!=3)
        {
            std::cout<<"user IP Port"<<std::endl;
            return -1;
        }
        Log(DEBUG) << " 地址端口正确。" << "\n";

        int fd=socket(AF_INET,SOCK_STREAM,0);
        if(fd<0)
        {
            Log(CAITICAL)<<"socket"<<std::endl;
            return 2;
        }
        Log(DEBUG) << " 创建socket端口成功。" << "\n";
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
        Log(DEBUG) << " 绑定端口成功。" << "\n";

        if(listen(fd,5)<0)
        {
            Log(CAITICAL)<<"listen"<<std::endl;
            return 4;
        }
        Log(DEBUG) << " 监听端口中...." << "\n";
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
            Log(DEBUG) << " 建立连接成功。" << "\n";
            pthread_t tid;
            Context* context=new Context();
            context->addr =client_addr;
            context->fd=fd;
            pthread_create(&tid,NULL,ThreadEntry,reinterpret_cast<void*>(context));
            Log(DEBUG) << " 线程创建成功。" << "\n";
            pthread_detach(tid);
            Log(DEBUG) << " 线程分离成功。" << "\n";
        }
        Log(DEBUG) << " 结束。" << "\n";
        return 0;
    }//end start
}//end namespace
