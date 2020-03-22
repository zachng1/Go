#include "square.h"
#include <QtWidgets>

Square::Square(QGraphicsItem * parent) : QGraphicsItem(parent)
{
    setRect(0, 0, 100, 100);
    QPen pen();
    pen.setStyle(Qt::SolidLine);
    pen.setBrush(Qt::black);
    pen.setWidth(2);
    setPen(pen);
    brush.setStyle(Qt::SolidPattern);
    brush.setColor(QColor::fromRgb(220, 179, 92);
    setBrush(brush);
}
