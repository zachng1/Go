#include "gameclient.h"

GameClient::GameClient(int s, QWidget * parent) : GameOnline(s, parent)
{
    //client always starts as white
    setTurn(false);
}

void GameClient::connectHost(QString hostName, quint16 port) {
    QTcpSocket * sock = new QTcpSocket();
    sock->connectToHost(hostName, port);
    setSocket(sock);
    connect(socket(), &QAbstractSocket::connected,
            this, &GameClient::connection);
}

