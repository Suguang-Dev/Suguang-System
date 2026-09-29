#pragma once

// ===== 标准库 =====
#include <iostream>
#include <string>
#include <cstdint>
#include <cctype>
#include <cstdlib>
#include <stdexcept>
#include <bitset>
#include <thread>
#include <chrono>

// ===== Windows API =====
#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#undef RGB

// ===== C语言标准库 =====
#include <cpuid.h>

using namespace std;

namespace ErrorCodes{                                                                                                   //错误代码
    constexpr const char* success    =   "DONE";
    constexpr const char* fail       =   "FAIL";
    constexpr const char* unknown    =   "UKOW";
};