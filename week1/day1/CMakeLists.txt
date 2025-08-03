# Day 1: Calculator Project
add_executable(calculator calculator.cpp)

# 确保使用C++17标准
target_compile_features(calculator PRIVATE cxx_std_17)

# 设置编译器路径
set_target_properties(calculator PROPERTIES
    COMPILE_FLAGS "-std=c++17"
) 