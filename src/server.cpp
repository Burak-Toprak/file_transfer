/**
 * Author:  Burak Toprak
 **/

#include <iostream>
#include "server.h"

#pragma warning(disable:4996)

Server::Server(string in_connection_type) : connection_type(in_connection_type) {
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
	{
        cout << "The Winsock dll not found!" << endl;
    }
    server_socket = INVALID_SOCKET;
    if(connection_type == "tcp")
    {
        server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    else if(connection_type == "udp")
    {
        server_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
    else
    {
        cout << "Connection type must be 'tcp' or 'udp'." << endl;
    }
    if(server_socket == INVALID_SOCKET)
    {
        cout << "Socket creation failed" << endl;
        return;
    }
    sockaddr_in address;
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = inet_addr("127.0.0.1");
    address.sin_port = htons(55555);
    bind(server_socket, reinterpret_cast<SOCKADDR*>(&address), sizeof(address));
}

Server::~Server() {
    if(server_socket != INVALID_SOCKET)
    {
        closesocket(server_socket);
    }
    WSACleanup();
}

bool Server::start_listening() {
    if(connection_type == "tcp")
    {
        if(listen(server_socket, 5) == SOCKET_ERROR)
        {
            cout << "Listening failed" << endl;
            return false;
        }
    }
    return true;
}

Stream* Server::accept_connection() {
    if(connection_type == "tcp")
    {
        SOCKET accept_socket = accept(server_socket, NULL, NULL);
        if(accept_socket == INVALID_SOCKET)
        {
            cout << "Connection acception failed" << endl;
            return NULL;
        }
        cout << "Connection established." << endl;
        return new Stream(accept_socket, connection_type);
    }
    else if(connection_type == "udp")
    {
        return new Stream(server_socket, connection_type);        
    }
    else
    {
        cout << "Connection type must be 'tcp' or 'udp'." << endl;
        return NULL;
    }
}