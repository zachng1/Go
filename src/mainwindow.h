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
#include "dialogs/gameoverbox.h"
#include "dialogs/joindialog.h"
#include "dialogs/hostdialog.h"
#include "gameclient.h"
#include "gamehost.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);

signals:

public slots:
    void score();
    void clientJoin();
    void serverHost();

private:
    void setupMenu();
    void setupStatusBar();
    Game * game;
    int size;
    GameOverBox * gameover;
    JoinDialog * jd;
    HostDialog * hd;

    QAction * join;
    QAction * host;



};

#endif // MAINWINDOW_H
