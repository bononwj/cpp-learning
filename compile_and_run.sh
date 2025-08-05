#!/bin/bash

# 快速编译和运行C++文件的脚本
# 使用方法: ./compile_and_run.sh filename.cpp

if [ $# -eq 0 ]; then
    echo "使用方法: $0 <cpp文件>"
    echo "例如: $0 calculator.cpp"
    exit 1
fi

cpp_file=$1
executable_name="${cpp_file%.*}"

echo "正在编译 $cpp_file..."

# 编译C++文件
clang++ -std=c++17 -g -Wall -Wextra -o "$executable_name" "$cpp_file"

if [ $? -eq 0 ]; then
    echo "编译成功！"
    echo "正在运行 $executable_name..."
    echo "----------------------------------------"
    ./"$executable_name"
    echo "----------------------------------------"
    echo "程序执行完成"
else
    echo "编译失败！"
    exit 1
fi 