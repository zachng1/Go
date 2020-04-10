#ifndef TURNINFO_H
#define TURNINFO_H

#include <QLabel>
#include <QString>
#include <sstream>
#include <string>
#include "../enum.h"

class TurnInfo: public QLabel
{
    Q_OBJECT
public:
    TurnInfo(QWidget * parent=nullptr);

public slots:
    void update(int whosTurn);

private:
    QString text;
};

#endif // TURNINFO_H
