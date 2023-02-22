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
#include <vector>
#include "sockpp/tcp_acceptor.h"
#include "sockpp/version.h"
#include "keyence_client.h"
using namespace std;


class keyenceServer
{
private:
    keyence_client* Kclient;
    std::string server_ip = "127.0.0.1";
    uint16_t server_port = 6666;
    std::vector<double> values ;

public:
    keyenceServer(/* args */);
    ~keyenceServer();
    int run_server();
    double get_value_sensor();
    int emit_value_sensor_to_client(sockpp::tcp_socket sock);
};

keyenceServer::keyenceServer(/* args */)
{
    Kclient = new keyence_client("192.168.0.104");
}

keyenceServer::~keyenceServer()
{
    delete Kclient;
}

int keyenceServer::run_server()
{
    std::cout << "keyence server is running" << std::endl;
    Kclient->connect();

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
            thread thr(&keyenceServer::emit_value_sensor_to_client, this,std::move(sock));
            thr.detach();
        }
    }

}

int keyenceServer::emit_value_sensor_to_client(sockpp::tcp_socket sock) // (sockpp::tcp_socket sock)
{
    ssize_t n;
    char buf[512];

    while ((n = sock.read(buf, sizeof(buf))) > 0)
    {
       values.push_back(get_value_sensor());
        sock.write_n(&values[0],values.size());

    }
    
    cout << "Connection closed from " << sock.peer_address() << endl;
    return 0;
}
double keyenceServer::get_value_sensor()
{
   return Kclient->get_value_output(0);
}
