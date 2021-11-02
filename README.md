


# 遇到的问题
## 一
git  443 禁止访问

```
git config --global http.proxy
git config --global https.proxy
```
发现有代理，需要关闭
```
unset http_proxy
unset https_proxy
```