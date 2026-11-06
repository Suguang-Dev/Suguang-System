# Suguang-System

一个使用 C++ 23 开发的 Windows Terminal 模拟 BIOS 程序.\
本项目目前仅支持中文文档.

**Suguang System开发团队名单**:

主开发者:
- [Suguang-Dev](https://github.com/Suguang-Dev)

Issues 回复:
- [Suguang-QA-Bot](https://github.com/Suguang-QA-Bot)

## 🚨 防伪与免责声明

**本项目除部分内部测试版本闭源外, 其余版本完全开源, 且仅通过上方 GitHub 账号发布.<br>
非官方 [Releases](https://github.com/Suguang-Dev/Suguang-System/releases) 页面提供的下载文件均为盗版.**

- 任何未在官方 [Releases](https://github.com/Suguang-Dev/Suguang-System/releases) 通知或获取原作者授权后的\
 可执行文件或源码, 均有可能为盗版, 请注意辨别.
- 防伪措施开发中, 暂不透露.
- 如果本项目在未授权的地方被传播, 请立刻发送邮件至 `suguang_163com@163.com` 举报.

## ⚠️ 已知问题与环境兼容性

### 1. 旧版控制台真彩色失效
在开发者[Suguang-Dev](https://github.com/Suguang-Dev)的测试编译环境下, <br>
**Windows 10 21H2 以下的操作系统**可能因为默认控制台程序为 `cmd.exe` 或 `conhost.exe`, <br>
**无法正确地将类似 `\033[38;2;r;g;bm` 的 ANSI 转义字符转义为真彩色**.这并非程序漏洞.<br>
**解决方案**:请在**系统管理员同意**的前提下, 安装 [Windows Terminal](https://aka.ms/terminal).
*注:本文所提供的链接均在 `hosts` 文件未被篡改的前提下有效.若发现非 Microsoft Store 界面或被安全软件阻止的网页*
*（自定义规则限制除外）, 请立刻关闭并检查本机 `hosts` 文件是否被篡改.*

### 2. 其他可能漏洞
- 你的 CPU 不支持 `__cpuid` 指令时, 程序将设定为 `Unknown CPU`.
- 外部 API 调用异常.
- 第三方插件指针错误等.`[注释A]`
- 等等.

若发现出错, 请发送 Issue 至 [GitHub Issues](https://github.com/Suguang-Dev/Suguang-System/issues), 
或发送邮件至 `suguang_163com@163.com`.

## 🛠️ 编译方式

- **编译前, 请双击运行 `buildstd.bat` 以搭建标准库环境！**
- 推荐使用 [MSYS2](https://www.msys2.org/) 并且搭配 `MINGW64` 版编译.
- 在编译的时候, 需要将 `/src` 目录下的所有 `.cpp` 文件编译, 否则会导致链接错误.
- 可以在 PowerShell 里运行的参考命令（请将第一段替换为你的实际目录）:

```powershell
cd "C:\CPP\Suguang System" ; if ($?) { g++ -std=c++23 -fmodules-ts -Wall -Iinclude -Isrc main.cpp src/*.cpp -o main.exe -lstdc++exp }
```

## 📝 注释
[注释A]非官方衍生版本、第三方魔改插件、
或违反本声明修改代码所引发的任何指针错误、内存泄漏及系统崩溃, 均与原开发者团队无关.