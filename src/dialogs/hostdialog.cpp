#include "hostdialog.h"

HostDialog::HostDialog() : QDialog()
{

}

void HostDialog::display(QHostAddress address, quint16 port) {
    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Hosting on: " + address.toString() + ":" + QString::number(port)));
    setLayout(layout);
    this->exec();
}
