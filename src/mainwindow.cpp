#include "mainwindow.h"
#include <QtWidgets>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    game(new Game(18, this)),
    size(18)
{
    setCentralWidget(game);

    setupMenu();
    setupStatusBar();

}

void MainWindow::reset() {
    delete game;
    game = new Game(size, this);
    setCentralWidget(game);
}

void MainWindow::resize(int s) {
    size = s;
    reset();
}

/*void MainWindow::score() {
    int bs = game->bscore();
    int ws = game->wscore();
    std::cout << bs << ws << std::endl;
    std::string scoreText = "Black score: " + std::to_string(bs) + "\nWhite score: " + std::to_string(ws);
    QString qscoreText = QString::fromStdString(scoreText);
    QDialog * dialog = new QDialog(this);
    dialog->setModal(true);
    dialog->setMinimumSize(150, 75);
    QLabel * score = new QLabel(qscoreText, dialog);
    dialog->exec();
}*/

void MainWindow::setupMenu() {
    QMenu * gameMenu = menuBar()->addMenu("Game");

    QAction * reset = new QAction("Restart");
    connect(reset, &QAction::triggered, this, &MainWindow::reset);
    gameMenu->addAction(reset);

    QMenu * changeSize = new QMenu("Choose Size");

    QAction * nineteen = new QAction("19");
    connect(nineteen, &QAction::triggered, this,
            [=](){MainWindow::resize(18);});
    changeSize->addAction(nineteen);

    QAction * thirteen = new QAction("13");
    connect(thirteen, &QAction::triggered, this,
            [=](){MainWindow::resize(12);});
    changeSize->addAction(thirteen);

    QAction * nine = new QAction("9");
    connect(nine, &QAction::triggered, this,
            [=](){MainWindow::resize(8);});
    changeSize->addAction(nine);

    gameMenu->addMenu(changeSize);

    /*QAction * score = new QAction("Score");
    connect(score, &QAction::triggered, this, &MainWindow::score);
    gameMenu->addAction(score);*/
}

void MainWindow::setupStatusBar(){

    QStatusBar * statusbar = statusBar();
    statusbar->showMessage("Play Go!");

}
