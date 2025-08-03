#!/bin/bash

# MSYS2代理设置脚本
# 使用方法：在MSYS2终端中运行 source msys2_proxy_setup.sh

# 设置代理地址（请根据你的VPN修改）
PROXY_HOST="127.0.0.1"
PROXY_PORT="7890"  # 常见端口：7890, 1080, 8080

# HTTP代理
export http_proxy="http://${PROXY_HOST}:${PROXY_PORT}"
export https_proxy="http://${PROXY_HOST}:${PROXY_PORT}"
export HTTP_PROXY="http://${PROXY_HOST}:${PROXY_PORT}"
export HTTPS_PROXY="http://${PROXY_HOST}:${PROXY_PORT}"

# SOCKS5代理（如果使用SOCKS5）
# export http_proxy="socks5://${PROXY_HOST}:${PROXY_PORT}"
# export https_proxy="socks5://${PROXY_HOST}:${PROXY_PORT}"

# # Git代理设置
# git config --global http.proxy "http://${PROXY_HOST}:${PROXY_PORT}"
# git config --global https.proxy "http://${PROXY_HOST}:${PROXY_PORT}"

# echo "代理设置完成："
# echo "HTTP代理: $http_proxy"
# echo "HTTPS代理: $https_proxy" 