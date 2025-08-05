# Makefile for C++ projects
CXX = clang++
CXXFLAGS = -std=c++17 -g -Wall -Wextra
TARGET = calculator
SOURCE = week1/day1/calculator.cpp

# 默认目标
all: $(TARGET)

# 编译目标
$(TARGET): $(SOURCE)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCE)

# 运行目标
run: $(TARGET)
	./$(TARGET)

# 编译并运行
build-and-run: $(TARGET)
	./$(TARGET)

# 清理编译文件
clean:
	rm -f $(TARGET)
	rm -f *.o
	rm -rf build/

# 编译当前目录下的所有.cpp文件
%.cpp:
	$(CXX) $(CXXFLAGS) -o $* $@

# 帮助信息
help:
	@echo "可用的目标:"
	@echo "  all          - 编译项目"
	@echo "  run          - 运行程序"
	@echo "  build-and-run - 编译并运行"
	@echo "  clean        - 清理编译文件"
	@echo "  help         - 显示此帮助信息"

.PHONY: all run build-and-run clean help 