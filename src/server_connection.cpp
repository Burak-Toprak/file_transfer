/**
 * Author:  Burak Toprak
 **/

#include "server_connection.h"

Server* TCPConnection::create_server() {
    return new Server("tcp");  
}

Server* UDPConnection::create_server() {
    return new Server("udp");  
}

ConnectionStrategy* TCPFactory::create_connection() {
    return new TCPConnection();
}

ConnectionStrategy* UDPFactory::create_connection() {
    return new UDPConnection();
}