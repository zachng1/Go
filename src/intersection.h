#ifndef INTERSECTION_H
#define INTERSECTION_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>


class Intersection : public QGraphicsEllipseItem
{
public:
    Intersection(qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = nullptr);

private:
    QPen pen;
    QBrush brush;
    int status;
    friend class Board;
};

#endif // INTERSECTION_H
