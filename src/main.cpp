#include <QApplication>
#include <iostream>
#include <string>
#include <sstream>
#include <limits>
#include "board.h"
#include "mainwindow.h"

int main(int argc, char **argv) {
    QApplication app(argc, argv);
    MainWindow mainWin;

    mainWin.showMaximized();
    return app.exec();
}
