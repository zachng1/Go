#include "turninfo.h"

TurnInfo::TurnInfo(QWidget * parent) : QLabel(parent),
    text("Black")
{
    setText(text);
}

void TurnInfo::update(int whosTurn) {
    std::ostringstream stringStream;
    if (whosTurn == BLACK) {
        stringStream << "Black";
    }
    else {
        stringStream << "White";
    }
    std::string string = stringStream.str();
    setText(QString::fromStdString(string));
}
