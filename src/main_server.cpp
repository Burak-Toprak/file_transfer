/**
 * Author:  Burak Toprak
 **/

#include <iostream>
#include "server_connection.h"

#pragma comment(lib, "Ws2_32.lib")

int main(int argc, char* argv[]) {
	cout << "Server Program" << endl;
	if(argc != 4)
	{
		cout << "Usage:  server <filename> <direction ('u' for upload, 'd' for download)> <protocol ('tcp' or 'udp')> " << endl;
		return 1;
	}
	string file_name(argv[1]);
	string file_extension(file_name.substr(file_name.length() - 3));
	string direction(argv[2]);
	string connection_type(argv[3]);
	ConnectionFactory* connection_factory;
	if(connection_type == "tcp")
	{
		connection_factory = new TCPFactory;
	}
	else if(connection_type == "udp")
	{
		connection_factory = new UDPFactory;
	}
	else
	{
        cout << "Connection type must be 'tcp' or 'udp'." << endl;
		return 1;
	}
	ConnectionStrategy* connection_strategy = connection_factory->create_connection();
	Server* server = connection_strategy->create_server();
	Stream* stream = NULL;
	if(direction == "u")
	{
		WritingStrategy* writing_strategy;
		CountData count_data;
		if(file_extension == "txt")
		{
			writing_strategy = new WriteTextFile(file_name);
		}
		else
		{
			writing_strategy = new WriteBinaryFile(file_name);
		}
		if(server->start_listening())
		{
			stream = server->accept_connection();
			if(stream != NULL)
			{
				stream->file_transfer->add_observer(writing_strategy);
				stream->file_transfer->add_observer(&count_data);
				stream->receive_file();
				cout << count_data.get_count() << " bytes of data are received." << endl;
				delete stream;
			}
		}
		delete writing_strategy;
	}
	else if(direction == "d")
	{
		if(server->start_listening())
		{
			stream = server->accept_connection();		
			if(stream != NULL)
			{
				ReadingStrategy* reading_strategy;
				if(file_extension == "txt")
				{
					reading_strategy = new ReadTextFile(file_name);
				}
				else
				{
					reading_strategy = new ReadBinaryFile(file_name);
				}
				stream->file_transfer->set_strategy(reading_strategy);
				if(stream != NULL)
				{
					stream->send_file(stream->file_transfer->get_strategy());
					delete stream;
				}
				delete reading_strategy;
			}
		}
	}
	else
	{
        cout << "Direction must be 'u' (upload) or 'd' (download)." << endl;
	}
	delete server;
	delete connection_strategy;
	delete connection_factory;
	return 0;
}