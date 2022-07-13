/*
muduo网络库给用户了两个主要的类
TcpServer：用于编写服务器程序
TcpClient：用于编写客户端程序

epoll+线程池
好处：能够把网络I/O的代码和业务代码区分开，这样我们就只需要关注业务代码，网络代码直接使用网络库提供的接口就可以了
                        用户的连接和断开    用户的可读写事件
*/
#include <muduo/net/TcpServer.h>
#include <muduo/net/EventLoop.h>
#include <iostream>
#include <functional>
#include <string>
using namespace std;
using namespace muduo;
using namespace muduo::net;
using namespace placeholders;

/*
基于muduo网络库开发服务器程序
1. 组合的TcpServer对象
2. 创建EventLoop事件循环对象指针
3. 明确TcpServer构造函数需要什么参数，输出ChatServer的构造函数
4. 在当前服务器类的构造函数中，注册处理来凝结的回调函数共和处理读写事件的回调函数
5. 设置合适的服务端线程数量，muduo库会自己分配I/O线程核worker线程
*/
class ChatServer
{
public:
    ChatServer(EventLoop* loop,   //事件循环
            const InetAddress &listenAddr,   //IP+Port
            const string &nameArg)   //服务器名字
        :_server(loop, listenAddr, nameArg), _loop(loop)
    {
        //给服务器注册用户连接的创建和断开回调，_1为参数占位符，关注连接
        _server.setConnectionCallback(std::bind(&ChatServer::onConnection, this, _1));

        //给服务器注册用户读写事件回调，_1,_2,_3参数占位符，关注读写
        _server.setMessageCallback(std::bind(&ChatServer::onMessage, this, _1, _2, _3));

        //设置服务器端的线程数量，根据CPU核数确定，4核就可以设置为4
        //这里就是有 1个I/O线程 3个worker线程
        _server.setThreadNum(4);
    }
    //开启事件循环
    void start()
    {
        _server.start();
    }

private:
    //专门处理用户的连接创建和断开，在连接创建或断开发生的时候调用这个函数
    void onConnection(const TcpConnectionPtr &conn) 
    {
        if(conn->connected())
        {
            cout << conn->peerAddress().toIpPort() << " -> " <<
                conn->localAddress().toIpPort() << "state:online" << endl;
        }
        else
        {
            cout << conn->peerAddress().toIpPort() << " -> " <<
                conn->localAddress().toIpPort() << "state:offline" << endl;
                conn->shutdown();   // close(fd)
                // _loop->quit();
        }
    }

    //专门处理用户的读写事件
    void onMessage(const TcpConnectionPtr &conn,   //连接
                    Buffer *buffer,   //缓冲区
                    Timestamp time)   //接收到数据的时间信息
    {
        string buf = buffer->retrieveAllAsString();
        cout << "recv data: " << buf << "time: " << time.toString() << endl;
        conn->send(buf);
    }

    TcpServer _server; //第一步
    EventLoop *_loop; //第二步
};

int main()
{
    EventLoop loop; // epoll
    InetAddress addr("127.0.0.1", 6000);
    ChatServer server(&loop, addr, "ChatServer");

    server.start();   //listenfd epoll_ctl=>epoll
    loop.loop();   // epoll_wait以阻塞方式等待新用户连接吗，已连接用户的读写事件等

    return 0;
}