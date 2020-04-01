#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include "stone.h"
#include <iostream>


class Intersection : public QGraphicsEllipseItem
{
public:
    Intersection(Qt::GlobalColor, qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = nullptr);
    int status();
    void setStatus(int COLOUR, bool permanent);

private:
    QPen pen;
    QBrush brush;
    Stone * stone;
    int state;


};

#endif // INTERSECTION_H
