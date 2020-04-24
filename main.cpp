#include <ctime>
#include <exception>
#include <functional>
#include <signal.h>
#include <fstream>
#include <streambuf>

#include "sources/application/application.h"
#include "util/generic/iostream.h"

THolder<TApplication> application;

TString ReadFile(const TString& path) {
    std::ifstream stream(path);
    return TString((std::istreambuf_iterator<char>(stream)), std::istreambuf_iterator<char>());
}

int main(int argc, char* argv[]) {
    try {
        Cout << "Program started" << Endl;
        TString configPath = "config/test.json";
        if (argc > 1) {
            configPath = argv[1];
        }
        NJson::TJsonValue config = NJson::TJsonValue::parse(ReadFile(configPath));

        DoInitGlobalLog(config["Log"]);
        INFO_LOG << "Server start with " << configPath << Endl;

        application.reset(new TApplication(config));
        auto term = [](int signum) {
            ERROR_LOG << "Interrupt signal (" << signum << ") received" << Endl;
            exit(0);
        };
        signal(SIGINT, term);
        signal(SIGTERM, term);

        application->Start();
        return 1;
    } catch (const std::exception& e) {
        ERROR_LOG << e.what() << Endl;
        return 1;
    }
}
