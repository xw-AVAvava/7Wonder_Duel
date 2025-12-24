# Windows 系统安装和运行指南

本文档详细说明如何在 **Windows** 系统上编译和运行 **7 Wonders Duel** 游戏。

## 系统要求

- **操作系统**: Windows 10 或更高版本
- **编译器**: Visual Studio 2019+ 或 MinGW-w64
- **CMake**: 3.10 或更高版本 (使用CMake编译时需要)

## 快速开始

### 最简单的方法 (推荐给初学者)

如果您已经安装了 **Visual Studio** 和 **CMake**:

1. 解压项目文件到任意目录,例如 `C:\7wonders_duel`
2. 双击运行 `build_windows.bat` 脚本
3. 等待编译完成(约1-2分钟)
4. 双击运行 `run_game.bat` 启动游戏

就这么简单!

## 详细安装步骤

### 方法一: 使用 Visual Studio + CMake

这是最推荐的方法,因为Visual Studio是Windows上最成熟的C++开发环境。

#### 步骤1: 安装Visual Studio

访问 [Visual Studio官网](https://visualstudio.microsoft.com/vs/community/) 下载 **Visual Studio Community** (免费版)。

安装时,请确保选择以下组件:

- **Desktop development with C++** (使用C++的桌面开发)
- 在右侧的"安装详细信息"中,确保勾选:
  - MSVC v142 或更高版本的C++编译器
  - Windows 10 SDK

安装大小约为 **5-10 GB**,请确保有足够的磁盘空间。

#### 步骤2: 安装CMake

访问 [CMake官网](https://cmake.org/download/) 下载最新版本的CMake安装程序。

安装时,选择 **"Add CMake to the system PATH for all users"** 选项,这样可以在命令行中直接使用CMake。

#### 步骤3: 编译项目

打开项目目录,双击运行 `build_windows.bat` 脚本。

脚本会自动执行以下操作:

1. 创建 `build` 目录
2. 使用CMake配置项目
3. 调用Visual Studio编译器编译项目
4. 生成可执行文件到 `build\bin\Release\7wonders_duel.exe`

如果一切顺利,您会看到 **"编译成功!"** 的提示。

#### 步骤4: 运行游戏

双击运行 `run_game.bat` 脚本,游戏将自动启动。

### 方法二: 使用 MinGW-w64

如果您不想安装庞大的Visual Studio,可以使用轻量级的 **MinGW-w64** 编译器。

#### 步骤1: 安装MinGW-w64

访问 [MinGW-w64下载页面](https://www.mingw-w64.org/downloads/) 或使用以下推荐的安装方式:

**推荐: 使用MSYS2安装MinGW-w64**

1. 下载并安装 [MSYS2](https://www.msys2.org/)
2. 打开MSYS2终端,运行以下命令:
   ```bash
   pacman -S mingw-w64-x86_64-gcc
   ```
3. 将MinGW的 `bin` 目录添加到系统PATH环境变量中:
   - 默认路径: `C:\msys64\mingw64\bin`
   - 右键点击"此电脑" → "属性" → "高级系统设置" → "环境变量"
   - 在"系统变量"中找到"Path",点击"编辑",添加上述路径

#### 步骤2: 验证安装

打开命令提示符(cmd),输入以下命令验证g++是否安装成功:

```cmd
g++ --version
```

如果显示版本信息,说明安装成功。

#### 步骤3: 编译项目

双击运行 `build_mingw.bat` 脚本。

脚本会直接使用 `g++` 编译所有源文件,并生成可执行文件到 `bin\7wonders_duel.exe`。

#### 步骤4: 运行游戏

双击运行 `run_game.bat` 脚本,游戏将自动启动。

## 常见问题

### 问题1: 中文显示乱码

**原因**: Windows控制台默认使用GBK编码,而项目源代码使用UTF-8编码。

**解决方案**:

在运行游戏前,先在命令提示符中执行以下命令:

```cmd
chcp 65001
```

这会将控制台编码切换为UTF-8。您也可以在 `run_game.bat` 脚本的开头添加这一行。

### 问题2: 编译时出现"找不到g++"错误

**原因**: MinGW的 `bin` 目录没有添加到系统PATH环境变量中。

**解决方案**:

按照上述"方法二 步骤1"中的说明,将MinGW的 `bin` 目录添加到PATH环境变量中,然后重新打开命令提示符窗口。

### 问题3: CMake配置失败

**原因**: 可能是CMake版本过低,或者没有找到C++编译器。

**解决方案**:

1. 确保CMake版本至少为3.10:
   ```cmd
   cmake --version
   ```
2. 确保已安装Visual Studio或MinGW-w64
3. 尝试手动运行CMake:
   ```cmd
   cd build
   cmake ..
   ```
   查看详细的错误信息

### 问题4: 运行时出现"缺少DLL文件"错误

**原因**: 使用MinGW编译时,可能需要一些运行时库文件。

**解决方案**:

将MinGW的 `bin` 目录下的以下文件复制到游戏的 `bin` 目录:

- `libgcc_s_seh-1.dll`
- `libstdc++-6.dll`
- `libwinpthread-1.dll`

或者,在编译时添加 `-static` 链接选项,将这些库静态链接到可执行文件中。

## 手动编译 (高级用户)

如果您熟悉命令行操作,也可以手动编译项目。

### 使用CMake手动编译

```cmd
mkdir build
cd build
cmake ..
cmake --build . --config Release
```

### 使用g++手动编译

```cmd
mkdir bin obj obj\cards obj\game obj\player obj\resources obj\ui

g++ -std=c++17 -Wall -Wextra -Iinclude -c src/Types.cpp -o obj/Types.o
g++ -std=c++17 -Wall -Wextra -Iinclude -c src/main.cpp -o obj/main.o
REM ... (编译其他源文件)

g++ -std=c++17 -o bin/7wonders_duel.exe obj/*.o obj/cards/*.o obj/game/*.o obj/player/*.o obj/resources/*.o obj/ui/*.o
```

完整的编译命令请参考 `build_mingw.bat` 脚本。

## 使用Visual Studio Code开发

如果您使用 **Visual Studio Code** 进行开发,可以安装以下扩展:

- **C/C++** (Microsoft)
- **CMake Tools** (Microsoft)

然后在VS Code中打开项目目录,按 `Ctrl+Shift+P`,选择 **"CMake: Configure"**,即可配置项目。

配置完成后,按 `F7` 或选择 **"CMake: Build"** 即可编译项目。

## 项目文件说明

| 文件名 | 说明 |
|--------|------|
| `CMakeLists.txt` | CMake配置文件,用于跨平台编译 |
| `build_windows.bat` | Windows自动编译脚本(使用CMake) |
| `build_mingw.bat` | MinGW编译脚本(直接使用g++) |
| `run_game.bat` | 游戏运行脚本 |
| `Makefile` | Linux/Unix编译配置(Windows不需要) |

## 获取帮助

如果您在编译或运行过程中遇到问题,可以:

1. 仔细阅读本文档的"常见问题"部分
2. 检查编译器和CMake的版本是否符合要求
3. 查看编译时的详细错误信息,通常会指出问题所在

祝您游戏愉快!

---

**作者**: Manus AI  
**更新日期**: 2025年12月15日
