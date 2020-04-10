#include "gameoverbox.h"

GameOverBox::GameOverBox(QWidget * parent) : QDialog(parent),
    layout(new QVBoxLayout(this)),
    blabel(new QLabel),
    wlabel(new QLabel),
    winner(new QLabel),
    accept(new QPushButton(QString("Ok")))
{
    QLabel * gameover = new QLabel(QString("Game Over"));
    layout->addWidget(gameover, 0, Qt::AlignCenter);
    layout->addWidget(blabel, 0, Qt::AlignLeft);
    layout->addWidget(wlabel, 0, Qt::AlignLeft);
    layout->addWidget(winner, 0, Qt::AlignCenter);
    layout->addWidget(accept, 0, Qt::AlignCenter);
    resize(300, 200);
    connect(accept, &QPushButton::pressed, this, &QWidget::close);


}

void GameOverBox::show(int black, int white) {


    std::ostringstream blackscorestream;
    blackscorestream << "Black: " << black;
    std::string blackscore = blackscorestream.str();
    blabel->setText(QString::fromStdString(blackscore));

    std::ostringstream whitescorestream;
    whitescorestream << "White: " << white;
    std::string whitescore = whitescorestream.str();
    wlabel->setText(QString::fromStdString(whitescore));

    if (black > white) {
        winner->setText(QString("Black Wins"));
    }
    else if (white > black) {
        winner->setText(QString("White Wins"));
    }
    else {
        winner->setText(QString("Draw"));
    }

    exec();
}

void GameOverBox::closeEvent(QCloseEvent * event) {
    emit closed();
    QWidget::closeEvent(event);
}
