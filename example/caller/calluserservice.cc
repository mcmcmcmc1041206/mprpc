#include <iostream>
#include "mprpcapplication.h"
#include "user.pb.h"
#include "mprpcchannel.h"

int main(int argc,char **argv)
{
    //整个程序启动之后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架初始化函数
    MprpcApplication::Init(argc,argv);

    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    //rpc方法的请求参数
    fixbug::LoginRequest request;
    request.set_name("zhang san");
    request.set_pwd("123456");
    //rpc方法的响应
    fixbug::LoginResponse response;
    //发起rpc方法的调用 同步rpc调用过程
    stub.Login(nullptr,&request,&response,nullptr);//RpcChannel->RpcChannel::callMethod 集中做所有rpc方法调用的参数序列化和网络发送
    
    //一次rpc调用完成，读调用的结果
    if(0 == response.result().errcode())
    {
        std::cout<<"rpc login response suceess:"<<response.success()<<std::endl;
    }
    else{
        std::cout<<"rpc login response error:"<<response.result().errmsg()<<std::endl;
    }


    fixbug::registerRequest req;
    req.set_id(2000);
    req.set_name("mprpc");
    req.set_pwd("666666");
    fixbug::registerResponse rsp;

    stub.Register(nullptr,&req,&rsp,nullptr);
    if(0 == rsp.result().errcode())
    {
        std::cout<<"rpc register response suceess:"<<rsp.success()<<std::endl;
    }
    else{
        std::cout<<"rpc register response error:"<<rsp.result().errmsg()<<std::endl;
    }
    return 0;

}