#include "gameclient.h"

GameClient::GameClient(int s, QWidget * parent) : GameOnline(s, parent)
{
    //client always starts as white
    setTurn(false);
}

void GameClient::connectHost(QHostAddress hostName, quint16 port) {
    QTcpSocket * sock = new QTcpSocket();
    sock->connectToHost(hostName, port);
    setSocket(sock);
    connect(socket(), &QAbstractSocket::connected,
            this, &GameClient::connection);
    //connect(socket(), &QAbstractSocket::connected,
    //        this, &GameClient::recieveSize);
}

/*void GameClient::recieveSize() {
    socket()->waitForReadyRead(10000);
    QByteArray arr = socket()->read(64);
    resize(arr.toInt());
    qDebug() << arr.toInt();
}*/

