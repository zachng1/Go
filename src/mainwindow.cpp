#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    game(new Game(18, this)),
    size(18),
    gameover(new GameOverBox(this)),
    jd{new JoinDialog},
    hd{new HostDialog},
    error{new QErrorMessage},
    xy{new XYinfo},
    turn{new TurnInfo}
{
    setupMenu();
    setupStatusBar();
    setupGame();
}

void MainWindow::setupGame() {
    if (game == nullptr) return;
    connect(game, &Game::gameOver, this, &MainWindow::score);
    connect(gameover, &GameOverBox::closed, game, &Game::reset);
    connect(game, &Game::turnChange, turn, &TurnInfo::update);
    setCentralWidget(game);

    //need to add setupMenu logic here
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
            [&](){
        this->game->resize(18);
        this->resizeEvent(nullptr);
    });
    changeSize->addAction(nineteen);

    QAction * thirteen = new QAction("13");
    connect(thirteen, &QAction::triggered, this,
            [&](){
        this->game->resize(12);
        this->resizeEvent(nullptr);
    });
    changeSize->addAction(thirteen);

    QAction * nine = new QAction("9");
    connect(nine, &QAction::triggered, this,
            [&](){
        this->game->resize(8);
        this->resizeEvent(nullptr);
    });
    changeSize->addAction(nine);

    gameMenu->addMenu(changeSize);

    // online stuff here

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

    statusbar->addPermanentWidget(xy);
    statusbar->addPermanentWidget(turn);
}

void MainWindow::score() {
    int black = game->score(BLACK);
    int white = game->score(WHITE);
    gameover->show(black, white);
}

void MainWindow::clientJoin() {
    join->setDisabled(true);
    host->setDisabled(true);
    jd->exec();
    if (jd->result() == QDialog::Rejected) {
        join->setDisabled(false);
        host->setDisabled(false);
        return;
    }
    else {
        game->deleteLater();
        game = new GameClient(18);
        connect(((GameOnline *)game), &GameOnline::error,
                this, &MainWindow::onlineErrorHandler);
        ((GameClient *) game)->connectHost(jd->address(), jd->port());
        setupGame();
        resizeEvent(nullptr);
    }
}

void MainWindow::serverHost() {
    join->setDisabled(true);
    host->setDisabled(true);
    //int onlineSize = game->size(); (I thought I could implement some kind of size sharing mechanism between the two
    // I thought wrong/not ready to implement it this afternoon..

    game->deleteLater();
    game = new GameHost(18);
    connect(((GameHost *)game), &GameHost::listening,
            hd, &HostDialog::display);
    connect(((GameHost *)game), &GameHost::connection,
            hd, &QDialog::accept);
    connect(((GameOnline *)game), &GameOnline::error,
            this, &MainWindow::onlineErrorHandler);

    connect(hd, &QDialog::rejected, this, &MainWindow::closeServer);
    resizeEvent(nullptr);
    if (((GameHost *) game)->host() < 0) {
        onlineErrorHandler();
        return;
    }
    else {
        setupGame();
        resizeEvent(nullptr);
    }
}

void MainWindow::onlineErrorHandler() {
    error->showMessage("There was an error with online play.\n Resetting to local mode.");
    game->deleteLater();
    game = new Game(18);
    setupGame();
    resizeEvent(nullptr);
}

void MainWindow::closeServer() {
    join->setDisabled(false);
    host->setDisabled(false);
    game->deleteLater();
    game = new Game(18);
    setupGame();
    resizeEvent(nullptr);
}

void MainWindow::resizeEvent(QResizeEvent *event) {
    game->fitInView(game->sceneRect(), Qt::KeepAspectRatio);
}
