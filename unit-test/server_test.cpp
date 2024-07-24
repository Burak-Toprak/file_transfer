#include "gtest/gtest.h"
#include "server_connection.h"

#pragma comment (lib, "Ws2_32.lib")

TEST(ObserverTest, WriteTextFileConstructor) {

	WriteTextFile w("output.txt");
	EXPECT_TRUE(w.file);
}

TEST(ObserverTest, WriteBinaryFileConstructor) {

	WriteBinaryFile w("output");
	EXPECT_TRUE(w.file);
}

TEST(ObserverTest, CountDataConstructor) {

	CountData c;
	EXPECT_EQ(c.get_count(), 0);
}

TEST(ObserverTest, Process) {

	WritingStrategy* w_text = new WriteTextFile("output.txt");
	WritingStrategy* w_binary = new WriteBinaryFile("output");
	CountData c;
	string s("test");
	w_text->process(s, s.size());
	w_binary->process(s, s.size());
	c.process(s, s.size());
	EXPECT_EQ(s.size(), c.get_count());
	delete w_text;
	delete w_binary;

	ifstream text_stream("output.txt");
	ifstream binary_stream("output", ios::in | ios::binary);
	char buffer[1024];
	text_stream.read(buffer, 1024);
	EXPECT_EQ(s, string(buffer, text_stream.gcount()));
	binary_stream.read(buffer, 1024);
	EXPECT_EQ(s, string(buffer, binary_stream.gcount()));
	text_stream.close();
	binary_stream.close();
}

TEST(ReadingTest, ReadTextFileConstructor) {

	ofstream file("input.txt");
	file.close();
	ReadTextFile read_text_file("input.txt");
	EXPECT_TRUE(read_text_file.file);
}

TEST(ReadingTest, ReadBinaryFileConstructor) {

	ofstream file("input");
	file.close();
	ReadBinaryFile read_binary_file("input");
	EXPECT_TRUE(read_binary_file.file);
}

TEST(ReadingTest, ReadData) {

	ofstream text_stream("input.txt");
	ofstream binary_stream("input", ios::out | ios::binary);
	string s("test");
	text_stream.write(&s[0], s.size());
	binary_stream.write(&s[0], s.size());
	text_stream.close();
	binary_stream.close();

	ReadingStrategy* read_text_file = new ReadTextFile("input.txt");
	ReadingStrategy* read_binary_file = new ReadBinaryFile("input");
	EXPECT_EQ(s, read_text_file->read_data());
	EXPECT_EQ(s, read_binary_file->read_data());
	delete read_text_file;
	delete read_binary_file;
}

TEST(FileTransferTest, AddObserver) {
	WriteTextFile* write_text_file = new WriteTextFile("test_text");
	WriteBinaryFile* write_binary_file = new WriteBinaryFile("test_binary");
	CountData* count_data = new CountData;
	FileTransferProxy file_transfer;

	file_transfer.add_observer(write_text_file);
	file_transfer.add_observer(write_binary_file);
	file_transfer.add_observer(count_data);

	EXPECT_EQ(file_transfer.real_file_transfer->observers[0], write_text_file);
	EXPECT_EQ(file_transfer.real_file_transfer->observers[1], write_binary_file);
	EXPECT_EQ(file_transfer.real_file_transfer->observers[2], count_data);

	delete write_text_file;
	delete write_binary_file;
	delete count_data;
}


TEST(FileTransferTest, NotifyObservers) {
	WriteTextFile* write_text_file = new WriteTextFile("test.txt");
	WriteBinaryFile* write_binary_file = new WriteBinaryFile("test");
	CountData* count_data = new CountData;

	FileTransferProxy file_transfer;
	string s("test");

	file_transfer.add_observer(write_text_file);
	file_transfer.add_observer(write_binary_file);
	file_transfer.add_observer(count_data);
	file_transfer.notify_observers(s, s.size());

	EXPECT_EQ(s.size(), count_data->get_count());
	delete write_text_file;
	delete write_binary_file;
	delete count_data;

	ifstream text_stream("test.txt");
	ifstream binary_stream("test", ios::in | ios::binary);
	char buffer[1024];
	text_stream.read(buffer, 1024);
	EXPECT_EQ(s, string(buffer, text_stream.gcount()));
	binary_stream.read(buffer, 1024);
	EXPECT_EQ(s, string(buffer, binary_stream.gcount()));
	text_stream.close();
	binary_stream.close();
}

