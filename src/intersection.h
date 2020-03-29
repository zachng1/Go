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
    int Status();
    void setStatus(int COLOUR);
    void givePosition(int x, int y);
    void setCoords(int x, int y);

    void hoverEnterEvent(QGraphicsSceneHoverEvent * event);
    void hoverLeaveEvent(QGraphicsSceneHoverEvent * event);
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

private:
    QPen pen;
    QBrush brush;
    Stone * stone;
    int state;
    int xpos;
    int ypos;
    int xcoord;
    int ycoord;

};

#endif // INTERSECTION_H
