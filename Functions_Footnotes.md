# 对于本"Study System" `main.cpp` 中一些函数的介绍

## RGB 类

### 枚举(`enum`)
1. `RGB::Get`：在使用`GetColor(RGB::Get)`函数里作为必须传参。内含`_Red_`,`_Green_`,`_Blue_`.

### 构造函数

1. `RGB()`(无参数版本)：默认使用 `#000000`；
2. `RGB(uint8_t, uint8_t, uint8_t)` (三个`0~255`区间数字版本)：将数字Red Green Blue值导入至对象；
3. `RGB(string&)` (RGB字面量)：将`#RRGGBB`或`#RGB`转为数字导入至对象；
4. `//更多` 未来考虑使用HSL等其他表达方式转换……
 
### 普通函数

1. `GetColor(RGB::Get)`：获取Red/Green/Blue的值(类型：`uint8_t`)。

## BIOS 类

###