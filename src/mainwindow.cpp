#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    board(new Board(19)),
    display(new QWidget),
    layout(new QGridLayout)
{
    for (int i = 0; i < board->size(); i++) {
        for (int j = 0; j < board->size(); j++) {
            layout->addWidget(new QPushButton("+"), j, i);
        }
    }

    layout->setHorizontalSpacing(0);
    layout->setVerticalSpacing(0);

    display->setLayout(layout);
    setCentralWidget(display);

}
