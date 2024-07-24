/**
 * Author:  Burak Toprak
 **/

#include "file_transfer.h"

class Stream {
    protected:
        SOCKET socket_descriptor;
        string connection_type;
    public:
        Stream(SOCKET, string);
        ~Stream();
        friend class Server;
        friend class Client;
        FileTransfer* file_transfer;
        void send_file(ReadingStrategy*);
        void receive_file();
};