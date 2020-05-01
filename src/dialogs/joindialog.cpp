#include "joindialog.h"

JoinDialog::JoinDialog(QWidget * parent) : QDialog(parent)
{
    QFormLayout layout;
    a = new QLineEdit();
    p = new QLineEdit();
    p->setInputMask("DDDD");
    a->setInputMask("000.000.000");
    layout.addRow("IP Address", a);
    layout.addRow("Port", p);

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    connect(buttonbox, &QDialogButtonBox::accepted,
            this, &QDialog::accept);
    connect(buttonbox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);
    layout.addRow(buttonbox);
    setLayout(&layout);
}

QString JoinDialog::address() {
    return a->text();
}

quint16 JoinDialog::port() {
    return p->text().toUShort();
}
