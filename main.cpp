#ifdef _WIN64

#include "stdafx.hpp"
using namespace std;

//      ====================================
//      =      常量以及命名空间的定义      =
//      ====================================

namespace ErrorCodes{                                                                                                   //错误代码
    constexpr const char* success    =   "DONE";
    constexpr const char* fail       =   "FAIL";
    constexpr const char* unknown    =   "UKOW";
};

namespace StyleSystem{                                                                                                  //颜色设定

    class ColorStyle{
    public:
        uint8_t FontColorRedChannel          =   0xFF;          //  FCRC
        uint8_t FontColorGreenChannel        =   0xFF;          //  FCGC
        uint8_t FontColorBlueChannel         =   0xFF;          //  FCBC
        bool    FontFontBoldAdjustment       =   0x00;  //false //  FFBA
        bool    FontFontItalicAdjustment     =   0x00;  //false //  FFIA
        bool    FontFontUnderlineAdjustment  =   0x00;  //false //  FFUA
        bool    ShowBackgroundAdjustment     =   0x00;  //false //  BGSA
        uint8_t BackgroundColorRedChannel    =   0x00;          //  BCRC
        uint8_t BackgroundColorGreenChannel  =   0x00;          //  BCGC
        uint8_t BackgroundColorBlueChannel   =   0x00;          //  BCBC
    
        constexpr ColorStyle()               =   default;
        constexpr ColorStyle(
            uint8_t FCRC,
            uint8_t FCGC,
            uint8_t FCBC,
            bool    FFBA = 0x00,
            bool    FFIA = 0x00,
            bool    FFUA = 0x00,
            uint8_t BCRC = 0x00,
            uint8_t BCGC = 0x00,
            uint8_t BCBC = 0x00
        ):
            FontColorRedChannel             (FCRC),
            FontColorGreenChannel           (FCGC),
            FontColorBlueChannel            (FCBC),

            FontFontBoldAdjustment          (FFBA),
            FontFontItalicAdjustment        (FFIA),
            FontFontUnderlineAdjustment     (FFUA),

            BackgroundColorRedChannel       (BCRC),
            BackgroundColorGreenChannel     (BCGC),
            BackgroundColorBlueChannel      (BCBC)
        {}
    };

}


constexpr StyleSystem::ColorStyle BasicColorStyle(0xff,0xff,0xff,0,0,0,0x0,0x0,0x0);

constexpr const char* EMPTY_STRING = "";

//      ====================================
//      =     主要类的定义以及类内实现     =
//      ====================================

class RGB{                                                                                                              //标准色彩通道

