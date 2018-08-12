#include<iostream>
#include<sofa/pbrpc/pbrpc.h>
#include"echo_service.pb.h"


int main()
{
    SOFA_PBRPC_SET_LOG_LEVEL(NOTICE);
    sofa::pbrpc::RpcClientOptions client_options;
    client_options.work_thread_num = 8;
    sofa::pbrpc::RpcClient rpc_client(client_options);
    sofa::pbrpc::RpcChannel rpc_channel(&rpc_client, "127.0.0.1:12321");

    sofa::pbrpc::test::EchoServer_Stub stub(&rpc_channel);

    sofa::pbrpc::test::EchoRequest request;
    request.set_message("Hello world!");
    sofa::pbrpc::test::EchoResponse response;
    sofa::pbrpc::RpcController controller;
    controller.SetTimeout(3000);
    stub.Echo(&controller, &request, &response, NULL);
    if (controller.Failed()) {
        SLOG(ERROR, "request failed: %s", controller.ErrorText().c_str());

    }

    return EXIT_SUCCESS;

}

