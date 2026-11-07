#ifdef _WIN64

#include "stdafx.hpp"
#include "sysstd.hpp"
using namespace std;

// version: 0.1.{20260929.215244} -ttt

void StringWrite(const string& str, BIOS& b){   
    //Issue by @Suguang-Dev, Created & Published. 
    //SYSTEM-App do not use this.
    for(char c:str) b.write(c);
}


void MainFunction(BIOS& bios){
    for(char c:bios.ver()) bios.write(c);
}


int main(void){
    BIOS bios;
    bios.PowerOnSelfTest();
    MainFunction(bios);
    bios.ClearScreen();
    bios.end();
    cin.get();
    return 0;
}


#else
#error "This system is for Windows NT 10.0 64bits or later. And pls use Windows Terminal."
#endif