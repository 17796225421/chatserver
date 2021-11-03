/*
测试json反序列化
*/
#include <iostream>
#include "../../thirdparty/json.hpp"
using json = nlohmann::json;
using namespace std;

string func1(){
    json js;
    js["msg_type"]=2;
    js["from"]="zhang san";
    js["to"]="li si";
    js["msg"]="hello, what are you doing now?";

    string sendBuf=js.dump();
    return sendBuf;
}

string func2()
{
    json js;
    // 添加数组
    js["id"] = {1, 2, 3, 4, 5};
    // 添加key-value
    js["name"] = "zhang san";
    // 添加对象
    js["msg"]["zhang san"] = "hello world";
    js["msg"]["liu shuo"] = "hello china";
    // 上面等同于下面这句一次性添加数组对象
    js["msg"] = {{"zhang san", "hello world"}, {"liu shuo", "hello china"}};

    return js.dump();
}

string func3()
{
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

    return js.dump();
}
int main(){
    string recvBuf=func3();
    //数据的反序列化  json字符串=》反序列化 数据对象（看作容器，方便访问）
    json jsbuf=json::parse(recvBuf);

    //test func1()
    // cout<<jsbuf["msg_type"]<<endl;
    // cout<<jsbuf["from"]<<endl;
    // cout<<jsbuf["to"]<<endl;
    // cout<<jsbuf["msg"]<<endl;
    // cout<<jsbuf["id"]<<endl;

    //test func2()
    // auto arr=jsbuf["id"];
    // cout<<arr[3]<<endl;
    // auto msgjs=jsbuf["msg"];
    // cout<<msgjs["zhang san"]<<endl;
    // cout<<msgjs["liu shuo"]<<endl;

    //test func3()
    // vector<int>vec=jsbuf["list"];//js对象里的数据类型，直接放入vector容器中
    // for(int&v:vec){
    //     cout<<v<<" ";
    // }
    // cout<<endl;
    // map<int,string>mymap=jsbuf["path"];
    // for(auto&m:mymap){
    //     cout<<m.first<<' '<<m.second<<endl;
    // }
    // cout<<endl;
    return 0;
}