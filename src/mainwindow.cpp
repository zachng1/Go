#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    game(new Game)
{
    view = new QGraphicsView(game);
    setCentralWidget(view);
    setStatusBar(new QStatusBar);
    setMenuBar(new QMenuBar);
}
