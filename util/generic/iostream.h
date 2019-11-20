#pragma once

#include <ctime>
#include <iostream>
#include <fstream>

#include "holder.h"
#include "string.h"

#define Cout std::cout
#define Cin std::cin
#define Endl std::endl

namespace {
    static time_t _seconds;
    static struct tm* _local;
    static char _buffer[20];

    inline char* _GetNowTime() {
        _seconds = time(NULL);
        _local = localtime(&_seconds);
        strftime(_buffer, 20, "%Y/%m/%dT%X", _local);
        return _buffer;
    }
} // namespace

#define OUTPUT_DATETIME _GetNowTime()

static std::ostream* _CoutInfo(&Cout);
/*
static void DoInitGlobalLog(const TString& logPath) {
    if (logPath != "console") {
        _CoutInfo = new std::ofstream(logPath);
    }
}
*/
#define ERROR_LOG *_CoutInfo << "[ERROR] " << OUTPUT_DATETIME << " (" << __FILE__ << ":" << __LINE__ <<"): "
#define INFO_LOG *_CoutInfo << "[INFO] " << OUTPUT_DATETIME << ": "
