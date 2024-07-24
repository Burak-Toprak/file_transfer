/**
 * Author:  Burak Toprak
 **/

#include "stream.h"

// This class represents the server.
class Server {
    protected:
        SOCKET server_socket;
        string connection_type;
    public:
        Server(string);
        ~Server();
        bool start_listening();
        Stream* accept_connection();
};