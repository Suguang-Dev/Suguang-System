#pragma once
#include "RGB.hpp"
#include "stdafx.hpp"
#include "StyleSystem.hpp"
#include <cstring>

using std::string;

class BIOS{                                                                                                            //标准输入输出系统
    public:
        enum Authority{ Guest , NormalUser , HighUser , SuperUser , SYSTEM , TrustedInstaller , SystemMakerTeam };
    private:
        const string LatestUpdate =     "20260925(Q3)";  //start on 260925
        const string      Version =     "Standard";
        const string        Maker =     "Suguang-Dev(on Github)";
        const string        Email =     "suguang_163com@163.com";
              string     UserName =     "User";
              string      CPUInfo =     "Unknown CPU";
            uint64_t   MemoryInfo =     0; //GiB

    public:
        BIOS();
        BIOS(string);
        string ver();
        void write(char);
        void write(char,const StyleSystem::ColorStyle&) ;
        void write(char,int,int,int) ;
        void write(char,const RGB&) ;
        void input(string& str);
        void backspace(const StyleSystem::ColorStyle& s={});
        void ClearScreen(DWORD DelayMs = 0);
        void Ring(DWORD freq=440, DWORD duration = 100) ;
        void end();
        ~BIOS();
        void PowerOnSelfTest();
        string GetCPUInfo() ;
        uint64_t CheckMemory() ;
};
