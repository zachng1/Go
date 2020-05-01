#include "gameonline.h"

GameOnline::GameOnline(int size, QWidget * parent) : Game(size, parent),
    s{nullptr},
    myturn{true}
{
    setMouseTracking(true);
    connect(s, &QIODevice::readyRead,
            this, &GameOnline::socketEvent);
}

QTcpSocket * GameOnline::socket() {
    return s;
}

void GameOnline::setSocket(QTcpSocket * socket) {
    s = socket;
}

void GameOnline::setTurn(bool turn) {
    myturn = turn;
}


void GameOnline::socketEvent() {
    QDataStream socketdstream(s);
    socketdstream.setVersion(QDataStream::Qt_5_14);
    socketdstream.startTransaction();
    QEvent::Type type;
    QPointF localPos;
    Qt::MouseButton button;
    Qt::MouseButtons buttons;
    Qt::KeyboardModifiers modifiers;
    socketdstream >>
            type >>
            localPos >>
            button >>
            buttons >>
            modifiers;
    if (!socketdstream.commitTransaction()) return;
    else {
        Game::mousePressEvent(new QMouseEvent(type, localPos, button, buttons, modifiers));
        myturn = !myturn;
    }

}

void GameOnline::mousePressEvent(QMouseEvent * event) {
    if (myturn) {
        sendMouseEvent(event);
        Game::mousePressEvent(event);
        myturn = !myturn;
    }
}

void GameOnline::mouseMoveEvent(QMouseEvent *event) {
    if (myturn) {
        Game::mouseMoveEvent(event);
    }
}

void GameOnline::sendMouseEvent(QMouseEvent *event) {
    QByteArray buffer;
    QDataStream bufferdstream(&buffer, QIODevice::WriteOnly);
    bufferdstream.setVersion(QDataStream::Qt_5_14);
    bufferdstream <<
                     event->type() <<
                     event->localPos() <<
                     event->button() <<
                     event->buttons() <<
                     event->modifiers();

    QDataStream socketdstream(s);
    socketdstream.setVersion(QDataStream::Qt_5_14);
    socketdstream << bufferdstream;
}
