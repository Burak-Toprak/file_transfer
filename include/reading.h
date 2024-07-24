/**
 * Author:  Burak Toprak
 **/
 
#include <fstream>
#include <string>

using namespace std;

// ReadingStrategy reads data from a file. Strategy design pattern is used to open the file as a text file or a binary file.
class ReadingStrategy {
    protected:
        ReadingStrategy(string, ios_base::openmode = ios_base::in);
    public:
        ~ReadingStrategy();
        ifstream file;
        string read_data();
};

// If the file is a text file, ReadTextFile object is created.
class ReadTextFile : public ReadingStrategy {
    public:
        ReadTextFile(string);
};

// If the file is a text file, ReadBinaryFile object is created.
class ReadBinaryFile : public ReadingStrategy {
    public:
        ReadBinaryFile(string);
};