#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QErrorMessage>
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
    void closeServer();
    void onlineErrorHandler();

private:
    void resizeEvent(QResizeEvent *event) override;
    void setupMenu();
    void setupStatusBar();
    void setupGame();

    Game * game;
    int size;
    GameOverBox * gameover;
    JoinDialog * jd;
    HostDialog * hd;
    QErrorMessage * error;

    QAction * join;
    QAction * host;

    XYinfo * xy;
    TurnInfo * turn;


};

#endif // MAINWINDOW_H
