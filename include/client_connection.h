/**
 * Author:  Burak Toprak
 **/

#include "client.h"

// ConnectionStrategy is an abstract class which is used to create the client with the given connection strategy (tcp or udp). Strategy design pattern is used to set the communication protocol and Factory Method design pattern is used to create the TCPConnection and UDPConnection objects.
class ConnectionStrategy {
    public:
        virtual Client* create_client() = 0;
        virtual ~ConnectionStrategy() {};
};

// TCPConnection object is used to create the client using tcp communication protocol.
class TCPConnection : public ConnectionStrategy {
    public:
        Client* create_client() override;
};

// UDPConnection object is used to create the client using udp communication protocol.
class UDPConnection : public ConnectionStrategy {
    public:
        Client* create_client() override;
};

// ConnectionFactory is an abstract class to implement the Factory Method design pattern. 
class ConnectionFactory {
    public:
        virtual ConnectionStrategy* create_connection() = 0;
        virtual ~ConnectionFactory () {};
};

// TCPFactory object creates a TCPConnection object using create_connection function.
class TCPFactory : public ConnectionFactory {
    public:
        ConnectionStrategy* create_connection() override;
};

// UDPFactory object creates a UDPConnection object using create_connection function.
class UDPFactory : public ConnectionFactory {
    public:
        ConnectionStrategy* create_connection() override;
};