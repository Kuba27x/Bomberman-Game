#include "stdafx.h"
#include "ServerConnection.h"

//Online aspect left for now todo later 

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
        cerr << "Blad podczas odczytu z serwera: " << e.what() << std::endl;
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
                cerr << "Blad podczas wysylania wiadomosci" << std::endl;
                break;
            }
        }
    }
    catch (std::exception& e) {
        cerr << "Blad podczas wysylania wiadomosci: " << e.what() << std::endl;
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
        cout << "Bombit - test komunikacji v2" << endl;

        sf::TcpSocket socket;
        sf::IpAddress serverAddress;
        unsigned short serverPort;

        cout << "Podaj adres serwera: ";
        cin >> serverAddress;
        cout << "Podaj numer portu: ";
        cin >> serverPort;

        if (socket.connect(serverAddress, serverPort) != sf::Socket::Done) {
            cerr << "Nie udalo sie polaczyc z serwerem" << endl;
            return 1;
        }

        startClient(&socket);
    }
    catch (std::exception& e) {
        cerr << "Blad: " << e.what() << endl;
    }

    return 0;
}