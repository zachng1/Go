#include "mainwindow.h"
#include <QtWidgets>
#include "game.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent) {
    Game * game = new Game;
    QGraphicsView * view = new QGraphicsView(game);
    setCentralWidget(view);
}
