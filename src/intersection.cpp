#include "intersection.h"
#include <QtWidgets>

Intersection::Intersection(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent) :
    QGraphicsEllipseItem(x, y, width, height, parent)
{
    pen.setStyle(Qt::SolidLine);
    pen.setBrush(Qt::black);
    pen.setWidth(2);
    setPen(pen);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(Qt::black);
    setBrush(brush);
}