    private:
        uint8_t Red;        //红色通道, 对应 StyleSystem::ColorStyle::FCRC
        uint8_t Green;      //绿色通道, 对应 StyleSystem::ColorStyle::FCGC
        uint8_t Blue;       //蓝色通道, 对应 StyleSystem::ColorStyle::FCBC
        static uint8_t HexToInt(const string& Hex){
            try{
                return static_cast<uint8_t>(stoi(Hex, nullptr, 16));
            }
            catch(const exception& e){
                cerr << "This Hex String"<< Hex
                     << " cannot change to int." << e.what() 
                     << '\n';
                return 0;
            }
        }
    public:
        enum class Get{     // 枚举: 当前对象    红, 绿, 蓝  分别的十进制值    作为传入的参数
            _Red_,          // 红的;
            _Green_,        // 蓝的;
            _Blue_          // 绿的;
        };
                //      ====================
                //      =     构造函数     =
                //      ====================
        constexpr RGB():                                  // 不传参就黑化
            Red     (   0   ),
            Green   (   0   ),
            Blue    (   0   )
        {}
        constexpr RGB(uint8_t r, uint8_t g, uint8_t b):   // 只要是数字合规直接放你过不黑化 (除非故意传 (0,0,0) 让咱黑化) 
            Red     (   r   ), 
            Green   (   g   ),                                                                              // 颜色化
            Blue    (   b   )
        {}
        RGB(const string& InputRGBString){      // 只给一个字符串就……转成RGB颜色然后颜色化
            string RedGreenBlueString               =       InputRGBString;                                  // 拷贝一份，不会改变原值

            for(char &c : RedGreenBlueString)  c    =       static_cast<char>(std::tolower(static_cast<unsigned char>(c))); 
                                                                                                            // 强迫症犯了必须小写
            if(RedGreenBlueString.empty() == false                                                          // 不是空的才给过不要等下炸了.
            and RedGreenBlueString.at(0) == '#' )           RedGreenBlueString.erase(RedGreenBlueString.begin());
                                                                                                            // 删掉一些开头"#"
            if(RedGreenBlueString.size() == 3){                                                             // 短写的RGB代号，没事转一下
                string OldRedGreenBlueString        =       RedGreenBlueString;                             // 临时变量因为需要重新赋值
                RedGreenBlueString                  =       EMPTY_STRING;                                   // 其实没啥用就是清空字符串
                for(char c:OldRedGreenBlueString)           RedGreenBlueString.append(2,c);                 // 删掉的我要两倍拿回来!
            }
            if(RedGreenBlueString.size() != 6){                                                             // 这还不是六的长度? 非标吧!
                cerr <<                                     "[RGB] Input NOT RGB Code! Error from: \""      // 炸了: 不是正经RGB! 
                     <<                                     RedGreenBlueString << "\"." << ErrorCodes::fail // 扔回给系统加上fail
                     <<                                     " \n";                                          // 依旧endl的宠被'\n'抢了
                    Red                             =       0;
                    Green                           =       0;                                              // 黑化了家人们
                    Blue                            =       0;
                return;                                                                                     // 炸
            }
            for(char c : RedGreenBlueString){                                                               // 依旧懒得写(i=0;i<n;i++)
                bool IF                             =       isxdigit(static_cast<unsigned char>(c));        // 检测是不是16进制
                if (not IF) {                                                                               // 不是?!!
                    cerr <<                                 "[RGB] Illegal Char. \"" << c << "\" in Code: " // 非法玩意儿枪毙了
                         <<                                 RedGreenBlueString << "Go to #000000\n";      // 黑化了家人们
                    Red                             =       0;
                    Green                           =       0;                                              // 黑化中……
                    Blue                            =       0;
                    return;
                }
            }
            Red     =   static_cast<uint8_t>(HexToInt(RedGreenBlueString.substr(0,2)));
            Green   =   static_cast<uint8_t>(HexToInt(RedGreenBlueString.substr(2,2)));                     // 颜色化
            Blue    =   static_cast<uint8_t>(HexToInt(RedGreenBlueString.substr(4,2)));
        }
                //      ====================
                //      =    获取值函数    =
                //      ====================
        uint8_t GetColor(Get Color) const {     // 合理的获取颜色而不是不优雅的RGB::Red
            switch(Color){
                case Get::_Red_:
                    return Red;
                case Get::_Green_:
                    return Green;
                case Get::_Blue_:
                    return Blue;
                default:
                    cerr << "Is maker made a new version and forgot to fix this? Call suguang_163com@163.com!\n";
                    return 0;
            }
        }
};

namespace StdColors{                            // 标准颜色色卡
    constexpr RGB StdRed     =  RGB(255 ,  0  ,  0 );
    constexpr RGB StdGreen   =  RGB( 0  , 255 ,  0 );
    constexpr RGB StdBlue    =  RGB( 0  ,  0  , 255);

    constexpr RGB StdYellow  =  RGB(255 , 255 ,  0 );
    constexpr RGB StdPurple  =  RGB(255 ,  0  , 255);
    constexpr RGB StdCyan    =  RGB( 0  , 255 , 255);

    constexpr RGB StdBlack   =  RGB( 0  ,  0  ,  0 );
    constexpr RGB StdDark    =  RGB( 64 ,  64 ,  64);
    constexpr RGB StdGrey    =  RGB(128 , 128 , 128);
    constexpr RGB StdLight   =  RGB(192 , 192 , 192);
    constexpr RGB StdWhite   =  RGB(255 , 255 , 255);

