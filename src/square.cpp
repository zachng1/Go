#include "square.h"
#include <QtWidgets>

Square::Square(qreal x,
               qreal y,
               qreal width,
               qreal height,
               QGraphicsItem * parent) :
    QGraphicsRectItem(x, y, width + 1, height + 1 ,parent),
    status(EMPTY)
{
    pen.setStyle(Qt::SolidLine);
    pen.setBrush(Qt::black);
    pen.setWidth(2);
    setPen(pen);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(220, 179, 92));
    setBrush(brush);
}
