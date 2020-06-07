#ifndef HOSTDIALOG_H
#define HOSTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QHostAddress>
#include <QVBoxLayout>
#include <QLabel>
#include <QUdpSocket>
#include <QTimer>


class HostDialog : public QDialog
{
    Q_OBJECT
public:
    HostDialog();
public slots:
    void display(QHostAddress address, quint16 port);
private slots:
    void broadcastMessage();


private:
    void stopBroadcasting();
    void startBroadcasting(QHostAddress address, quint16 port);
    QUdpSocket * s;
    QTimer * timer;
    QHostAddress a;
    quint16 p;
};

#endif // HOSTDIALOG_H
