#ifndef JOINDIALOG_H
#define JOINDIALOG_H

#include <QDialog>
#include <QFormLayout>
#include <QLineEdit>
#include <QDialogButtonBox>

class JoinDialog : public QDialog
{
    Q_OBJECT
public:
    JoinDialog(QWidget * parent = nullptr);
    QString address();
    quint16 port();

private:
    QLineEdit * a;
    QLineEdit * p;
    QDialogButtonBox * buttonbox;
};

#endif // JOINDIALOG_H
