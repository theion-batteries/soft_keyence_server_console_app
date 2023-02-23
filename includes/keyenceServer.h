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
    std::vector<double> values;

public:
    keyenceServer(std::string keyence_controller_ip);
    ~keyenceServer();
    int run_server();
    double get_value_sensor();
    int emit_value_sensor_to_client(sockpp::tcp_socket sock);
};

keyenceServer::keyenceServer(std::string keyence_controller_ip)
{
    Kclient = new keyence_client(keyence_controller_ip);
}

keyenceServer::~keyenceServer()
{
    delete Kclient;
}

int keyenceServer::run_server()
{
    std::cout << "keyence server is running" << std::endl;
    Kclient->connect();
    sockpp::socket_initializer sockInit;
    sockpp::tcp_acceptor acc(server_port);
    //acc.set_non_blocking(true);

    if (!acc) {
        cerr << "Error creating the acceptor: " << acc.last_error_str() << endl;
        return 1;
    }
    cout << "Awaiting connections on server_port " << server_port << "..." << endl;

    while (true) {
        sockpp::inet_address peer;

        // Accept a new client connection
        sockpp::tcp_socket sock = acc.accept(&peer);
        //sock.set_non_blocking(true);
        cout << "Received a connection request from " << peer << endl;

        if (!sock) {
            cerr << "Error accepting incoming connection: "
                << acc.last_error_str() << endl;
        }
        else {
            thread thr(&keyenceServer::emit_value_sensor_to_client, this, std::move(sock));
            thr.detach();
        }
    }

}

int keyenceServer::emit_value_sensor_to_client(sockpp::tcp_socket sock) // (sockpp::tcp_socket sock)
{
    ssize_t n;
    char buf[5012];

    while ((n = sock.read(&buf, sizeof(buf))) > 0)
    {
        std::cout << "n bytes received: " << n << std::endl;
        std::string incoming_data = buf;
        incoming_data.resize(n);
        std::cout << "received " << incoming_data << endl;
        if (incoming_data == "?")
        {
        values.insert(values.begin(), get_value_sensor());
        std::cout << "forwarding value sensor " << values[0] <<" to client"<< std::endl;
        sock.write(to_string(values[0]));
        }
        else
        {
        
        std::cout << "cmd not recognized"<< std::endl;
        sock.write("NA");        }


    }

    cout << "Connection closed from " << sock.peer_address() << endl;
    return 0;
}
double keyenceServer::get_value_sensor()
{
    return Kclient->get_value_output(0);
}
