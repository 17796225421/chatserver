

# 简介

项目名称：基于muduo网络库实现的聊天服务器

平台工具：vscode远程linux开发，Ubuntu 21.04，cmake构建

项目内容：

1、使用基于reactor模型的muduo网络库作为项目的网络核心模块，提供高并发网络IO服务，解耦网络和业务模块代码。

2、使用json序列化和反序列化消息作为私有通信协议。

3、配置nginx基于tcp基于权重的负载均衡，实现聊天服务器的集群功能，提高后端服务的并发能力。

4、基于redis的发布-订阅功能，实现跨服务器的消息通信。

5、使用mysql关系型数据库作为项目数据的落地存储。

// TODO 6、使用连接池提高数据库的数据存取性能

// TODO 7、jmeter测试服务器并发量

# json测试

JSON for Modern C++
# boost测试
https://blog.csdn.net/QIANGWEIYUAN/article/details/88792874

# muduo测试
https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980

![image-20211103121856233](image/image-20211103121856233.png)

# cmake测试



```
# g++ -o server -g muduo_server.cpp xxx.cpp -l/usr/include -L/usr/lib -lmuduo_net -lmuduo_base -lpthread

cmake_minimum_required(VERSION 3.0)
project(main)

# 配置编译选项 -O2 -g
set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -g)

# 配置头文件搜索路径 -l/usr/include
# include_directories()

# 配置库文件搜索路径 -l/usr/lib
# link_directories()

# 设置需要编译的源文件列表
set(SRC_LIST muduo_server.cpp)

# 把.指定路径下的所有源文件名字放入变量SRC_LIST里面
# aux_source_directory(. SRC_LIST)

add_executable(server ${SRC_LIST})

# server需要链接库文件
target_link_libraries(server muduo_net muduo_base pthread)
```



# mysql测试

修改密码

https://blog.csdn.net/qq_26164609/article/details/106881079

user表

| 字段名   | 字段类型                  | 字段说明     | 约束                        |
| -------- | ------------------------- | ------------ | --------------------------- |
| id       | INT                       | 用户id       | PRIMARY KEY, AUTO_INCREMENT |
| name     | VARCHAR                   | 用户名       | NOT NULL, UNIQUE            |
| password | VARCHAR                   | 用户密码     | NOT NULL                    |
| state    | ENUM('online', 'offline') | 当前登录状态 | DEFAULT 'offline'           |

friend表

| 字段名   | 字段类型 | 字段说明 | 约束               |
| -------- | -------- | -------- | ------------------ |
| userid   | INT      | 用户id   | NOT NULL, 联合主键 |
| friendid | INT      | 好友id   | NOT NULL, 联合主键 |

allgroup表

| 字段名    | 字段类型     | 字段说明   | 约束                       |
| --------- | ------------ | ---------- | -------------------------- |
| id        | INT          | 组id       | PRIMARY KEY, AUT_INCREMENT |
| groupname | VARCHAR(50)  | 组名称     | NOT NULL                   |
| groupdesc | VARCHAR(200) | 组功能描述 | DEFAULT ''                 |

groupuser表

| 字段名    | 字段类型                  | 字段说明 | 约束               |
| --------- | ------------------------- | -------- | ------------------ |
| groupid   | INT                       | 组id     | NOT NULL, 联合主键 |
| userid    | INT                       | 组员id   | NOT NULL, 联合主键 |
| grouprole | ENUM('creator', 'normal') | 组内角色 | DEFAULT 'normal'   |

offlinemessage表

| 字段名  | 字段类型     | 字段说明             | 约束     |
| ------- | ------------ | -------------------- | -------- |
| userid  | INT          | 用户id               | NOT NULL |
| message | VARCHAR(500) | 离线消息(json字符串) | NOT NULL |

# nginx tcp 负载均衡测试

```
cd /usr/local/nginx/
```

nginx.conf

```
worker_processes  1;

events {
    worker_connections  1024;
}

# 自定义tcp负载均衡
stream {
    upstream MyServer{
        # 开启两台服务器分别为127.0.0.1:6000和127.0.0.1:6002
        server 127.0.0.1:6000 weight=1 max_fails=3 fail_timeout=30s;
        server 127.0.0.1:6002 weight=1 max_fails=3 fail_timeout=30s;
    }

    server{
        listen 8000; # 客户端连接8000端口
        proxy_pass MyServer;
    }
}

```

启动sbin中

```
./nginx
```

# redis 发布 订阅 测试

