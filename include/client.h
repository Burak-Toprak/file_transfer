/**
 * Author:  Burak Toprak
 **/

#include "stream.h"

// This class represents the client.
class Client {
    protected:
        SOCKET client_socket;
        string connection_type;
    public:
        Client(string);
        ~Client();
        Stream* create_stream();
};