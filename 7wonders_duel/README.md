# 7 Wonders Duel - C++ Console Edition

这是一个基于C++实现的经典桌游 **7 Wonders Duel (七大奇迹:对决)** 的控制台版本。项目旨在通过面向对象编程(OOP)的原则,完整地模拟游戏的核心机制、卡牌系统和胜利条件。

## 项目特点

- **完整的游戏逻辑**: 实现了三个时代的所有卡牌、奇迹、军事冲突、科技发展和最终计分规则。
- **面向对象设计**: 采用模块化的类结构,将游戏元素(如卡牌、玩家、游戏板)清晰地分离,易于扩展和维护。
- **AI对战**: 包含两种AI策略(随机AI和贪心AI),可以与AI进行对战或观看AI互相对战。
- **控制台界面**: 提供清晰的文本界面来展示游戏状态、玩家信息和可用行动,并通过命令行进行交互。
- **跨平台兼容**: 使用标准的C++17编写,并提供Makefile,方便在Linux和macOS等系统上编译和运行。

## 如何编译和运行

### 环境要求

- C++17 编译器 (如 g++)
- `make` 构建工具

### 编译步骤

1.  **克隆或下载项目**

2.  **进入项目目录**:
    ```bash
    cd 7wonders_duel
    ```

3.  **编译项目**:
    ```bash
    make
    ```
    这将编译所有源文件,并在 `bin` 目录下生成可执行文件 `7wonders_duel`。

### 运行游戏

编译成功后,通过以下命令启动游戏:

```bash
./bin/7wonders_duel
```

游戏开始后,根据提示输入玩家名称和类型(人类或AI),然后即可开始游戏。

## 项目结构

```
7wonders_duel/
├── bin/              # 存放可执行文件
├── include/          # 头文件
│   ├── cards/        # 卡牌相关类
│   ├── game/         # 游戏逻辑核心类
│   ├── player/       # 玩家和AI策略
│   ├── resources/    # 资源和成本
│   └── ui/           # 用户界面
├── obj/              # 编译生成的中间文件
├── src/              # 源文件实现
├── Makefile          # 编译配置文件
└── README.md         # 项目说明
```

## 实现思路

详细的实现思路和UML架构图请参考 `implementation_details.md` 文件。

## Windows 编译和运行

### 方法一: 使用CMake (推荐)

这是最简单的方法,需要安装 **CMake** 和 **Visual Studio** (Community版即可)。

1.  **安装依赖**:
    - [CMake](https://cmake.org/download/)
    - [Visual Studio](https://visualstudio.microsoft.com/vs/community/) (安装时选择 "Desktop development with C++")

2.  **编译**:
    - 双击运行 `build_windows.bat` 脚本。
    - 脚本会自动创建 `build` 目录,配置并编译项目。

3.  **运行**:
    - 编译成功后,可执行文件位于 `build\bin\Release\7wonders_duel.exe`。
    - 双击运行 `run_game.bat` 即可启动游戏。

### 方法二: 使用MinGW-w64

如果你没有安装Visual Studio,可以使用 **MinGW-w64** 编译器。

1.  **安装依赖**:
    - [MinGW-w64](https://www.mingw-w64.org/downloads/) (确保将 `bin` 目录添加到系统PATH环境变量中)

2.  **编译**:
    - 双击运行 `build_mingw.bat` 脚本。
    - 脚本会直接使用 `g++` 编译项目。

3.  **运行**:
    - 编译成功后,可执行文件位于 `bin\7wonders_duel.exe`。
    - 双击运行 `run_game.bat` 即可启动游戏。

### 注意事项

- **UTF-8编码**: 为了正确显示中文,请确保您的Windows控制台支持UTF-8编码。在较新的Windows 10/11系统中,这通常是默认设置。
- **清屏**: 代码中使用了 `system("cls")` 来清屏,如果您的环境不支持,可能会看到一些奇怪的字符。
