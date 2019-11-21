#include <ctime>
#include <exception>
#include <functional>
#include <signal.h>

#include "sources/application/application.h"
#include "util/generic/iostream.h"

THolder<TApplication> application;

int main(int argc, char* argv[]) {
    try {
        DoInitGlobalLog("console");
        Cout << "Program started" << Endl;
        srand(static_cast<unsigned int>(time(NULL)));
        if (argc < 2) {
            ERROR_LOG << "missing config file" << Endl;
        }
        application.reset(new TApplication());
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
