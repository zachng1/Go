#include "joindialog.h"

JoinDialog::JoinDialog(QWidget * parent) : QDialog(parent),
    view{this},
    model{this},
    s{new QUdpSocket},
    hosts{}
{
    QVBoxLayout * layout = new QVBoxLayout{this};
    if (!s->bind(61603, QUdpSocket::ShareAddress)) {
        qDebug() << "Couldn't bind socket" << s->error();
        layout->addWidget(new QLabel{"Could not initialise online. Please restart"});

    }
    else {
        view.setModel(&model);
        view.setSelectionMode(QAbstractItemView::SingleSelection);
        view.setViewMode(QListView::ListMode);
        view.setResizeMode(QListView::Adjust);
        view.setLayoutMode(QListView::SinglePass);
        view.setEditTriggers(QListView::NoEditTriggers);

        connect(&view, &QAbstractItemView::clicked, this, &JoinDialog::setSelection);
        connect(s, &QUdpSocket::readyRead, this, &JoinDialog::updateView);

        layout->addWidget(&view);
    }

    buttonbox = new QDialogButtonBox(QDialogButtonBox::Ok | QDialogButtonBox::Cancel);
    buttonbox->button(QDialogButtonBox::Ok)->setEnabled(false);

    connect(buttonbox, &QDialogButtonBox::accepted,
            this, &QDialog::accept);
    connect(buttonbox, &QDialogButtonBox::rejected,
            this, &QDialog::reject);

    layout->addWidget(buttonbox);
    setLayout(layout);
}

QHostAddress JoinDialog::address() {
    return a;
}

quint16 JoinDialog::port() {
    return p;
}


void JoinDialog::updateView() {
    QNetworkDatagram message = s->receiveDatagram();
    qDebug() << "Dgram recieved";
    if (hosts.find(message.data()) == hosts.end()) {
        hosts.emplace(message.data(), true);
        QStandardItem * addressAndPort{new QStandardItem{"Server"}};
        addressAndPort->setData(message.data(), Qt::DisplayRole);
        model.appendRow(addressAndPort);
    }
    else qDebug() << hosts.find(message.data())->first;
}

void JoinDialog::setSelection(const QModelIndex &index) {

    //I am so sorry about how ugly this is !!
    QVariant addressAndPort = model.itemFromIndex(index)->data(Qt::DisplayRole);

    QString addressAndPortQString = QString::fromUtf8(addressAndPort.value<QByteArray>());
    QString addressString = addressAndPortQString.left(addressAndPortQString.indexOf(':'));
    QString portString = addressAndPortQString.mid(addressAndPortQString.indexOf(':')+1);
    a = QHostAddress{addressString};
    //this will be safe since p starts on the other end as a valid port (i.e. 16bit unsigned)
    //and thus will never result in overflow
    p = std::stoi(portString.toStdString());
    buttonbox->button(QDialogButtonBox::Ok)->setEnabled(true);
}
