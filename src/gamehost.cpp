#include "gamehost.h"

GameHost::GameHost(int s, QWidget * parent) : GameOnline(s, parent),
    server{new QTcpServer}
{
    connect(server, &QTcpServer::newConnection,
            this, &GameHost::clientJoin);
    //connect(this, &GameHost::connection,
      //      this, &GameHost::sendSize);
    //host always starts as black
    setTurn(true);
}

int GameHost::host() {
    if (server->listen()) {
        const QHostAddress &localhost = QHostAddress(QHostAddress::LocalHost);
        QHostAddress a = localhost;
        for (const QHostAddress &address: QNetworkInterface::allAddresses()) {
            if (address.protocol() == QAbstractSocket::IPv4Protocol && address != localhost) {
                a = address;
            }
        }
        emit listening(a, server->serverPort());
        return 0;
    }
    return -1;
}

void GameHost::clientJoin() {
    if (socket() != nullptr) socket()->deleteLater();
    setSocket(server->nextPendingConnection());
    server->close();
    emit connection();
}

/*void GameHost::sendSize() {
   QByteArray arr;
   arr.setNum(size());
   socket()->write(arr);
   qDebug() << arr;
}*/
