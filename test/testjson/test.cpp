#include "json.hpp"
using json = nlohmann::json;

#include <iostream>
#include <vector>
#include <map>
#include <string>
using namespace std;

//json序列化示例1------反序列化
string func1() {
    json js;
    js["msg_type"] = 2;
    js["from"] = "zhang san";
    js["to"] = "li si";
    js["msg"] = "hello, what are you doing mow?";

    string sendBuf = js.dump();
    //cout << sendBuf.c_str() << endl;
    return sendBuf;
}

//序列化2
string func2() {
    json js;
    // 添加数组
    js["id"] = {1,2,3,4,5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};
    //cout << js << endl;
    string sentBuf = js.dump();
    return sentBuf;
}

//json序列化代码示例3
string func3() {
    json js;
    // 直接序列化一个vector容器
    vector<int> vec;
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(5);
    js["list"] = vec;
    // 直接序列化一个map容器
    map<int, string> m;
    m.insert({1, "黄山"});
    m.insert({2, "华山"});
    m.insert({3, "泰山"});
    js["path"] = m;

    //cout<<js<<endl;
    string sendBuf = js.dump();
    return sendBuf;
}

int main() {
    string recvBuf = func3();//接收字符流
    json js = json::parse(recvBuf);//反序列化

    // cout << jsbuf["msg_type"] << endl;
    // cout << jsbuf["from"] << endl;
    // cout << jsbuf["to"] << endl;
    // cout << jsbuf["msg"] << endl;

    // cout << js["id"] << endl;
    // auto arr = js["id"];
    // cout << arr[2] << endl;

    // auto msg_js  = js["msg"];
    // cout << msg_js["zhang san"] << endl;
    // cout << msg_js["liu shuo"] << endl;

    // auto vec = js["list"];
    // for(int &i : vec) {
    //     cout << i << " ";
    // }
    // cout << endl;

    map<int, string> mymap = js["path"];
    for(auto &p : mymap) {
        cout << p.first << " " << p.second << endl;
    }

    return 0;
}