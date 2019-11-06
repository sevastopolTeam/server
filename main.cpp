#include <iostream>
#include <exception>
#include <functional>
#include <signal.h>

#include "sources/application/application.h"

THolder<TApplication> application;

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cout << "miss config file" << std::endl;
        }
        application.reset(new TApplication());
        auto term = [](int signum) {
            std::cout << "Interrupt signal (" << signum << ") received.\n";
            exit(0);
        };
        signal(SIGINT, term);

        application->Start();
        return 0;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
