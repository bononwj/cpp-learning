# 编译器设置
CXX = D:/msys64/mingw64/bin/clang++.exe
CXXFLAGS = -std=c++17 -Wall -Wextra

# 目标文件
TARGET = calculator
SOURCE = calculator.cpp

# 默认目标
all: $(TARGET)

# 构建可执行文件
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 清理
clean:
	del $(TARGET).exe

# 帮助
help:
	@echo "可用目标:"
	@echo "  all   - 构建程序"
	@echo "  run   - 构建并运行程序"
	@echo "  clean - 清理生成的文件"
	@echo "  help  - 显示此帮助信息" 