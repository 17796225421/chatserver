#ifndef CHATSERVICE_H
#define CHATSERVICE_H

#include <muduo/net/TcpConnection.h>
#include <unordered_map>
#include <functional>
using namespace std;
using namespace muduo;
using namespace muduo::net;

#include "json.hpp"
using json=nlohmann::json;

//  表示处理信息的事件回调方法类型
using MsgHandler=std::function<void(const TcpConnectionPtr&conn,json &js,Timestamp)>;

// 聊天服务器业务类
class ChatService
{
public:
private:
};

#endif