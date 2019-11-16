#include <ctime>
#include <exception>
#include <functional>
#include <signal.h>

#include "sources/application/application.h"
#include "util/generic/iostream.h"

THolder<TApplication> application;

int main(int argc, char* argv[]) {
    try {
        srand(time(0));
        if (argc < 2) {
            Cout << "missing config file" << Endl;
        }
        application.reset(new TApplication());
        auto term = [](int signum) {
            Cout << "Interrupt signal (" << signum << ") received.\n";
            exit(0);
        };
        signal(SIGINT, term);
        signal(SIGTERM, term);

        application->Start();
        return 1;
    } catch (const std::exception& e) {
        Cout << e.what() << Endl;
        return 1;
    }
}
