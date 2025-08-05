#include <regex>
#include <functional>
#include <iostream>
#include <map>
#include <stdexcept>
#include <string>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#endif

class Calculator
{
public:
  Calculator() { initializeOperators(); }

  double calculate(const std::string &expression)
  {
    std::smatch expressionMatch;

    // 将expression拆解为数字和运算符
    std::vector<std::string> numbers;
    std::vector<std::string> exp_operators;
    std::regex pattern1("[-+]?\\d+([.]\\d+)?");
    std::regex pattern2("[-+*/]");
    // 先确定运算符
    std::sregex_iterator it(expression.begin(), expression.end(), pattern2);
    std::sregex_iterator end;
    while (it != end)
    {
      exp_operators.push_back(it->str());
      it++;
    }
    // 基于exp_operators拆解expression！！
    std::string exp_expression = expression;
    for (const auto &op : exp_operators)
    {
      // 转义正则表达式特殊字符
      std::string escaped_op = op;
      if (op == "+" || op == "*" || op == "/" || op == "-")
      {
        escaped_op = "\\" + op;
      }
      exp_expression = std::regex_replace(exp_expression, std::regex(escaped_op), " " + op + " ");
    }
    std::sregex_iterator it2(exp_expression.begin(), exp_expression.end(), pattern1);
    std::sregex_iterator end2;
    while (it2 != end2)
    {
      numbers.push_back(it2->str());
      it2++;
    }

    // 打印拆解结果
    std::cout << "数字: ";
    for (const auto &num : numbers)
    {
      std::cout << num << " ";
    }
    std::cout << std::endl;

    std::cout << "运算符: ";
    for (const auto &op : exp_operators)
    {
      std::cout << op << " ";
    }
    std::cout << std::endl;

    // 计算结果
    double result = std::stod(numbers[0]);
    for (size_t i = 0; i < exp_operators.size(); i++)
    {
      result = operators[exp_operators[i]](result, std::stod(numbers[i + 1]));
    }
    return result;
  }

private:
  std::map<std::string, std::function<double(double, double)>> operators;

  void initializeOperators()
  {
    operators["+"] = [](double a, double b)
    { return a + b; };
    operators["-"] = [](double a, double b)
    { return a - b; };
    operators["*"] = [](double a, double b)
    { return a * b; };
    operators["/"] = [](double a, double b)
    { return a / b; };
  }
};

int main()
{
// 设置控制台编码为UTF-8
#ifdef _WIN32
  SetConsoleOutputCP(CP_UTF8);
  SetConsoleCP(CP_UTF8);
#endif

  std::cout << "命令行计算器" << std::endl;
  std::cout << "请输入表达式，如：4 * 3.25" << std::endl;
  std::string expression;
  std::getline(std::cin, expression);

  try
  {
    Calculator calc;
    while (true)
    {
      double result = calc.calculate(expression);
      std::cout << "结果：" << result << std::endl;
      std::cout << "请输入表达式，如：4 * 3.25（输入 q 退出）" << std::endl;
      std::getline(std::cin, expression);
      if (expression == "q" || expression == "Q")
      {
        break;
      }
    }
  }
  catch (const std::exception &e)
  {
    std::cout << "错误：" << e.what() << std::endl;
  }

  return 0;
}