    constexpr RGB Success    =  StdGreen;
    constexpr RGB Warning    =  StdYellow;
    constexpr RGB Error      =  StdRed;
    constexpr RGB Info       =  StdCyan;
}

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
                //      ====================
                //      =     构造函数     =
                //      ====================
        BIOS() = default;
        BIOS(string usrName){
            UserName = usrName;
        }
                //      ====================
                //      =     获取版本     =
                //      ====================
        string ver(){
            return LatestUpdate + " " + Version + " " + Maker + "\n";
        }
                //      ====================
                //      =     显示函数     =
                //      ====================

        void write(char c){
            cout << c;
        }
        void write(char c, const StyleSystem::ColorStyle& s) {
            cout << (s.FontFontBoldAdjustment ?      "\033[1m"  : "")
                 << (s.FontFontItalicAdjustment ?    "\033[3m"  : "")
                 << (s.FontFontUnderlineAdjustment ? "\033[4m"  : "");
            if(s.ShowBackgroundAdjustment)
                cout << "\033[48;2;"
                     << (int)s.BackgroundColorRedChannel     << ";"
                     << (int)s.BackgroundColorGreenChannel   << ";"
                     << (int)s.BackgroundColorBlueChannel    << "m";
             cout << "\033[38;2;" 
                  << (int)s.FontColorRedChannel     << ";" 
                  << (int)s.FontColorGreenChannel   << ";" 
                  << (int)s.FontColorBlueChannel    << "m"
                  << c << "\033[0m";
        }
        void write(char c, int r, int g, int b) {
            write(c,
                StyleSystem::ColorStyle(r,g,b)
            );
        }
        void write(char c, const RGB& rgb) {
            write(c,
                StyleSystem::ColorStyle
                (
                rgb.GetColor(RGB::Get::_Red_),
                rgb.GetColor(RGB::Get::_Green_),
                rgb.GetColor(RGB::Get::_Blue_)
                )
            );
        }
                //      ====================
                //      =     输入函数     =
                //      ====================
        void input(string& str){
            getline(cin,str);
        }
                //      ====================
                //      =     退格函数     =
                //      ====================
        void backspace(const StyleSystem::ColorStyle& s={}){
            write('\b',s);
            write(' ', s);
            write('\b',s);
        }
                //      ====================
                //      =     慢速清屏     =
                //      ====================
        void ClearScreen(DWORD DelayMs = 0){
            HANDLE                          hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
            CONSOLE_SCREEN_BUFFER_INFO      csbi;
            if(hConsole == INVALID_HANDLE_VALUE
               or not GetConsoleScreenBufferInfo(hConsole, &csbi))      return;
            DWORD                            columns = csbi.dwSize.X;
            DWORD                               rows = csbi.dwSize.Y;
            DWORD                            written = 0;
            for (DWORD i = 0; i < rows; i++) {
                COORD                        linePos = { 0, (SHORT)i };
                FillConsoleOutputCharacterA(hConsole, ' ', columns, linePos, &written);
                FillConsoleOutputAttribute(hConsole, csbi.wAttributes, columns, linePos, &written);
                if (DelayMs > 0)                                        Sleep(DelayMs);
            }
            COORD                            TopLeft = { 0, 0 };
            SetConsoleCursorPosition(hConsole ,TopLeft);
        }
                //      ====================
                //      =   播放频率声音   =
                //      ====================
        void Ring(DWORD freq, DWORD duration = 100) {
            std::thread([freq, duration]() {
                Beep(freq, duration);
            }).detach();
        }
                //      ====================
                //      =     析构函数     =
                //      ====================
        void end(){
            for(char c:"You can power off the system now.") write(c,StdColors::Warning);
        }
        ~BIOS() = default;
        void PowerOnSelfTest();
        string GetCPUInfo() {
            char brand[49] = {0};
            unsigned int regs[4];
            for (unsigned int i = 0; i < 3; i++) {
                __cpuid(0x80000002 + i, regs[0], regs[1], regs[2], regs[3]);
                memcpy(brand + i * 16, regs, 16);
            }
            CPUInfo = string(brand);
            return CPUInfo;
        }
        uint64_t CheckMemory() {
            MEMORYSTATUSEX ms;
            ms.dwLength = sizeof(ms);
            GlobalMemoryStatusEx(&ms);

            DWORDLONG totalGiB =  (ms.ullTotalPhys + 512 * 1024 * 1024) / (1024ULL * 1024 * 1024);
            MemoryInfo = totalGiB;
            return totalGiB;
        }
};

void StringWrite(const string& str){   //Issue by @Suguang-Dev, Created & Published. SYSTEM-App do not use this.
    BIOS b;
    for(char c:str) b.write(c);
}

int main(void){
    BIOS bios;
    bios.PowerOnSelfTest();
    bios.end();
    system("pause");
    return 0;
}


void BIOS::PowerOnSelfTest(){
    ClearScreen(0);
    for(char c:"Checking CPU Info...\n") write(c);
    for(char c:GetCPUInfo()) write(c);
    write('\n');
    for(char c:"Memory Testing...\n") write(c);
    uint64_t mint = CheckMemory();
    for (int i = 1; i <= mint; i+=1) {
        write('\r');
        for (int k = 0; k < 30; k++) write(' ');
        write('\r');
        for (char c : to_string(i) + " GiB") write(c);
        Sleep(10);
    }
    for(char c:"Done.\n") write(c);
    Sleep(1000);
    ClearScreen(100);
}



#else
#error "This system is for Windows NT 10.0 64bits or later. And pls use Windows Terminal."
#endif