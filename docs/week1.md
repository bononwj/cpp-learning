### 第一周：C++ 核心语法与面向对象（加速版）

以下是针对有编程基础学习者的浓缩课程，重点突出 C++ 特有概念和关键实践：

#### **Day 1：环境搭建与核心语法**

**核心重点**：

1. 安装 Clang/MSVC + CMake
2. C++ 编译模型（预处理 → 编译 → 链接）
3. C++ 特有特性：引用、const、函数重载

**实战任务（命令行计算器升级版）**：

```cpp
#include <iostream>
#include <map>
#include <functional>

// 使用函数对象和map实现计算器
class Calculator {
public:
    Calculator() {
        // 注册运算操作（lambda表达式）
        ops["+"] = [](double a, double b) { return a + b; };
        ops["-"] = [](double a, double b) { return a - b; };
        ops["*"] = [](double a, double b) { return a * b; };
        ops["/"] = [](double a, double b) {
            if(b == 0) throw std::runtime_error("Division by zero!");
            return a / b;
        };
    }

    double calculate(const std::string& expr) {
        // 解析表达式逻辑
        // ...
        return ops[op](num1, num2);
    }

private:
    std::map<std::string, std::function<double(double, double)>> ops;
};

int main() {
    Calculator calc;
    std::cout << "3.5 * 4 = " << calc.calculate("3.5 * 4") << std::endl;
}
```

#### **Day 2：内存管理与现代指针**

**核心重点**：

1. RAII 范式（资源获取即初始化）
2. 智能指针深度使用：
   - `unique_ptr`（独占所有权）
   - `shared_ptr`（共享所有权）
   - `weak_ptr`（打破循环引用）

**实战任务（智能指针实践）**：

```cpp
#include <memory>
#include <vector>

class Resource {
public:
    Resource() { std::cout << "Resource acquired\n"; }
    ~Resource() { std::cout << "Resource released\n"; }
};

void process() {
    // 使用独占指针
    auto res1 = std::make_unique<Resource>();

    // 共享资源
    auto sharedRes = std::make_shared<Resource>();
    std::vector<std::shared_ptr<Resource>> pool;
    pool.push_back(sharedRes);

    // 观察但不拥有
    std::weak_ptr<Resource> observer = sharedRes;
    if(auto locked = observer.lock()) {
        std::cout << "Resource still exists\n";
    }
} // 自动释放所有资源
```

#### **Day 3：面向对象高级特性**

**核心重点**：

1. 多态与虚函数表原理
2. 移动语义（std::move）
3. 纯虚函数与接口设计

**实战任务（图形系统升级）**：

```cpp
class Shape {
public:
    virtual double area() const = 0; // 纯虚函数
    virtual std::unique_ptr<Shape> clone() const = 0; // 克隆模式
    virtual ~Shape() = default;
};

class Circle : public Shape {
public:
    explicit Circle(double r) : radius(r) {}

    double area() const override {
        return 3.14159 * radius * radius;
    }

    std::unique_ptr<Shape> clone() const override {
        return std::make_unique<Circle>(*this);
    }

private:
    double radius;
};

// 使用示例
auto original = std::make_unique<Circle>(5.0);
auto copy = original->clone();
```

#### **Day 4：STL 深度探索**

**核心重点**：

1. 容器内部实现机制
2. 迭代器失效问题
3. 高效算法使用

**实战任务（学生系统优化）**：

```cpp
#include <algorithm>
#include <vector>

struct Student {
    std::string id;
    std::string name;
    int score;

    // 移动构造函数
    Student(Student&& other) noexcept
        : id(std::move(other.id)),
          name(std::move(other.name)),
          score(other.score) {}
};

class StudentManager {
public:
    void addStudent(Student s) {
        students.push_back(std::move(s));
    }

    void sortByScore() {
        std::sort(students.begin(), students.end(),
            [](const auto& a, const auto& b) {
                return a.score > b.score;
            });
    }

private:
    std::vector<Student> students;
};
```

#### **Day 5：模板元编程基础**

**核心重点**：

1. 类型萃取（type traits）
2. SFINAE 原则
3. 变参模板

**实战任务（通用容器）**：

```cpp
template <typename T>
class GenericArray {
public:
    explicit GenericArray(size_t size) : size(size), data(new T[size]) {}

    ~GenericArray() { delete[] data; }

    // 移动构造函数
    GenericArray(GenericArray&& other) noexcept
        : size(other.size), data(other.data) {
        other.data = nullptr;
        other.size = 0;
    }

    T& operator[](size_t index) {
        return data[index];
    }

private:
    size_t size;
    T* data;
};

// 特例化版本
template <>
class GenericArray<bool> {
    // 位压缩实现
};
```

#### **Day 6：异常与文件系统**

**核心重点**：

1. 异常安全保证（基本、强、无异常）
2. `<filesystem>` 库使用
3. 自定义异常类型

**实战任务（高级日志系统）**：

```cpp
#include <fstream>
#include <filesystem>
#include <stdexcept>

namespace fs = std::filesystem;

class FileLogger {
public:
    explicit FileLogger(const fs::path& path) {
        if(!fs::exists(path.parent_path())) {
            fs::create_directories(path.parent_path());
        }

        file.open(path, std::ios::app);
        if(!file) throw std::runtime_error("Cannot open log file");
    }

    void log(const std::string& message) {
        file << message << '\n';
        if(!file) throw std::runtime_error("Write failed");
    }

private:
    std::ofstream file;
};
```

#### **Day 7：测试驱动开发**

**核心重点**：

1. Google Test 高级特性
2. 测试桩（Mocking）
3. 代码覆盖率分析

**实战任务（测试学生系统）**：

```cpp
#include <gtest/gtest.h>

TEST(StudentManagerTest, AddStudent) {
    StudentManager mgr;
    mgr.addStudent({"001", "Alice", 95});
    ASSERT_EQ(1, mgr.getCount());
}

TEST(StudentManagerTest, Sorting) {
    StudentManager mgr;
    mgr.addStudent({"001", "Alice", 85});
    mgr.addStudent({"002", "Bob", 95});
    mgr.sortByScore();
    ASSERT_EQ("Bob", mgr.getTopStudent().name);
}

// 编译命令：g++ -std=c++17 -lgtest -lgtest_main
```

### 第一周学习重点提示：

1. **理解对象生命周期**：C++ 手动内存管理特性
2. **掌握移动语义**：现代 C++ 性能关键
3. **深入模板机制**：C++ 泛型编程核心
4. **实践 RAII 模式**：资源管理核心范式
5. **测试驱动开发**：工业级代码质量保障

> **加速学习建议**：
>
> 1. 重点研究 C++ 特有机制（RAII、移动语义、模板）
> 2. 使用编译器资源查看器（如 Compiler Explorer）
> 3. 阅读标准库源码（如 LLVM libc++）
> 4. 每日代码量 ≥ 500 行，侧重质量而非数量

完成第一周后，你应能：

- 编写异常安全的 C++ 代码
- 合理使用智能指针管理资源
- 设计基于模板的泛型组件
- 实现多态类层次结构
- 构建基础测试套件

明天开始第二周内容时，我们将重点探讨现代 C++ 特性（C++17/20）和并发编程基础。请准备好今天的实战代码，我们可以随时讨论实现细节！