```
git clone https://github.com/redis/hiredis
```

# 改善文件组成

bin: 可执行文件

lib: 中间库文件

include: 头文件

src: 源文件

build: 编译过程产生的临时中间文件

example: 示例代码

thridparty: 第三方源码文件

CMakeLists.txt

autobuild.sh: 一键编译



# 需求

## 注册

## 登录

## 添加好友

## 好友聊天

## 离线消息

## 添加群

## 群聊天





# 遇到的问题

## 一（已解决）
Failed to connect to github.com port 443: 拒绝连接
### 方法一（无效）
```
git config --global http.proxy
git config --global https.proxy
```
发现有代理，需要关闭
```
unset http_proxy
unset https_proxy
```

### 方法二（有效）
发现虚拟机无法登陆github，给虚拟机开启vpn
https://steemit.com/ubutnu/@yanwu/vmware-ubuntu-shadowsocks

## 二（已解决）
GnuTLS recv error (-54): Error in the pull function.

### 方法一（有效）
可能是vscode bug，如果git的图形界面远程库选择时直接通过github仓库选择不行，要通过url选择



## 四（已解决）

git clone太慢，但是难以和vpn配合使用，vpn有时全局有时绕过大陆

直接下载zip压缩包后Xftp传输

## 五（已解决）

cmake

```
include_directories(${PROJECT_SOURCE_DIR}/thirdparty)
```

但是部分文件夹不能

```
#include "json.hpp"
```

解决方法

可能是cmake bug， 需要在src文件夹server main函数中\#include "chatservice.hpp"，可能.hpp文件需要被include，否则有不知名bug

可能是vscode加载不完全，时好时坏。

可能是缓存问题，需要手动刷新一下。

有效解决方法：重新安装cmake插件（啊这）

有效解决方法：将h文件变为hpp文件（啊这，就是cmake或vscode的bug吧）

有效解决方法：删掉build再cmake make

## 六（已解决）

Failed to connect to 127.0.0.1 port 10808: Connection refused

我知道10808是我在尝试给git clone添加vpn操作时设置的，现在应该取消掉

git config --global --unset http.proxy

## 七（已解决）

error: 推送一些引用到 'https://github.com/aqua5201314/QQ' 失败
提示：更新被拒绝，因为远程仓库包含您本地尚不存在的提交。这通常是因为另外
提示：一个仓库已向该引用进行了推送。再次推送前，您可能需要先整合远程变更
提示：（如 'git pull ...'）。

并且尝试新建空库后推送成功，较大可能是因为冲突。

解决方法

自己要提交的项目，从github拿下来要用pull不要用clone，防止冲突。

## 八（已解决）

安装nginx报错“src/os/unix/ngx_user.c:26:7: error: ‘struct crypt_data’ has no member named ‘current_salt’”

https://www.codeleading.com/article/84874357019/

## 九（已解决）

redis设计思路

https://blog.csdn.net/QIANGWEIYUAN/article/details/97895611

## 十 登录、注销、再登录发生阻塞（已解决）



# 面试

面试就是聊天，不是你问我答。字斟句酌我不会，大白话，我喜欢。

## 项目介绍

 我这个项目首先是一个网络服务器的项目，它分为四个模块，首先第一个是网络模块，网络模块我使用的是muduo库，它是一个性能非常不错的网络库，它的好处是解耦了网络代码和业务代码，能够让开发者专注于业务的开发。然后是服务层，我用了一些c++11的技术，比如map呀，绑定器呀，我主要是做了一个消息id以及这个消息发生以后的一个回调操作的一个绑定，相当于我做了一个回调机制，当我这个网络io给我出来一个消息请求的话，我这里边通过消息请求去解析出这个json，然后得到消息id，然后通过回调啊就可以处理这个操作了，主要是这么一个设计的过程。然后这个数据存储层我用了这个mysql对我这个项目上的一些关键的数据啊进行落地，比如用户的账号啊，还有离线的消息列表啊，还有群组的列表关系，都是在mysql里面进行存储的。单机服务下主要就这几个模块，单机服务下它的并发能力是有限的，所以我考虑了这个快速的去提高整个项目的并发的能力，我这项目可以支持多机的扩展，那要部署多态网络服务器的话，我就需要挂一个nginx的这个负载均衡，我这个项目因为主要是基于tcp私有协议自己去搭建的这个C-S的通信，所以nginx负载均衡需要做一个长连接，因为我是消息聊天通信，客户端不仅仅要给服务器主动发消息，服务器还要主动给客户端推消息呢，这必须就得是长连接了，短连接它做不到，短连接它没有办法给客户端直接推消息 ，然后另外呢，在负载均衡里面，因为我是各个服务器它有不同的人进行注册，那不同服务器注册的用户需要进行通信的话，我这边是引入了redis做出一个MQ消息队列的一个功能，利用它的发布订阅实现了一个跨服务器的消息通信。

