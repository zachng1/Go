#ifndef GAME_H
#define GAME_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsItem>
#include <QEvent>
#include <QPointF>
#include <vector>
#include <iostream>
#include <cmath>

#include "enum.h"
#include "board.h"


class Game : public QGraphicsView
{
    Q_OBJECT
public:
    Game(int s, QWidget * parent = nullptr);
    void mousePressEvent(QMouseEvent *event) override;
    void mouseMoveEvent(QMouseEvent *event) override;
    int whosTurn();

    int score(int COLOUR);
    void resize(int size);

public slots:
    void reset();

signals:
    int coords(int x, int y);
    int gameOver();
    int turnChange(int turn);


private:
    QGraphicsScene * scene;
    Board * board;
    std::vector<std::vector<bool>> helper;
    int turn;
    int pass;
    int s;
    //for keeping track of mouse position
    int hoverx;
    int hovery;

    int checkAlive(int GROUPCOLOUR, int x, int y);
    int removeGroup();
    void resetHelper();
};

#endif // GAME_H
