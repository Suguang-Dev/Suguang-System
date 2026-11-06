@echo off
chcp 65001 >nul
echo [Build] 开始构建 C++23 模块项目...

set GCC="F:/gcc/MSYS2_GCC_16.2.0/ucrt64/bin/g++.exe"
set STDCC="F:/gcc/MSYS2_GCC_16.2.0/ucrt64/include/c++/16.2.0/bits/std.cc"

:: 检查是否已经生成了 std 模块缓存
if not exist gcm.cache (
    echo [Build] 盲猜你是第一次跑这玩意儿，等我整个 std.cc ...
    %GCC% -std=c++23 -fmodules-ts -x c++ -c %STDCC% -o std.o
    echo [Build] （拍出灰尘）行了。
)

echo [Build] 等我整下 main.cpp 哈 ...
%GCC% -std=c++23 -fmodules-ts -Wall -Iinclude -Isrc main.cpp src/*.cpp -o main.exe -lstdc++exp

if %errorlevel% neq 0 (
    echo [Build] 完犊子了炸了，赶紧投诉Suguang-Dev的屎山代码
    pause
    exit /b
)

echo [Build] 行了，直接跑得了。
pause