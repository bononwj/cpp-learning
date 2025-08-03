# 基本概念

## 1. 引用 vs 指针

指针：是一个变量，存储内存地址
引用：是变量的别名，不是独立的变量

```cpp
int x = 10;

// 指针
int* ptr = &x;  // ptr是一个变量，存储x的地址
ptr = nullptr;  // 可以改变ptr指向的地址

// 引用
int& ref = x;   // ref是x的别名，不是独立变量
// int& ref2;   // 错误！引用必须初始化
// ref = nullptr; // 错误！引用不能重新绑定
```

重要区别：
引用必须初始化，指针可以指向 nullptr
引用不能重新绑定，指针可以改变指向
引用更安全，但功能更受限

## 2. const 关键字

```cpp
int value = 10;
int other = 20;

// const int* - 指向常量的指针
const int* ptr1 = &value;  // 不能通过ptr1修改value
// *ptr1 = 30;            // 错误！
ptr1 = &other;            // 可以改变指向

// int* const - 常量指针
int* const ptr2 = &value; // ptr2本身是常量
*ptr2 = 30;               // 可以修改指向的值
// ptr2 = &other;         // 错误！不能改变指向

// const int* const - 指向常量的常量指针
const int* const ptr3 = &value;
// *ptr3 = 30;            // 错误！
// ptr3 = &other;         // 错误！
```

记忆技巧：

`[const] int* [const] ptr`

const 修饰谁，谁就不可以改变

- const int\* = 指向 const int 的指针
- int\* const = const 指针指向 int
- const int\* const = const 指针指向 const int

## 3. 函数重载

只有参数列表不同才能重载

```cpp
// 正确：参数列表不同
int add(int a, int b) { return a + b; }
int add(int a, int b, int c) { return a + b + c; }
double add(double a, double b) { return a + b; }

// 错误：只有返回值不同
int getValue() { return 10; }
double getValue() { return 10.0; }  // 编译错误！
```
