#ifdef _WIN64

#include "stdafx.hpp"
#include "RGB.hpp"
#include "BIOS.hpp"


void StringWrite(const string& str){   //Issue by @Suguang-Dev, Created & Published. SYSTEM-App do not use this.
    BIOS b;
    for(char c:str) b.write(c);
}


void MainFunction(BIOS& bios){

}


int main(void){
    BIOS bios;
    bios.PowerOnSelfTest();
    MainFunction(bios);
    bios.end();
    cin.get();
    return 0;
}


#else
#error "This system is for Windows NT 10.0 64bits or later. And pls use Windows Terminal."
#endif