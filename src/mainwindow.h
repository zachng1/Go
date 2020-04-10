#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "board.h"
#include "game.h"
#include "statusbarwidgets/xyinfo.h"
#include "statusbarwidgets/turninfo.h"
#include "gameoverbox.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void score();

private:
    void setupMenu();
    void setupStatusBar();
    Game * game;
    int size;
    GameOverBox * gameover;

};

#endif // MAINWINDOW_H
