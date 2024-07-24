/**
 * Author:  Burak Toprak
 **/

#include <iostream>
#include "reading.h"

ReadingStrategy::ReadingStrategy(string file_name, ios_base::openmode mode) : file(file_name, mode) {
    if(!file)
    {
        cout << "Input file opening error" << endl;
    }
}

ReadingStrategy::~ReadingStrategy() {
    file.close();
}

string ReadingStrategy::read_data() {
    char buffer[1024];
    file.read(buffer, 1024);
    return string(buffer, file.gcount());
}

ReadTextFile::ReadTextFile(string file_name) : ReadingStrategy(file_name)
{}

ReadBinaryFile::ReadBinaryFile(string file_name) : ReadingStrategy(file_name, ios::in | ios::binary)
{}