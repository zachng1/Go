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
    if (server->listen()) {
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        QHostAddress a = localhost;
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
                a = address;
            }
        }
        emit listening(a, server->serverPort());
    }
    else printf("Error listening");
}

void GameHost::clientJoin() {
    if (socket() != nullptr) socket()->deleteLater();
    setSocket(server->nextPendingConnection());
    server->close();
    emit connection();
}
