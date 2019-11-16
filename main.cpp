#include <ctime>
#include <exception>
#include <iostream>
#include <functional>
#include <signal.h>

#include "sources/application/application.h"

THolder<TApplication> application;

int main(int argc, char* argv[]) {
    try {
        srand(time(0));
        if (argc < 2) {
            std::cout << "missing config file" << std::endl;
        }
        application.reset(new TApplication());
        auto term = [](int signum) {
            std::cout << "Interrupt signal (" << signum << ") received.\n";
            exit(0);
        };
        signal(SIGINT, term);
        signal(SIGTERM, term);

        application->Start();
        return 1;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
