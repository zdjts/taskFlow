# 目标文件名
TARGET = text.exe

# 源文件
SRC = text.cpp

# 头文件
HEADERS = ThreadPool.hpp

# 编译器和编译选项
CXX = g++
CXXFLAGS = -std=c++11 -Wall

# 默认目标
all: $(TARGET)

# 生成目标文件
$(TARGET): $(SRC)
	$(CXX) $(CXXFLAGS) $(SRC) -o $(TARGET)

# 运行程序
run: $(TARGET)
	./$(TARGET)

# 清理目标文件
clean:
	rm -f $(TARGET)
