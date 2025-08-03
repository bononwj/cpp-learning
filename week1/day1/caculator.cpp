#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>


class Calculator {
public:
  Calculator() {
    // 初始化运算符映射
    initializeOperators();
  }

  double calculate(const std::string &expression) {
    // TODO: 实现表达式解析和计算
    return 0.0;
  }

private:
  // 存储运算符和对应的函数
  std::map<std::string, std::function<double(double, double)>> operators;

  void initializeOperators() {
    // TODO: 添加四则运算
  }
};

int main() {
  Calculator calc;

  std::cout << "命令行计算器" << std::endl;
  std::cout << "请输入表达式（例如：3.5 * 4）：";

  std::string expression;
  std::getline(std::cin, expression);

  try {
    double result = calc.calculate(expression);
    std::cout << "结果: " << result << std::endl;
  } catch (const std::exception &e) {
    std::cout << "错误: " << e.what() << std::endl;
  }

  return 0;
}