#include "intersection.h"
#include "board.h"
#include <QtWidgets>

Intersection::Intersection(Qt::GlobalColor colour, qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent) :
    QGraphicsEllipseItem(x, y, width, height, parent),
    stone(nullptr),
    state(EMPTY)
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

int Intersection::Status() {
    return state;
}

void Intersection::setStatus(int COLOUR) {
    state = COLOUR;
    stone = new Stone(true, COLOUR, xpos-25, ypos-25, 50, 50, this);
}

void Intersection::givePosition(int x, int y) {
    xpos = x;
    ypos = y;
}

void Intersection::setCoords(int x, int y) {
    xcoord = x;
    ycoord = y;
}

void Intersection::hoverEnterEvent(QGraphicsSceneHoverEvent * event) {
    //fix up so COLOUR is transmitted via global turn
    if (stone == nullptr) {
        stone = new Stone(false, WHITE, xpos - 25, ypos - 25, 50, 50, this);
    }
}

void Intersection::hoverLeaveEvent(QGraphicsSceneHoverEvent * event) {
    if (!stone->Opacity()) {
        delete stone;
        stone = nullptr;
    }
}

void Intersection::mousePressEvent(QGraphicsSceneMouseEvent * event) {
    //sorry this is so yucky!!!
    ((Board *) parentItem())->placeStone(WHITE, xcoord, ycoord);
}

