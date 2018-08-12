#include <sofa/pbrpc/pbrpc.h>  // sofa-pbrpc头文件
#include "echo_service.pb.h"


class EchoServerImpl : public sofa::pbrpc::test::EchoServer
{
public:
    EchoServerImpl(){}
    virtual ~EchoServerImpl() {}

private:
    virtual void Echo(google::protobuf::RpcController* controller,
                      const sofa::pbrpc::test::EchoRequest* request,
                      sofa::pbrpc::test::EchoResponse* response,
                      google::protobuf::Closure* done)
    {
        sofa::pbrpc::RpcController* cntl =
            static_cast<sofa::pbrpc::RpcController*>(controller);
        SLOG(NOTICE, "Echo(): request message from %s: %s",
             cntl->RemoteAddress().c_str(), request->message().c_str());
        response->set_message("echo message: " + request->message());
        done->Run();

    }

};

int main()
{
    SOFA_PBRPC_SET_LOG_LEVEL(NOTICE);

    sofa::pbrpc::RpcServerOptions options;
    options.work_thread_num = 8;
    sofa::pbrpc::RpcServer rpc_server(options);

    if (!rpc_server.Start("0.0.0.0:12321")) {
        SLOG(ERROR, "start server failed");
        return EXIT_FAILURE;

    }

    sofa::pbrpc::test::EchoServer* echo_service = new EchoServerImpl();
    if (!rpc_server.RegisterService(echo_service)) {
        SLOG(ERROR, "register service failed");
        return EXIT_FAILURE;

    }
    rpc_server.Run();
    rpc_server.Stop();

    return EXIT_SUCCESS;

}

