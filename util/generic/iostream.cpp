#include "iostream.h"

std::ostream* _CoutLog(&Cout);

void DoInitGlobalLog(const TString& logPath) {
    if (logPath == "priemka") {
        _CoutLog = new std::ofstream("logs/preimka.log", std::ios_base::out);
    } else if (logPath != "console") {
        _CoutLog = new std::ofstream(logPath, std::ios_base::app);
    }
}
