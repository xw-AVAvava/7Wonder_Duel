CXX = g++
CXXFLAGS = -std=c++17 -Wall -Wextra -Iinclude
LDFLAGS =

# 目录
SRC_DIR = src
OBJ_DIR = obj
BIN_DIR = bin

# 目标可执行文件
TARGET = $(BIN_DIR)/7wonders_duel

# 源文件
SOURCES = $(shell find $(SRC_DIR) -name '*.cpp')
OBJECTS = $(patsubst $(SRC_DIR)/%.cpp,$(OBJ_DIR)/%.o,$(SOURCES))

# 默认目标
all: directories $(TARGET)

# 创建必要的目录
directories:
	@mkdir -p $(BIN_DIR)
	@mkdir -p $(OBJ_DIR)
	@mkdir -p $(OBJ_DIR)/cards
	@mkdir -p $(OBJ_DIR)/game
	@mkdir -p $(OBJ_DIR)/player
	@mkdir -p $(OBJ_DIR)/resources
	@mkdir -p $(OBJ_DIR)/ui

# 链接目标文件
$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)
	@echo "编译完成: $(TARGET)"

# 编译源文件
$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	@mkdir -p $(dir $@)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# 清理
clean:
	rm -rf $(OBJ_DIR) $(BIN_DIR)
	@echo "清理完成"

# 运行
run: all
	./$(TARGET)

# 调试编译
debug: CXXFLAGS += -g -O0 -DDEBUG
debug: clean all

# 发布编译
release: CXXFLAGS += -O3 -DNDEBUG
release: clean all

.PHONY: all clean run debug release directories
