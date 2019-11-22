#pragma once

#include <ctime>
#include <iostream>
#include <fstream>
#include <mutex>

#include "string.h"

#define Cout std::cout
#define Cin std::cin
#define Endl std::endl

namespace {
    inline tm _localtime_xp(time_t timer) {
        tm bt{};
#if defined(__unix__)
        localtime_r(&timer, &bt);
#elif defined(_MSC_VER)
        localtime_s(&bt, &timer);
#else
        static std::mutex mtx;
        std::lock_guard<std::mutex> lock(mtx);
        bt = *localtime(&timer);
#endif
        return bt;
    }

    inline char* _GetNowTime() {
        static char _buffer[20] = "TODO";
        // strftime(_buffer, 20, "%Y/%m/%dT%X", &_localtime_xp(time(NULL))); // Don't work on macos
        return _buffer;
    }
} // namespace


void DoInitGlobalLog(const TString& logPath);

extern std::ostream* _CoutLog;

#define OUTPUT_DATETIME _GetNowTime()
#define CODE_FILE_LINE '(' << __FILE__ << ':' << __LINE__ << ')'
#define GET_STREAM (_CoutLog ? *_CoutLog : Cout)

#define ERROR_LOG GET_STREAM << "[ERROR] " << OUTPUT_DATETIME << ' ' << CODE_FILE_LINE << ": "
#define INFO_LOG GET_STREAM << "[INFO] " << OUTPUT_DATETIME << ": "
