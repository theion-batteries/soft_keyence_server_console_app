#include "keyenceServer.h"
#include <iostream>
#include <string>

int main(int argc, char* argv[])
{
    // Default value
    std::string _ip = "192.168.0.104";
    std::string ip = "";
    // Prompt user for input
    std::cout << "Enter an keyence controller ip, or press enter to use the default value: ";
    std::getline(std::cin, ip);

    // Check if an argument was provided
    if (argc > 1) {
        ip = argv[1];
    }

    // Use default value if input is empty
    if (ip.empty()) {
        ip = _ip;
    }
    // Print out the argument
    std::cout << "ip used: " << ip << std::endl;
    std::cout << "connect to this server forwarder with port: 6666 \n";
    std::cout << "send th server ? to get sensor value \n";

    keyenceServer KS {ip};
    KS.run_server();
    return 0;
}
