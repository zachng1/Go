#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include "board.h"
#include "game.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void reset();
    void resize(int s);
    //void score();

private:
    void setupMenu();
    void setupStatusBar();
    Game * game;
    int size;

};

#endif // MAINWINDOW_H
