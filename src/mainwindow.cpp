#include "mainwindow.h"
#include <QtWidgets>
#include "board.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    QGraphicsScene * scene = new QGraphicsScene;
    QGraphicsView * view = new QGraphicsView(scene);
    Board * b = new Board(18);
    scene->addItem(b);
    setCentralWidget(view);
}
