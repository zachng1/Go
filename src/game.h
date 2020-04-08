#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include "board.h"
#include "enum.h"


class Game : public QGraphicsView
{
public:
    Game(int s, QWidget * parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;

    int getXCoord();
    int getYCoord();
    int passes();
    int bscore();
    int wscore();


private:
    QGraphicsScene * scene;
    Board * b;
    int pass;
};

#endif // GAME_H
