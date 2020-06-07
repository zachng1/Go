#include "hostdialog.h"

HostDialog::HostDialog() : QDialog(), s{new QUdpSocket}, timer{new QTimer}, a{QHostAddress()}, p{quint16()}
{

    connect(timer, &QTimer::timeout,
            this, &HostDialog::broadcastMessage);
    timer->setInterval(2000);

    connect(this, &QDialog::accepted,
            this, &HostDialog::stopBroadcasting);
    connect(this, &QDialog::rejected,
            this, &HostDialog::stopBroadcasting);
}

void HostDialog::display(QHostAddress address, quint16 port) {
    QVBoxLayout * layout = new QVBoxLayout();
    layout->addWidget(new QLabel("Listening for connections on:" + address.toString() + ":" + QString::number(port)));
    setLayout(layout);
    startBroadcasting(address, port);

    this->exec();
}

void HostDialog::stopBroadcasting() {
    timer->stop();
}

void HostDialog::startBroadcasting(QHostAddress address, quint16 port) {
    a = address;
    p = port;
    timer->start();
}

void HostDialog::broadcastMessage() {
    QByteArray message{};
    message.append(a.toString());
    message.append(':');
    message.append(QString::fromStdString(std::to_string(p)));
    s->writeDatagram(message, QHostAddress::Broadcast, 61603);
}
