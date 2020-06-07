#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include <QHostAddress>
#include "gameonline.h"

class GameClient : public GameOnline
{
    Q_OBJECT
public:
    GameClient(int s, QWidget * parent = nullptr);
    void connectHost(QHostAddress hostName, quint16 port);

public slots:
    //void recieveSize();

signals:
    void connection();
};

#endif // GAMECLIENT_H
