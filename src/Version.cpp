#include "Version.hpp"
namespace {
    constexpr const char* MainVer  = "0";
    constexpr const char* ForkVer  = "1";
    constexpr const char* Point    = "000";
    constexpr const char* Created  = __DATE__;
    constexpr const char* Tips     = "-ttt";

    std::string GetVersion(){
        return std::string(MainVer)+"."+ForkVer+"."+Point+" ("+Created+") "+Tips;
    }
    bool Verify(){
        //TODO
        return !false;
    }
}