#ifndef GAMECLIENT_H
#define GAMECLIENT_H

#include "gameonline.h"

class GameClient : public GameOnline
{
    Q_OBJECT
public:
    GameClient(int s, QWidget * parent = nullptr);
    void connectHost(QString hostName, quint16 port);
signals:
    void connection();
};

#endif // GAMECLIENT_H
