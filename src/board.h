#ifndef BOARD
#define BOARD

#include <vector>
#include <iostream>
#include <QGraphicsItem>
#include "square.h"
#include "intersection.h"
#include "enum.h"

class Board : public QGraphicsRectItem {
    public:
    Board(int s);
    ~Board();


    int placeStone(int COLOUR, int x, int y);
    int checkAlive(int GROUPCOLOUR, int x, int y);
    int removeGroup();
    bool checkPosStatus(int COLOUR, int x, int y);
    int size();

    private:
    std::vector<std::vector<Square *>> squares;
    std::vector<std::vector<Intersection *>> board;
    std::vector<std::vector<bool>> helper;
    int s;
    QPen pen;
    QBrush brush;

    void resetHelper();

};


#endif
