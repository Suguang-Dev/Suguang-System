#pragma once
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