## 数据安全问题

我这个项目它是一个明文传输，那肯定是要考虑做密文传输了，那密文传输就肯定需要引入一个加密解密的算法机制了，传输之前要加密，对端接收以后要进行解密，我呢，熟悉混合加密的详细过程，但是我之前做的过程中呢对加解密没有考虑的非常完全，所以没有自己去实现过加密解密，没有引入过加密解密的这个算法，所以在具体的实现中，我这个思路应该是没有问题的，但是具体怎么实现可能需要查一些资料，去具体实现一下才行。

## 按序到达问题

我们可以试着给消息加一个时间戳，比如甲给乙发消息，第一秒发在吗，第二秒发下午有空吗，第三秒发下午打球，这三条消息还真不一定就按序到达服务端，有可能在吗先发，但是它选择的网络的路由节点有很多节点路由器，有本地的，有运营商的，到我们的这个服务端，那么经过的这个网络节点可能比较拥堵，所以呢这个在网络节点存储的时间比较长，而这个下午有空吗，它可能根据我们的路由算法选择的服务节点可能比较通畅，可能更快到达这个服务端，那服务端就会对消息进行转发给乙，那转发同样也会遇到我们甲客户端往服务端发送消息所选择的不同的路由节点，不同的网络拥塞情况，还会遇到同样的问题。总之乙接收到的数据就可能是乱序的。

那我们可以给消息就一个时间戳，在到达乙的时候给消息做一个排序，然后再显示。呃那会有问题，我们网络是随时可能会有消息发送过来的，那我们进行排序的时候可以隔一段时间排序一次并显示，比如隔一秒把这一秒收到的消息排序显示，呃那还是有问题，甲第一秒发在吗，第二秒发下午有空吗，第三秒发下午打球，那如果下午打球最早就到了并一秒过去立刻显示，那在吗下午有空吗缓缓来后也必定失序了，这就需要控制间隔时间，还有一些问题，总之按时间戳排序应该不可靠。

我们可以模仿一下tcp用序列号防止乱序，给每一个消息都添加一个序列号seq，甲跟乙聊，甲发的三条消息seq=0，seq=1，seq=2，服务器收到乱序的seq没关系直接转发给乙，呃那会有问题，乙作为接收方，应该需要维护每一个好友的seq，对于甲，seq=0，那么对于甲发送过来的消息，乙想要拿到seq=0的消息，其他消息就算提前到来，乙不能先显示这个，需要把seq=1消息先缓存到客户端本地。收到seq=0的消息后显示并把维护的这个好友甲的seq+1，在缓存中找有没有seq=1的消息。

## 短连接长连接选择

我这个聊天服务器为什么要实现成一个长连接，短连接行不行？短连接，就类似于我们http协议，它是一个应用层协议，它底层也是依赖tcp来实现的，但是呢，我们客户端就是浏览器，跟服务端进行交互的时候，我们浏览器永远是发送一个请求到服务端，服务端处理这个请求给一个响应，然后服务端会主动把这个连接关闭掉，然后给其他的更多的客户提供服务。这就是典型的一个短连接、无状态的这么一个协议。它的这个服务模式只能是客户端主动请求，服务端被迫营业，服务端是没有办法主动给浏览器推送消息的。我们这是一个聊天项目啊，甲跟乙聊，甲的消息先发到服务端，服务端找到乙，然后主动推消息给这个乙，服务器是主动推消息的啊，你不建立长连接，你服务器怎么知道跟乙通信用的socket是哪个呢。难道让乙自己去隔个十毫秒隔个一百毫秒去服务器拉一下，看看有没有我的消息，如果有一万个客户，十万个客户，每个客户都去拉一下，是不是大部分都没有消息，都白拉啦。所以我们这种即时聊天消息功能的服务器来说，这个设计肯定是要和客户端保持一个长连接，我们的服务端都会保存有一个长连接模块专门保存了所有客户端的这个连接消息。连接消息中包含了跟这个连接用的socketfd呀，还可能包含其他的统计信息，比如连接时长啊，连接的通信频率啊，之类的。所以我们的这个项目肯定得用长连接啊。



