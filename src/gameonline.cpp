#include "gameonline.h"

GameOnline::GameOnline(int size, QWidget * parent) : Game(size, parent),
    s{nullptr},
    myturn{true}
{
    setMouseTracking(true);
    connect(this, &Game::turnChange, this, &GameOnline::swapTurn);
}

QTcpSocket * GameOnline::socket() {
    return s;
}

void GameOnline::setSocket(QTcpSocket * socket) {
    if (s != nullptr) s->deleteLater();
    s = socket;
    connect(s, &QIODevice::readyRead,
            this, &GameOnline::socketEvent);
}

void GameOnline::setTurn(bool turn) {
    myturn = turn;
}

//takes COLOUR arg so can connect to
//Game::turnChange
void GameOnline::swapTurn(int COLOUR) {
    //qDebug() << "turn change";
    myturn = !myturn;
}


void GameOnline::socketEvent() {
    QDataStream socketdstream(s);
    socketdstream.setVersion(QDataStream::Qt_5_14);

    //this whole thing needs a makeover jesus christ
    //but it works??!
    socketdstream.startTransaction();
    quint32 bufsize;
    QEvent::Type type;
    QPointF localPos;
    Qt::MouseButton button;
    Qt::MouseButtons buttons;
    Qt::KeyboardModifiers modifiers;
    socketdstream >> bufsize >>
            type >>
            localPos >>
            button >>
            buttons >>
            modifiers;
    //qDebug() << "Ready read";
    if (!socketdstream.commitTransaction()) return;
    else {
        Game::mousePressEvent(new QMouseEvent(type, localPos, button, buttons, modifiers));
        //qDebug() << "Receive:" << type << localPos << button << buttons << modifiers;
    }
}

void GameOnline::mousePressEvent(QMouseEvent * event) {
    if (myturn) {
        sendMouseEvent(event);
        Game::mousePressEvent(event);
    }
}

void GameOnline::mouseMoveEvent(QMouseEvent *event) {
    if (myturn) {
        Game::mouseMoveEvent(event);
    }
}

void GameOnline::sendMouseEvent(QMouseEvent *event) {

    //this also needs a fucking makeoverlol
    //but hey
    QByteArray buffer;
    QDataStream bufferdstream(&buffer, QIODevice::ReadWrite);
    bufferdstream.setVersion(QDataStream::Qt_5_14);
    bufferdstream <<
                     event->type() <<
                     event->localPos() <<
                     event->button() <<
                     event->buttons() <<
                     event->modifiers();
    QDataStream socketdstream(s);
    socketdstream.setVersion(QDataStream::Qt_5_14);
    socketdstream << buffer;
    //qDebug() << "Send:" << QString(buffer);
    //qDebug() << event->type() << event->localPos();
}