TEST(FileTransferTest, SetGetStrategy) {

	ofstream test("test.txt");
	test.close();
	ReadingStrategy* reading_strategy = new ReadTextFile("test.txt");
	FileTransferProxy file_transfer;
	file_transfer.set_strategy(reading_strategy);
	EXPECT_EQ(file_transfer.get_strategy(), reading_strategy);
	delete reading_strategy;
}

class StreamTestClass : public Stream {
public:
	using Stream::Stream;
	SOCKET get_socket_descriptor() {
		return socket_descriptor;
	}
	string get_connection_type() {
		return connection_type;
	}
};

TEST(StreamTest, TCPStreamConstructor) {

	SOCKET test_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	StreamTestClass tcp_stream(test_socket, "tcp");
	EXPECT_EQ(tcp_stream.get_socket_descriptor(), test_socket);
	EXPECT_EQ(tcp_stream.get_connection_type(), "tcp");
	EXPECT_TRUE(tcp_stream.file_transfer);
}

TEST(StreamTest, UDPStreamConstructor) {

	SOCKET test_socket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	StreamTestClass udp_stream(test_socket, "udp");
	EXPECT_EQ(udp_stream.get_socket_descriptor(), test_socket);
	EXPECT_EQ(udp_stream.get_connection_type(), "udp");
	EXPECT_TRUE(udp_stream.file_transfer);
}

class ServerTestClass : public Server {
public:
	using Server::Server;
	SOCKET get_server_socket() {
		return server_socket;
	}
	string get_connection_type() {
		return connection_type;
	}
};

TEST(ServerTest, TCPServerConstructor) {

	ServerTestClass tcp_server("tcp");
	EXPECT_NE(tcp_server.get_server_socket(), INVALID_SOCKET);
	EXPECT_EQ(tcp_server.get_connection_type(), "tcp");
}

TEST(ServerTest, UDPServerConstructor) {

	ServerTestClass udp_server("udp");
	EXPECT_NE(udp_server.get_server_socket(), INVALID_SOCKET);
	EXPECT_EQ(udp_server.get_connection_type(), "udp");
}

TEST(ServerTest, StartListening) {

	ServerTestClass tcp_server("tcp");
	EXPECT_TRUE(tcp_server.start_listening());
	ServerTestClass udp_server("udp");
	EXPECT_TRUE(udp_server.start_listening());
}

TEST(ServerTest, AcceptConnection) {

	ServerTestClass tcp_server("tcp");
	tcp_server.start_listening();
	SOCKET client_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	sockaddr_in client_address;
	client_address.sin_family = AF_INET;
	client_address.sin_addr.s_addr = inet_addr("127.0.0.1");
	client_address.sin_port = htons(55555);
	connect(client_socket, reinterpret_cast<SOCKADDR*>(&client_address), sizeof(client_address));
	Stream* tcp_stream{};
	tcp_stream = tcp_server.accept_connection();
	ASSERT_TRUE(tcp_stream);
	delete tcp_stream;
	closesocket(client_socket);
}

TEST(ServerConnectionTest, TCPFactoryCreateConnection) {

	ConnectionFactory* connection_factory = new TCPFactory;
	ConnectionStrategy* connection_strategy = connection_factory->create_connection();
	EXPECT_TRUE(connection_strategy);
	delete connection_strategy;
	delete connection_factory;
}

TEST(ServerConnectionTest, UDPFactoryCreateConnection) {

	ConnectionFactory* connection_factory = new UDPFactory;
	ConnectionStrategy* connection_strategy = connection_factory->create_connection();
	EXPECT_TRUE(connection_strategy);
	delete connection_strategy;
	delete connection_factory;
}

TEST(ServerConnectionTest, TCPConnectionCreateServer) {

	ConnectionFactory* connection_factory = new TCPFactory;
	ConnectionStrategy* connection_strategy = connection_factory->create_connection();
	Server* server = connection_strategy->create_server();
	EXPECT_TRUE(server);
	delete server;
	delete connection_strategy;
	delete connection_factory;
}

TEST(ServerConnectionTest, UDPConnectionCreateServer) {

	ConnectionFactory* connection_factory = new UDPFactory;
	ConnectionStrategy* connection_strategy = connection_factory->create_connection();
	Server* server = connection_strategy->create_server();
	EXPECT_TRUE(server);
	delete server;
	delete connection_strategy;
	delete connection_factory;
}