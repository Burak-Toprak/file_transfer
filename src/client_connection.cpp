/**
 * Author:  Burak Toprak
 **/

#include "client_connection.h"

Client* TCPConnection::create_client() {
    return new Client("tcp");  
}

Client* UDPConnection::create_client() {
    return new Client("udp");  
}

ConnectionStrategy* TCPFactory::create_connection() {
    return new TCPConnection();
}

ConnectionStrategy* UDPFactory::create_connection() {
    return new UDPConnection();
}