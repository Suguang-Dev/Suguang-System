@echo off
chcp 65001 >nul
echo [Build] 开始构建 C++23 模块项目...

set GCC="F:/gcc/MSYS2_GCC_16.2.0/ucrt64/bin/g++.exe"
set STDCC="F:/gcc/MSYS2_GCC_16.2.0/ucrt64/include/c++/16.2.0/bits/std.cc"

:: 检查是否已经生成了 std 模块缓存
if not exist gcm.cache (
    echo [Build] 第一次运行，正在编译标准库模块 std.cc ...
    %GCC% -std=c++23 -fmodules-ts -x c++ -c %STDCC% -o std.o
    echo [Build] 标准库模块编译完成！
)

echo [Build] 正在编译 main.cpp ...
%GCC% -std=c++23 -fmodules-ts main.cpp -o main.exe -lstdc++exp

if %errorlevel% neq 0 (
    echo [Build] 编译失败，请检查代码中的错误。
    pause
    exit /b
)

echo [Build] 编译成功。
pause