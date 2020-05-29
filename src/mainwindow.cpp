#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    game(new Game(18, this)),
    size(18),
    gameover(new GameOverBox(this)),
    jd{new JoinDialog},
    hd{new HostDialog}
{
    setCentralWidget(game);
    //game->fitInView(game->sceneRect(), Qt::KeepAspectRatio);

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

    //now online stuff

    QMenu * onlineMenu = menuBar()->addMenu("Online");
    join = new QAction("Join Game");
    connect(join, &QAction::triggered, this, &MainWindow::clientJoin);
    onlineMenu->addAction(join);

    host = new QAction("Host a Match");
    connect(host, &QAction::triggered, this, &MainWindow::serverHost);
    onlineMenu->addAction(host);

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

void MainWindow::clientJoin() {
    join->setDisabled(true);
    host->setDisabled(true);
    game->deleteLater();
    game = new GameClient(18);
    setCentralWidget(game);
    jd->exec();
    if (jd->result() == QDialog::Rejected) {
        return;
    }
    ((GameClient *) game)->connectHost(jd->address(), jd->port());

    connect(game, &Game::gameOver, this, &MainWindow::score);
    connect(gameover, &GameOverBox::closed, game, &Game::reset);
}

void MainWindow::serverHost() {
    join->setDisabled(true);
    host->setDisabled(true);
    game->deleteLater();
    game = new GameHost(18);
    connect(((GameHost *)game), &GameHost::listening, hd, &HostDialog::display);
    connect(((GameHost *)game), &GameHost::connection, hd, &QDialog::accept);

    connect(game, &Game::gameOver, this, &MainWindow::score);
    connect(gameover, &GameOverBox::closed, game, &Game::reset);

    connect(hd, &QDialog::rejected, this, &MainWindow::closeServer);
    setCentralWidget(game);
    ((GameHost *) game)->host();
}

void MainWindow::closeServer() {
    join->setDisabled(false);
    host->setDisabled(false);
    game->deleteLater();
    game = new Game(18);
    connect(game, &Game::gameOver, this, &MainWindow::score);
    connect(gameover, &GameOverBox::closed, game, &Game::reset);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    game->fitInView(game->sceneRect(), Qt::KeepAspectRatio);
}
