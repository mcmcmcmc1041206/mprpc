#include <iostream>
#include "mprpcapplication.h"
#include "friend.pb.h"
#include "mprpcchannel.h"

int main(int argc,char **argv)
{
    //整个程序启动之后，想使用mprpc框架来享受rpc服务调用，一定需要先调用框架初始化函数
    MprpcApplication::Init(argc,argv);

    fixbug::UserServiceRpc_Stub stub(new MprpcChannel());
    //rpc方法的请求参数
    fixbug::GetFriendListRequest request;
    request.set_userid(1000);
    //rpc方法的响应
    fixbug::GetFriendListResponse response;
    //发起rpc方法的调用 同步rpc调用过程
    MprpcController controller;
    stub.GetFriendList(&controller,&request,&response,nullptr);//RpcChannel->RpcChannel::callMethod 集中做所有rpc方法调用的参数序列化和网络发送
    
    //一次rpc调用完成，读调用的结果
    if(controller.Failed())
    {
        std::cout<<controller.ErrorText()<<std::endl;
    }
    else
    {
            if(0 == response.result().errcode())
        {
            std::cout<<"rpc GetFriendList response suceess"<<std::endl;
            int size = response.friends_size();
            std::cout<<"friend_size:"<<size<<std::endl;
            for(int i = 0;i<size;i++)
            {
                std::cout<<"index:"<<(i+1)<<"name:"<<response.friends(i)<<std::endl;
            }
        }
        else{
            std::cout<<"rpc login response error:"<<response.result().errmsg()<<std::endl;
        }
    }
    
    return 0;
}