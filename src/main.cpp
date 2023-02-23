#include "keyenceServer.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    // Default value
    std::string ip = "192.168.0.104";

    // Check if an argument was provided
    if (argc > 1) {
        ip = argv[1];
    }

    // Print out the argument
    std::cout << "ip default: " << ip << std::endl;

    keyenceServer KS {ip};
    KS.run_server();
    return 0;
}
