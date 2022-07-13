#ifndef CHATSERVER_H
#define CHATSERVER_H


#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
using namespace muduo;
using namespace muduo::net;

/*
基于muduo网络库开发服务器程序
1. 组合的TcpServer对象
2. 创建EventLoop事件循环对象指针
3. 明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
4. 在当前服务器类的构造函数中，注册处理来凝结的回调函数共和处理读写事件的回调函数
5. 设置合适的服务端线程数量，muduo库会自己分配I/O线程核worker线程
*/
//聊天服务器主类
class ChatServer
{
public:
    //初始化聊天服务器对象
    ChatServer(EventLoop *loop,
            const InetAddress &listenAddr,
            const string &nameArg);

    //启动服务
    void start();
private:
    //上报链接相关信息的回调函数
    void onConnection(const TcpConnectionPtr &);

    //上报读写事件相关信息的回调函数
    void onMessage(const TcpConnectionPtr &, Buffer *, Timestamp);

    TcpServer _server;   //组合的muduo库，实现服务器功能的类对象
    EventLoop *_loop;   //指向事件循环对象的指针
};

#endif