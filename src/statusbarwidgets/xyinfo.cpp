#include "xyinfo.h"

XYinfo::XYinfo(QWidget *parent) : QLabel(parent),
    text("0, 0")
{
    setText(text);
}

void XYinfo::update(int x, int y) {
    std::ostringstream stringStream;
    stringStream << x << ',' << y;
    std::string string = stringStream.str();
    setText(QString::fromStdString(string));
}
