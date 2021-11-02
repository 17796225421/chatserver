
# json测试
JSON for Modern C++
# boost测试
https://blog.csdn.net/QIANGWEIYUAN/article/details/88792874

# muduo测试
https://blog.csdn.net/QIANGWEIYUAN/article/details/89023980
# 遇到的问题
## 一（已解决）
Failed to connect to github.com port 443: 拒绝连接

```
git config --global http.proxy
git config --global https.proxy
```
发现有代理，需要关闭
```
unset http_proxy
unset https_proxy
```
发现虚拟机无法登陆github，给虚拟机开启vpn
https://steemit.com/ubutnu/@yanwu/vmware-ubuntu-shadowsocks

## 二（未解决）
GnuTLS recv error (-54): Error in the pull function.
