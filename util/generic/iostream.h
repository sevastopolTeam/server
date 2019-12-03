#pragma once

#include <ctime>
#include <iostream>
#include <fstream>
#include <chrono>

#include "string.h"

#define Cout std::cout
#define Cin std::cin
#define Endl std::endl

namespace {
    inline TString _GetNowTime() {
        using std::chrono::system_clock;
        auto currentTime = system_clock::now();

        int millis = static_cast<int>((currentTime.time_since_epoch().count() / 1000000) % 1000);
        std::time_t tt = system_clock::to_time_t(currentTime);
        auto timeinfo = localtime(&tt);

        char buffer[24];
        strftime(buffer, 24, "%FT%H:%M:%S", timeinfo);
        sprintf(buffer, "%s.%03d", buffer, millis);
        return buffer;
    }
} // namespace

void DoInitGlobalLog(const TString& logPath);

extern std::ostream* _CoutLog;

#define OUTPUT_DATETIME _GetNowTime()
#define CODE_FILE_LINE '(' << __FILE__ << ':' << __LINE__ << ')'
#define GET_STREAM (_CoutLog ? *_CoutLog : Cout)

#define ERROR_LOG GET_STREAM << "[ERROR] " << OUTPUT_DATETIME << ' ' << CODE_FILE_LINE << ": "
#define INFO_LOG GET_STREAM << "[INFO] " << OUTPUT_DATETIME << ": "
