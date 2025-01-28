#ifndef APPSETUPDIALOG_H
#define APPSETUPDIALOG_H

#include <QDialog>
#include <QHostAddress>
#include <QString>
#include <QIntValidator>

namespace Ui {
class AppSetupDialog;
}

class AppSetupDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AppSetupDialog(QWidget *parent = nullptr);
    ~AppSetupDialog();
    QHostAddress orinRxIp() const;
    quint16 orinRxPort() const;
    QHostAddress orinTxIp() const;
    quint16 orinTxPort() const;
    QString videoPath() const;
private:
    Ui::AppSetupDialog *ui;
};

#endif // APPSETUPDIALOG_H
