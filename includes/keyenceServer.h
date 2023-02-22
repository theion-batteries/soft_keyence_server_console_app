/**
 * @file keyenceServer.h
 * @author your name (you@domain.com)
 * @brief
 * @version 0.1
 * @date 2023-02-22
 *
 * @copyright Copyright (c) 2023
 *
 */

#pragma once 
#include "sockpp/socket.h"
#include <string>
#include <iostream>
#include <thread>
#include "sockpp/tcp_acceptor.h"
#include "sockpp/version.h"
#include "keyence_client.h"

class keyenceServer
{
private:
    keyence_client Kclient;
    std::string server_ip = "127.0.0.1";
    uint16_t server_server_port = 6666;
public:
    keyenceServer(/* args */);
    ~keyenceServer();
    void run_server();
    double get_value_sensor();
};

keyenceServer::keyenceServer(/* args */)
{
}

keyenceServer::~keyenceServer()
{
}

void keyenceServer::run_server()
{
    std::cout << "keyence server is running" << std::endl;
    Kclient.connect();

    sockpp::initialize();

    sockpp::tcp_acceptor acc(server_port);

    if (!acc) {
        cerr << "Error creating the acceptor: " << acc.last_error_str() << endl;
        return 1;
    }
    cout << "Awaiting connections on server_port " << server_port << "..." << endl;

    while (true) {
        sockpp::inet_address peer;

        // Accept a new client connection
        sockpp::tcp_socket sock = acc.accept(&peer);
        cout << "Received a connection request from " << peer << endl;

        if (!sock) {
            cerr << "Error accepting incoming connection: "
                << acc.last_error_str() << endl;
        }
        else {
            // Create a thread and transfer the new stream to it.
            thread thr(run_echo, std::move(sock));
            thr.detach();
        }
    }

}

void run_echo(sockpp::tcp_socket sock)
{
    ssize_t n;
    char buf[512];

    while ((n = sock.read(buf, sizeof(buf))) > 0)
        sock.write_n(buf, n);

    cout << "Connection closed from " << sock.peer_address() << endl;
}
double keyenceServer::get_value_sensor()
{
   return Kclient.get_value_output(0);
}
