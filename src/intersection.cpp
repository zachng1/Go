#include "intersection.h"
#include "board.h"
#include <QtWidgets>

Intersection::Intersection(Qt::GlobalColor colour, qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent) :
    QGraphicsEllipseItem(x, y, width, height, parent),
    stone(nullptr),
    state(EMPTY),
    hoverstate(false)
{

    pen.setStyle(Qt::SolidLine);
    pen.setBrush(Qt::transparent);
    pen.setWidth(2);
    setPen(pen);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(colour);
    setBrush(brush);
}

int Intersection::status() {
    return state;
}

bool Intersection::permanent() {
    return hoverstate;
}

void Intersection::setStatus(int COLOUR, bool permanent) {
    if (stone != nullptr) delete stone;
    hoverstate = permanent;

    if (COLOUR != EMPTY && permanent) {
        state = COLOUR;
        stone = new Stone(true, COLOUR, -25, -25, 50, 50, this);
    }
    else if (COLOUR != EMPTY && !permanent) {
        stone = new Stone(false, COLOUR, -25, -25, 50, 50, this);
    }
    else if (COLOUR == EMPTY) {
        state = COLOUR;
        stone = nullptr;
    }
}

