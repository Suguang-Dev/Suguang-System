#include "RGB.hpp"
#include <string>

uint8_t RGB::HexToInt(const string& Hex){
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
RGB::RGB(const string& InputRGBString){      // 只给一个字符串就……转成RGB颜色然后颜色化
    string RedGreenBlueString               =       InputRGBString;                                 // 拷贝一份, 不会改变原值

    for(char &c : RedGreenBlueString)  c    =       static_cast<char>(std::tolower(static_cast<unsigned char>(c))); 
                                                                                                    // 强迫症犯了必须小写
    if(RedGreenBlueString.empty() == false                                                          // 不是空的才给过不要等下炸了.
    and RedGreenBlueString.at(0) == '#' )           RedGreenBlueString.erase(RedGreenBlueString.begin());
                                                                                                    // 删掉一些开头"#"
    if(RedGreenBlueString.size() == 3){                                                             // 短写的RGB代号, 没事转一下
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
uint8_t RGB::GetColor(Get Color) const {     // 合理的获取颜色而不是不优雅的RGB::Red
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

