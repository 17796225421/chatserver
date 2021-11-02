


# 遇到的问题
## 一（未解决）
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