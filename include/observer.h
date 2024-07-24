/**
 * Author:  Burak Toprak
 **/

#include <fstream>
#include <string>

using namespace std;

// Observer class represents an observer. Observer design pattern is used to write the received data into a file and to count the received bytes.
class Observer {
    public:
        virtual ~Observer() {};
        virtual void process(string, int) = 0;
};

// WritingStrategy is one of the observers and writes data into a file. Strategy design pattern is used to create the file as a text file or a binary file.
class WritingStrategy : public Observer {
    protected:
        WritingStrategy(string, ios_base::openmode = ios_base::out);
    public:        
        ~WritingStrategy();
        ofstream file;
        void process(string, int) override;
};

// If the file is a text file, WriteTextFile object is created.
class WriteTextFile : public WritingStrategy {
    public:
        WriteTextFile(string);
};

// If the file is a binary file, WriteBinaryFile object is created.
class WriteBinaryFile : public WritingStrategy {
    public:
        WriteBinaryFile(string);
};

// CountData is the other observer and counts the received bytes.
class CountData : public Observer {
    private:
        int count {};
    public:
        int get_count();
        void process(string, int) override;
};