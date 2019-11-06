#include <iostream>
#include <exception> 

#include "sources/application/application.h"

int main(int argc, char* argv[]) {
    try {
        if (argc < 2) {
            std::cout << "miss config file" << std::endl;
        }
        TApplication();
        return 0;
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        return 1;
    }
}
