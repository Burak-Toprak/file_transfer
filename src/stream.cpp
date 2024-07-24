/**
 * Author:  Burak Toprak
 **/

#include <iostream>
#include "stream.h"

Stream::Stream(SOCKET descriptor, string in_connection_type) 
:socket_descriptor(descriptor), connection_type(in_connection_type), file_transfer(new FileTransferProxy)
{}

Stream::~Stream() {
    closesocket(socket_descriptor);
    delete file_transfer;
}

void Stream::send_file(ReadingStrategy* reading_strategy) {
    file_transfer->send_file(reading_strategy, socket_descriptor, connection_type);
}

void Stream::receive_file() {
    file_transfer->receive_file(socket_descriptor, connection_type);
}