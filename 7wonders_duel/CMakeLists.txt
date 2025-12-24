cmake_minimum_required(VERSION 3.10)
project(7WondersDuel VERSION 1.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 设置输出目录
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

# 包含头文件目录
include_directories(include)

# 收集所有源文件
file(GLOB_RECURSE SOURCES 
    "src/*.cpp"
    "src/cards/*.cpp"
    "src/game/*.cpp"
    "src/player/*.cpp"
    "src/resources/*.cpp"
    "src/ui/*.cpp"
)

# 创建可执行文件
add_executable(7wonders_duel ${SOURCES})

# Windows特定设置
if(WIN32)
    # 设置控制台程序
    set_target_properties(7wonders_duel PROPERTIES
        WIN32_EXECUTABLE FALSE
    )
    
    # 添加Windows编译选项
    target_compile_options(7wonders_duel PRIVATE
        /W4  # 警告级别4
        /utf-8  # 使用UTF-8编码
    )
else()
    # Linux/Unix编译选项
    target_compile_options(7wonders_duel PRIVATE
        -Wall
        -Wextra
    )
endif()

# 安装规则
install(TARGETS 7wonders_duel DESTINATION bin)
