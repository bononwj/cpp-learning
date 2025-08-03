@echo off
REM MSYS2带代理启动脚本

REM 设置代理环境变量
set http_proxy=http://127.0.0.1:7890
set https_proxy=http://127.0.0.1:7890
set HTTP_PROXY=http://127.0.0.1:7890
set HTTPS_PROXY=http://127.0.0.1:7890

REM 启动MSYS2
D:\msys64\msys2_shell.cmd

@REM REM 清理环境变量
@REM set http_proxy=
@REM set https_proxy=
@REM set HTTP_PROXY=
@REM set HTTPS_PROXY= 