/**
 * Author:  Burak Toprak
 **/

#include <iostream>
#include "client.h"

#pragma warning(disable:4996)

Client::Client(string in_connection_type) : connection_type(in_connection_type) {
    WSADATA wsaData;
    if(WSAStartup(MAKEWORD(2, 2), &wsaData) != 0) 
	{
        cout << "The Winsock dll not found!" << endl;
    }    
    client_socket = INVALID_SOCKET;
    if(connection_type == "tcp")
    {
        client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    }
    else if(connection_type == "udp")
    {
        client_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    }
    else
    {
        cout << "Connection type must be 'tcp' or 'udp'." << endl;
    }
    if(client_socket == INVALID_SOCKET)
    {
        cout << "Socket creation failed" << endl;
        return;
    }
}

Client::~Client() {
    if(client_socket != INVALID_SOCKET)
    {
        closesocket(client_socket);
    }
    WSACleanup();
}

Stream* Client::create_stream() {
    if(connection_type == "tcp")
    {
        sockaddr_in address;
        address.sin_family = AF_INET;
        address.sin_addr.s_addr = inet_addr("127.0.0.1");
        address.sin_port = htons(55555);
        if(connect(client_socket, reinterpret_cast<SOCKADDR*>(&address), sizeof(address)) == SOCKET_ERROR)
        {
            cout << "Connection failed" << endl;
            return NULL;
        }
    }
    return new Stream(client_socket, connection_type);
}