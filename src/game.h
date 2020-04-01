#ifndef GAME_H
#define GAME_H

#include <QGraphicsScene>
#include <QEvent>
#include <QGraphicsSceneHoverEvent>
#include "board.h"
#include "enum.h"


class Game : public QGraphicsScene
{
public:
    Game(QObject * parent = nullptr);


private:
    Board * b;
};

#endif // GAME_H
