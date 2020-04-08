#ifndef BOARD
#define BOARD

#include <vector>
#include <iostream>
#include <QGraphicsItem>
#include "square.h"
#include "intersection.h"
#include "enum.h"
#include <QEvent>
#include <QGraphicsSceneHoverEvent>
#include <QGraphicsSceneMouseEvent>
#include <QPointF>

class Board : public QGraphicsRectItem {
    public:
    Board(int s);
    ~Board();

    int bscore();
    int wscore();
    private:
    void hoverStone(int COLOUR, int x, int y);
    void removeHoverStone(int x, int y);
    int placeStone(int COLOUR, int x, int y);
    int checkAlive(int GROUPCOLOUR, int x, int y);
    int removeGroup();
    bool checkPosStatus(int COLOUR, int x, int y);
    int size();

    //implemented here bc other option was in intersection class
    //got messy when needing to access turn state
    void hoverMoveEvent(QGraphicsSceneHoverEvent *event) override;
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    int whosTurn();


    std::vector<std::vector<Square *>> squares;
    std::vector<std::vector<Intersection *>> board;
    std::vector<std::vector<bool>> helper;
    int s;
    int turn;
    QPen pen;
    QBrush brush;

    //for keeping track of mouse position
    int hoverx;
    int hovery;

    void resetHelper();

};


#endif
