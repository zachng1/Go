#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    game(new Game(18, this)),
    size(18),
    gameover(new GameOverBox(this))
{
    setCentralWidget(game);

    setupMenu();
    setupStatusBar();
    connect(game, &Game::gameOver, this, &MainWindow::score);
    connect(gameover, &GameOverBox::closed, game, &Game::reset);

}



void MainWindow::setupMenu() {
    //new pointer to game for lambdas.
    QMenu * gameMenu = menuBar()->addMenu("Game");

    QAction * reset = new QAction("Restart");
    connect(reset, &QAction::triggered, game, &Game::reset);
    gameMenu->addAction(reset);

    QMenu * changeSize = new QMenu("Choose Size");

    QAction * nineteen = new QAction("19");
    connect(nineteen, &QAction::triggered, this,
            [&](){this->game->resize(18);});
    changeSize->addAction(nineteen);

    QAction * thirteen = new QAction("13");
    connect(thirteen, &QAction::triggered, this,
            [&](){this->game->resize(12);});
    changeSize->addAction(thirteen);

    QAction * nine = new QAction("9");
    connect(nine, &QAction::triggered, this,
            [&](){this->game->resize(8);});
    changeSize->addAction(nine);

    gameMenu->addMenu(changeSize);
}

void MainWindow::setupStatusBar(){

    QStatusBar * statusbar = statusBar();

    XYinfo * xy = new XYinfo;
    statusbar->addPermanentWidget(xy);
    connect(game, &Game::coords, xy, &XYinfo::update);

    TurnInfo * turn = new TurnInfo;
    statusbar->addPermanentWidget(turn);
    connect(game, &Game::turnChange, turn, &TurnInfo::update);
}

void MainWindow::score() {
    int black = game->score(BLACK);
    int white = game->score(WHITE);
    gameover->show(black, white);
}
