#include "stone.h"
#include <QtWidgets>

Stone::Stone(bool opaque, int COLOUR, qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent) :
        QGraphicsEllipseItem(x, y, width, height, parent),
        opacity(opaque)
    {
    if (COLOUR == BLACK) {
        pen.setStyle(Qt::SolidLine);
        pen.setBrush(Qt::black);
        pen.setWidth(2);
        setPen(pen);
        brush.setStyle(opaque ? Qt::SolidPattern : Qt::Dense4Pattern);
        brush.setColor(Qt::black);
        setBrush(brush);
    }
    else {
        pen.setStyle(Qt::SolidLine);
        pen.setBrush(Qt::white);
        pen.setWidth(2);
        setPen(pen);
        brush.setStyle(opaque ? Qt::SolidPattern : Qt::Dense4Pattern);
        brush.setColor(Qt::white);
        setBrush(brush);
    }
}

bool Stone::Opacity() {
    return opacity;
}
