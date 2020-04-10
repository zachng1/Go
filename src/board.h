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

    int placeStone(int COLOUR, int x, int y, bool hover=false);
    bool checkPosStatus(int COLOUR, int x, int y);
    bool posPermanent(int x, int y);
    int size();

    //implemented here bc other option was in intersection class
    //got messy when needing to access turn state



    std::vector<std::vector<Square *>> squares;
    std::vector<std::vector<Intersection *>> board;
    int s;
    QPen pen;
    QBrush brush;


};


#endif
