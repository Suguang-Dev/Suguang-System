#pragma once
#include "stdafx.hpp"

constexpr const char* EMPTY_STRING = "";

//      ====================================
//      =     主要类的定义以及类内实现     =
//      ====================================

class RGB{                                                                                                              //标准色彩通道

    private:
        uint8_t Red;        //红色通道, 对应 StyleSystem::ColorStyle::FCRC
        uint8_t Green;      //绿色通道, 对应 StyleSystem::ColorStyle::FCGC
        uint8_t Blue;       //蓝色通道, 对应 StyleSystem::ColorStyle::FCBC
        static uint8_t HexToInt(const string& Hex);
    public:
        enum class Get{     // 枚举: 当前对象    红, 绿, 蓝  分别的十进制值    作为传入的参数
            _Red_,          // 红的;
            _Green_,        // 蓝的;
            _Blue_          // 绿的;
        };
        constexpr RGB();
        constexpr RGB(uint8_t, uint8_t, uint8_t);
        RGB(const string& InputRGBString);
        uint8_t GetColor(Get) const;
};

constexpr RGB::RGB():                                  // 不传参就黑化
    Red     (   0   ),
    Green   (   0   ),
    Blue    (   0   )
{}
constexpr RGB::RGB(uint8_t r, uint8_t g, uint8_t b):   // 只要是数字合规直接放你过不黑化 (除非故意传 (0,0,0) 让咱黑化) 
    Red     (   r   ), 
    Green   (   g   ),                                                                              // 颜色化
    Blue    (   b   )
{}

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