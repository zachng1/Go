#ifndef GAMEONLINE_H
#define GAMEONLINE_H

#include "game.h"
#include <QTcpSocket>


class GameOnline : public Game
{
    Q_OBJECT
public:
    GameOnline(int size, QWidget * parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    QTcpSocket * socket();
    void setSocket(QTcpSocket * socket);
    void setTurn(bool turn);

public slots:
    void socketEvent();
    void swapTurn(int COLOUR);
signals:

private:
    QTcpSocket * s;
    bool myturn;
    void sendMouseEvent(QMouseEvent * event);
};

#endif // GAMEONLINE_H
