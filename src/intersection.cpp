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

int Intersection::status() {
    return state;
}

void Intersection::setStatus(int COLOUR, bool permanent) {
    state = COLOUR;
    std::cout << pos().x() << pos().y() << std::endl;
    if (COLOUR != EMPTY) {
        stone = new Stone(permanent, COLOUR, -25, -25, 50, 50, this);
        //stone->setPos(pos().x(), pos().y());
        std::cout << "set" << std::endl;
    }
    else {
        std::cout << "Delete action" << std::endl;
        delete stone;
    }
}

