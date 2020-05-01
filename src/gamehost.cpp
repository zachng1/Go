#include "gamehost.h"

GameHost::GameHost(int s, QWidget * parent) : GameOnline(s, parent),
    server{new QTcpServer}
{
    connect(server, &QTcpServer::newConnection,
            this, &GameHost::clientJoin);
    //host always starts as black
    setTurn(true);
}

void GameHost::host() {
    server->listen();
    emit listening(server->serverAddress(), server->serverPort());
}

void GameHost::clientJoin() {
    if (socket() != nullptr) socket()->deleteLater();
    setSocket(server->nextPendingConnection());
    server->close();
    emit connection();
}
