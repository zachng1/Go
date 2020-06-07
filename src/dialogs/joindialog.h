#ifndef JOINDIALOG_H
#define JOINDIALOG_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLineEdit>
#include <QDialogButtonBox>
#include <QUdpSocket>
#include <QNetworkDatagram>
#include <QListView>
#include <QStandardItemModel>
#include <QPushButton>
#include <QLabel>
#include <unordered_map>

class JoinDialog : public QDialog
{
    Q_OBJECT
public:
    JoinDialog(QWidget * parent = nullptr);
    QHostAddress address();
    quint16 port();
    void updateView();

private:
    QHostAddress a;
    quint16 p;
    QListView view;
    QStandardItemModel model;
    QDialogButtonBox * buttonbox;
    QUdpSocket * s;
    QTimer * t;
    std::unordered_map<QByteArray, bool> hosts;

private slots:
    void setSelection(const QModelIndex &index);

};

#endif // JOINDIALOG_H
