#ifndef SQUARE_H
#define SQUARE_H

#include <QGraphicsRectItem>
#include <QBrush>
#include <QPen>

class Square : public QGraphicsRectItem
{
    Q_OBJECT
public:
    explicit Square(QGraphicsItem * parent=nullptr);

signals:

public slots:

private:
    QBrush brush;
    QPen pen;
};

#endif // SQUARE_H
