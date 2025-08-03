#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>

#ifdef _WIN32
#include <windows.h>
#endif

class Calculator {
public:
  Calculator() { initializeOperators(); }

  double calculate(const std::string &expression) { return 0.0; }

private:
  std::map<std::string, std::function<double(double, double)>> operators;

  void initializeOperators() {}
};

int main() {
// 设置控制台编码为UTF-8
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif

  std::cout << "命令行计算器" << std::endl;
  std::cout << "请输入表达式，如：4 * 3.25" << std::endl;
  std::string expression;
  std::getline(std::cin, expression);

  try {
    Calculator calc;
    double result = calc.calculate(expression);
    std::cout << "结果：" << result << std::endl;
  } catch (const std::exception &e) {
    std::cout << "错误：" << e.what() << std::endl;
  }

  return 0;
}