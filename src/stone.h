#ifndef STONE_H
#define STONE_H

#include <QGraphicsEllipseItem>
#include <QPen>
#include <QBrush>
#include "enum.h"

class Stone : public QGraphicsEllipseItem
{
public:
    Stone(bool opaque, int COLOUR, qreal x, qreal y, qreal width, qreal height, QGraphicsItem * parent = nullptr);
    bool Opacity();

private:
    QPen pen;
    QBrush brush;
    bool opacity;
};

#endif // STONE_H
