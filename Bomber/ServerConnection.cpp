#include "stdafx.h"
#include "ServerConnection.h"

//Online part left for now, todo later 

using namespace std;

mutex consoleMutex;

void readFromServer(sf::TcpSocket* socket) {
    try {
        while (true) {
            char buffer[1024];
            std::size_t received;
            if (socket->receive(buffer, sizeof(buffer), received) == sf::Socket::Done) {
                lock_guard<mutex> lock(consoleMutex);
                cout << string(buffer, received) << endl;
            }
        }
    }
    catch (std::exception& e) 
    {
        cerr << "Error: " << e.what() << std::endl;
    }
}

void writeToServer(sf::TcpSocket* socket) {
    try {
        while (true) {
            string message;
            getline(cin, message);

            if (message == "quit") {
                break;
            }

            if (socket->send(message.c_str(), message.size() + 1) != sf::Socket::Done) {
                cerr << "Error sending a message" << std::endl;
                break;
            }
        }
    }
    catch (std::exception& e) {
        cerr << "Error sending a message: " << e.what() << std::endl;
    }
}

void startClient(sf::TcpSocket* socket) {
    thread readThread(readFromServer, socket);
    thread writeThread(writeToServer, socket);

    readThread.join();
    writeThread.join();
}

int ConnectWithServer() {
    try {
        cout << "Bomber - communication test v2" << endl;

        sf::TcpSocket socket;
        sf::IpAddress serverAddress;
        unsigned short serverPort;

        cout << "Server adress: ";
        cin >> serverAddress;
        cout << "Port number: ";
        cin >> serverPort;

        if (socket.connect(serverAddress, serverPort) != sf::Socket::Done) {
            cerr << "COULDNT CONNECT" << endl;
            return 1;
        }

        startClient(&socket);
    }
    catch (std::exception& e) {
        cerr << "Error: " << e.what() << endl;
    }

    return 0;
}