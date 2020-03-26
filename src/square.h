#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>
#include "enum.h"

class Square : public QGraphicsRectItem
{
public:
    explicit Square(qreal x,
                    qreal y,
                    qreal width,
                    qreal height,
                    QGraphicsItem * parent=nullptr);

private:
    QBrush brush;
    QPen pen;
    int status;
    friend class Board;
};

#endif // SQUARE_H
