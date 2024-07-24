## Introduction

This repository contains the project I have completed during my internship at Turkish Aerospace Industries. In this period the project was supervised by Ugur Melih Surme [@ugurmelihsurme](https://github.com/ugurmelihsurme).

## Overview

In this project, I developed server and client programs in C++ which are performing two-way file transfer between them. After completing the implementation, I wrote unit test for the software using the Google Test framework. Finally, I created the CMake structure to provide a more convenient building mechanism.

### - Server-Client:

In the implementation of the server and client programs, some design patterns are used. For reading and writing of the text and binary files, the strategy design pattern is applied. Additionally, the communication protocol (TCP or UDP) specifies the type of connection (TCPConnection or UDPConnection) using the strategy pattern. The creation of connection objects is done by the factory classes that utilize Factory Method design pattern, while files are transferred by objects that exhibit the Proxy design pattern.

### - Unit Test:

Unit testing of the source code is handled by the [Google Test](https://github.com/google/googletest) framework. Almost all methods of the software are tested in isolation in an automated manner.

### - CMake:

[CMake](https://cmake.org/) is used for building the programs and the tests.

## How To Build And Run

To build the programs and tests, you can use CMake.

### - Server-Client:

To build the server and client programs, you can use the given batch file `build.bat`. It builds the programs using CMake and creates two directories named as _server_ and _client_ containing the executables of server and client, respectively. Then,

* To run the server program, use `server <filename> <direction ('u' for upload, 'd' for download)> <protocol ('tcp' or 'udp')>` command in the _server_ directory or run given batch file `run_server.bat` after setting the command line arguments in the file properly.

* To run the client program, use `client <filename> <direction ('u' for upload, 'd' for download)> <protocol ('tcp' or 'udp')>` command in the _client_ directory or run given batch file `run_client.bat` after setting the command line arguments in the file properly.

**Make sure that the command line arguments given to server and client programs are same.**

The given batch files  `run_server.bat` and `run_client.bat` transfers a pdf file named as `a.pdf` from server to client using TCP protocol. Make sure that the input file is in the same directory with server program for download operations and client program for upload operations.

### - Unit Test:

To build the test, you can use the given batch file `build_test.bat` which is in the _unit-test_ directory. It builds the tests for server and client using CMake and creates two directories named as _server_ and _client_ containing the test executables of server and client, respectively. Then,

* To run the server test, use `server_test` command in the _server_ directory under _unit-test_ or run given batch file `run_server_test.bat`.

* To run the client test, use `client_test` command in the _client_ directory under _unit-test_ or run given batch file `run_client_test.bat`.