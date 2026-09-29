#ifdef _WIN64

#include "stdafx.hpp"
#include "RGB.hpp"
#include "BIOS.hpp"


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


#else
#error "This system is for Windows NT 10.0 64bits or later. And pls use Windows Terminal."
#endif