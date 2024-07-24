/**
 * Author:  Burak Toprak
 **/

#include <winsock2.h>
#include "reading.h"
#include "observer.h"
#include <vector>

// FileTransfer class is an abstract class representing the file transfer between server and client. Proxy design pattern is used to realize file transfer operations.
class FileTransfer {
    protected:
        FileTransfer() = default;
    public:
        friend class Stream;
        virtual ~FileTransfer() {};
        virtual void send_file(ReadingStrategy*, SOCKET, string) = 0;
        virtual void receive_file(SOCKET, string) = 0;
        virtual void add_observer(Observer*) = 0;
        virtual void notify_observers(string, int) = 0;
        virtual void set_strategy(ReadingStrategy*) = 0;
        virtual ReadingStrategy* get_strategy() = 0;
};

// RealFileTransfer class is the real part of the FileTransfer class in Proxy design pattern.
class RealFileTransfer : public FileTransfer {
    public:
        vector<Observer*> observers;
        ReadingStrategy* strategy;
        virtual ~RealFileTransfer() {};
        void send_file(ReadingStrategy*, SOCKET, string) override;
        void receive_file(SOCKET, string) override;
        void add_observer(Observer*) override;
        void notify_observers(string, int) override;
        void set_strategy(ReadingStrategy*) override;
        ReadingStrategy* get_strategy() override;
};

// FileTransferProxy class is the proxy part of the FileTransfer class in Proxy design pattern.
class FileTransferProxy : public FileTransfer {
    public:
        RealFileTransfer* real_file_transfer {};
        virtual ~FileTransferProxy();
        void send_file(ReadingStrategy*, SOCKET, string) override;
        void receive_file(SOCKET, string) override;
        void add_observer(Observer*) override;
        void notify_observers(string, int) override;
        void set_strategy(ReadingStrategy*) override;
        ReadingStrategy* get_strategy() override;
};