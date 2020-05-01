#ifndef HOSTDIALOG_H
#define HOSTDIALOG_H

#include <QDialog>
#include <QDialogButtonBox>
#include <QHostAddress>
#include <QVBoxLayout>
#include <QLabel>


class HostDialog : public QDialog
{
    Q_OBJECT
public:
    HostDialog();
public slots:
    void display(QHostAddress address, quint16 port);
};

#endif // HOSTDIALOG_H
