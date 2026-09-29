#include "BIOS.hpp"
BIOS::BIOS() = default;
BIOS::BIOS(string usrName){
    UserName = usrName;
}
string BIOS::ver(){
    return LatestUpdate + " " + Version + " " + Maker + "\n";
}
void BIOS::write(char c){
    cout << c;
}
void BIOS::write(char c, const StyleSystem::ColorStyle& s) {
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
void BIOS::write(char c, int r, int g, int b) {
    write(c,
        StyleSystem::ColorStyle(r,g,b)
    );
}
void BIOS::write(char c, const RGB& rgb) {
    write(c,
        StyleSystem::ColorStyle
        (
        rgb.GetColor(RGB::Get::_Red_),
        rgb.GetColor(RGB::Get::_Green_),
        rgb.GetColor(RGB::Get::_Blue_)
        )
    );
}
void BIOS::input(string& str){
            getline(cin,str);
        }
void BIOS::backspace(const StyleSystem::ColorStyle& s){
    write('\b',s);
    write(' ', s);
    write('\b',s);
}
void BIOS::ClearScreen(DWORD DelayMs){
    HANDLE     hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_SCREEN_BUFFER_INFO      csbi;
    if(hConsole == INVALID_HANDLE_VALUE
        or not GetConsoleScreenBufferInfo(hConsole, &csbi)) return;
    DWORD       columns = csbi.dwSize.X;
    DWORD          rows = csbi.dwSize.Y;
    DWORD       written = 0;
    for (DWORD i = 0; i < rows; i++) {
        COORD   linePos = { 0, (SHORT)i };
        FillConsoleOutputCharacterA(hConsole, ' ', columns, linePos, &written);
        FillConsoleOutputAttribute(hConsole, csbi.wAttributes, columns, linePos, &written);
        if (DelayMs > 0) Sleep(DelayMs);
    }
    COORD       TopLeft = { 0, 0 };
    SetConsoleCursorPosition(hConsole ,TopLeft);
}
void BIOS::Ring(DWORD freq, DWORD duration) {
    std::thread([freq, duration]() {
        Beep(freq, duration);
    }).detach();
}
void BIOS::end(){
    for(char c:"You can power off the system now.") write(c,StdColors::Warning);
}
BIOS::~BIOS() = default;
void BIOS::PowerOnSelfTest(){
    ClearScreen(0);
    for(char c:"Checking CPU Info...\n") write(c);
    for(char c:GetCPUInfo()) write(c);
    write('\n');
    for(char c:"Memory Testing...\n") write(c);
    uint64_t mint = CheckMemory();
    for (uint64_t i = 1; i <= mint; i+=1) {
        write('\r');
        for (int k = 0; k < 30; k++) write(' ');
        write('\r');
        for (char c : to_string(i) + " GiB") write(c);
        Sleep(10);
    }
    for(char c:" Done.\n") write(c);
    Sleep(1000);
    ClearScreen(100);
}
string BIOS::GetCPUInfo() {
    char brand[49] = {0};
    unsigned int regs[4];
    for (unsigned int i = 0; i < 3; i++) {
        __cpuid(0x80000002 + i, regs[0], regs[1], regs[2], regs[3]);
        memcpy(brand + i * 16, regs, 16);
    }
    CPUInfo = string(brand);
    return CPUInfo;
}
uint64_t BIOS::CheckMemory() {
    MEMORYSTATUSEX ms;
    ms.dwLength = sizeof(ms);
    GlobalMemoryStatusEx(&ms);
    DWORDLONG totalGiB =  (ms.ullTotalPhys + 512 * 1024 * 1024) / (1024ULL * 1024 * 1024);
    MemoryInfo = totalGiB;
    return totalGiB;
}