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
        std::chrono::time_point<std::chrono::system_clock> now = std::chrono::system_clock::now();
        auto duration = now.time_since_epoch();

        typedef std::chrono::duration<int, std::ratio_multiply<std::chrono::hours::period, std::ratio<3>>::type> Days; /* UTC: -3:00 */

        Days days = std::chrono::duration_cast<Days>(duration);
        duration -= days;
        auto hours = std::chrono::duration_cast<std::chrono::hours>(duration);
        duration -= hours;
        auto minutes = std::chrono::duration_cast<std::chrono::minutes>(duration);
        duration -= minutes;
        auto seconds = std::chrono::duration_cast<std::chrono::seconds>(duration);
        duration -= seconds;
        auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(duration);

        std::time_t tt = std::chrono::system_clock::to_time_t(now);
        auto timeinfo = localtime(&tt);

        char buffer[24];
        strftime(buffer, 24, "%F", timeinfo);
        sprintf(buffer, "%sT%02d:%02d:%02d.%03d",
            buffer,
            static_cast<int>(hours.count()),
            static_cast<int>(minutes.count()),
            static_cast<int>(seconds.count()),
            static_cast<int>(milliseconds.count())
        );
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
