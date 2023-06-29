#ifndef SERVERCONNECTION_H
#define SERVERCONNECTION_H

#include "stdafx.h"

extern std::mutex consoleMutex;

void readFromServer(sf::TcpSocket* socket);
void writeToServer(sf::TcpSocket* socket);
void startClient(sf::TcpSocket* socket);
int ConnectWithServer();

#endif // SERVERCONNECTION_H