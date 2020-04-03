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

    setAcceptHoverEvents(true);
    setAcceptedMouseButtons(Qt::LeftButton);
}

int Intersection::status() {
    return state;
}

bool Intersection::permanent() {
    return hoverstate;
}

void Intersection::setStatus(int COLOUR, bool permanent) {
    state = COLOUR;
    hoverstate = permanent;
    if (COLOUR != EMPTY) {
        stone = new Stone(permanent, COLOUR, -25, -25, 50, 50, this);
    }
    else if (COLOUR == EMPTY) {
        delete stone;
        stone = nullptr;
    }
}

