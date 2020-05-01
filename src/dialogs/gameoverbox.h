#ifndef GAMEOVERBOX_H
#define GAMEOVERBOX_H

#include <QDialog>
#include <QLabel>
#include <QVBoxLayout>
#include <QPushButton>
#include <sstream>
#include <string>
#include <iostream>

class GameOverBox : public QDialog
{
    Q_OBJECT
public:
    GameOverBox(QWidget * parent = nullptr);
    void show(int black, int white);

    void closeEvent(QCloseEvent * event) override;

signals:
    void closed();

private:
    QVBoxLayout * layout;
    QLabel * blabel;
    QLabel * wlabel;
    QLabel * winner;
    QPushButton * accept;
};

#endif // GAMEOVERBOX_H
