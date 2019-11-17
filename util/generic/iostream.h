#pragma once

#include <ctime>
#include <iostream>

#define Cout std::cout
#define Cin std::cin
#define Endl std::endl

namespace {
    static time_t seconds;
    static struct tm* timeinfo;
    static char buffer[20];

    inline char* GetNowTime() {
        seconds = time(NULL);
        timeinfo = localtime(&seconds);
        strftime(buffer, 20, "%Y/%m/%dT%X", timeinfo);
        return buffer;
    }
} // namespace

#define OUTPUT_DATETIME GetNowTime()

#define INFO_LOG Cout << "[INFO] " << OUTPUT_DATETIME << ": "
#define ERROR_LOG Cout << "[ERROR] " << OUTPUT_DATETIME << " (" << __FILE__ << ":" << __LINE__ <<"): "
