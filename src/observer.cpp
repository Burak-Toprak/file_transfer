/**
 * Author:  Burak Toprak
 **/

#include <iostream>
#include "observer.h"

WritingStrategy::WritingStrategy(string file_name, ios_base::openmode mode) : file(file_name, mode) {
    if(!file)
    {
        cout << "Output file opening error" << endl;
    }
}

WritingStrategy::~WritingStrategy() {
    file.close();
}

void WritingStrategy::process(string buffer, int buffer_size) {
    file.write(&buffer[0], buffer_size);
}

WriteTextFile::WriteTextFile(string file_name) : WritingStrategy(file_name)
{}

WriteBinaryFile::WriteBinaryFile(string file_name) : WritingStrategy(file_name, ios::out | ios::binary)
{}

int CountData::get_count() {
    return count;
}

void CountData::process(string buffer, int buffer_size) {
    count += buffer_size;
}