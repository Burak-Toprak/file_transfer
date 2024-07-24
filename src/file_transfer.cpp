/**
 * Author:  Burak Toprak
 **/

#include <winsock2.h>
#include <iostream>
#include "file_transfer.h"

#pragma warning(disable:4996)

void RealFileTransfer::send_file(ReadingStrategy* strategy, SOCKET descriptor, string connection_type) {
    string buffer;
    if(connection_type == "tcp")
    {
        while(!strategy->file.eof())
        {
            buffer = strategy->read_data();
            if(send(descriptor, &buffer[0], buffer.size(), 0) == SOCKET_ERROR)
            {
                cout << "Send error" << endl;
                return;
            }
        }
    }
    else if(connection_type == "udp")
    {
        sockaddr_in other_address;
        other_address.sin_family = AF_INET;
        other_address.sin_addr.s_addr = inet_addr("127.0.0.1");
        other_address.sin_port = htons(55555);
        int address_len = sizeof(other_address);
        while(!strategy->file.eof())
        {
            buffer = strategy->read_data();
            if(sendto(descriptor, &buffer[0], buffer.size(), 0, (struct sockaddr*) &other_address, address_len) == SOCKET_ERROR)
            {
                cout << "Send error" << endl;
                return;
            }
        }
        buffer = "end_of_the_transfer";
        sendto(descriptor, &buffer[0], buffer.size(), 0, (struct sockaddr*) &other_address, address_len);
    }
    else
    {
        cout << "Connection type must be 'tcp' or 'udp'." << endl;
    }
    cout << "File transfer is done." << endl;
}

void RealFileTransfer::receive_file(SOCKET descriptor, string connection_type) {
    string buffer(1024, 0);
    int received_bytes;
    if(connection_type == "tcp")
    {
        while((received_bytes = recv(descriptor, &buffer[0], 1024, 0)) > 0)
        {
            notify_observers(buffer, received_bytes);
        }
    }
    else if(connection_type == "udp")
    {
        sockaddr_in other_address;
        other_address.sin_family = AF_INET;
        other_address.sin_addr.s_addr = inet_addr("127.0.0.1");
        other_address.sin_port = htons(55555);
        int address_len = sizeof(other_address);
        bind(descriptor, (struct sockaddr*) &other_address, address_len);
        while(1)
        {
            received_bytes = recvfrom(descriptor, &buffer[0], 1024, 0, (struct sockaddr*) &other_address, &address_len);
            if(buffer.substr(0, 19) == "end_of_the_transfer")
            {
                break;
            }
            notify_observers(buffer, received_bytes);
        }
    }
    else
    {
        cout << "Connection type must be 'tcp' or 'udp'." << endl;
    }
    cout << "File transfer is done." << endl;
}

void RealFileTransfer::add_observer(Observer* observer) {
    observers.push_back(observer);
}

void RealFileTransfer::notify_observers(string buffer, int buffer_size) {
    for(Observer* observer : observers)
    {
        observer->process(buffer, buffer_size);
    }
}

void RealFileTransfer::set_strategy(ReadingStrategy* in_strategy) {
    strategy = in_strategy;
}

ReadingStrategy* RealFileTransfer::get_strategy() {
    return strategy;
}

FileTransferProxy::~FileTransferProxy() {
    if(real_file_transfer != NULL)
    {
        delete real_file_transfer;
    }
}

void FileTransferProxy::send_file(ReadingStrategy* strategy, SOCKET descriptor, string connection_type) {
    if(real_file_transfer == NULL)
    {
        real_file_transfer = new RealFileTransfer;
    }
    real_file_transfer->send_file(strategy, descriptor, connection_type);
}

void FileTransferProxy::receive_file(SOCKET descriptor, string connection_type) {
    if(real_file_transfer == NULL)
    {
        real_file_transfer = new RealFileTransfer;
    }
    real_file_transfer->receive_file(descriptor, connection_type);
}

void FileTransferProxy::add_observer(Observer* observer) {
    if(real_file_transfer == NULL)
    {
        real_file_transfer = new RealFileTransfer;
    }
    real_file_transfer->add_observer(observer);
}

void FileTransferProxy::notify_observers(string buffer, int buffer_size) {
    if(real_file_transfer == NULL)
    {
        real_file_transfer = new RealFileTransfer;
    }
    real_file_transfer->notify_observers(buffer, buffer_size);
}

void FileTransferProxy::set_strategy(ReadingStrategy* in_strategy) {
    if(real_file_transfer == NULL)
    {
        real_file_transfer = new RealFileTransfer;
    }
    real_file_transfer->set_strategy(in_strategy);
}

ReadingStrategy* FileTransferProxy::get_strategy() {
    if(real_file_transfer == NULL)
    {
        real_file_transfer = new RealFileTransfer;
    }
    return real_file_transfer->get_strategy();
}