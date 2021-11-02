/* 
muduo网络库给用户提供两个主要的类
TcpServer :用于编写服务器程序
TcpClient :用于编写客户端程序

epoll+线程池
好处: 能够把网络IO代码和业务代码区分开
*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include<functional>
#include <iostream>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*基于muduo网络库开发服务器程序
1. 组合TcpServer对象
2. 创建EventLoop时间循环对象的指针
3. 明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
*/
class ChatServer
{
public:
    ChatServer(EventLoop *loop,                 // 事件循环
               const InetAddress &listenAddr,   // IP+Port
               const string &nameArg)           // 服务器的名字
        : _server(loop, listenAddr, nameArg), _loop(loop)
    {
        // 给服务器注册用户连接的创建和断开回调
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection,this,_1));
        // 给服务器注册用户读写事件回调
    }

private:
    // 专门处理用户的连接创建和断开   epoll  listenfd  accept
    void onConnection(const TcpConnectionPtr&){

    }

    TcpServer _server; // #1
    EventLoop *_loop;  // #2 epoll
};