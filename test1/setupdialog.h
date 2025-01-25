#ifndef SETUPDIALOG_H
#define SETUPDIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <QList>

namespace Ui {
class SetupDialog;
}

class SetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetupDialog(QWidget *parent = nullptr);
    ~SetupDialog();

    QHostAddress selectedIp() const;
    quint16 selectedOrinPort() const;

private:
    Ui::SetupDialog *ui;
    QList<QHostAddress> availableAddresses;
};

#endif // SETUPDIALOG_H
