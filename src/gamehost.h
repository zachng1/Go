#ifndef GAMEHOST_H
#define GAMEHOST_H

#include "gameonline.h"
#include <QObject>
#include <QTcpServer>
#include <QTcpSocket>
#include <QDataStream>

class GameHost : public GameOnline
{
    Q_OBJECT
public:
    GameHost(int s, QWidget * parent = nullptr);
public slots:
    void host();
    void clientJoin();
signals:
    void connection();
    void listening(QHostAddress address, quint16 port);

private:
    QTcpServer * server;
};

#endif // GAMEHOST_H
