#ifndef XYINFO_H
#define XYINFO_H

#include <QWidget>
#include <QLabel>
#include <sstream>
#include <string>

class XYinfo : public QLabel
{
    Q_OBJECT
public:
    explicit XYinfo(QWidget *parent = nullptr);

public slots:
    void update(int x, int y);

signals:

private:
    QString text;
};

#endif // XYINFO_H
