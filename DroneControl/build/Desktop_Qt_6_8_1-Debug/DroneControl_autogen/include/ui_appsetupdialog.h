/********************************************************************************
** Form generated from reading UI file 'appsetupdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_APPSETUPDIALOG_H
#define UI_APPSETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_AppSetupDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QLineEdit *mOrinReceiveIpLineEdit;
    QSpacerItem *verticalSpacer;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *mOrinReceivePortLineEdit;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *mOrinTransmitIpLineEdit;
    QSpacerItem *verticalSpacer_3;
    QWidget *verticalLayoutWidget_4;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_4;
    QLineEdit *mOrinTransmitPortLineEdit;
    QSpacerItem *verticalSpacer_4;
    QWidget *verticalLayoutWidget_5;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QLineEdit *mVidePathLineEdit;
    QSpacerItem *verticalSpacer_5;

    void setupUi(QDialog *AppSetupDialog)
    {
        if (AppSetupDialog->objectName().isEmpty())
            AppSetupDialog->setObjectName("AppSetupDialog");
        AppSetupDialog->resize(400, 571);
        buttonBox = new QDialogButtonBox(AppSetupDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(40, 520, 341, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        verticalLayoutWidget = new QWidget(AppSetupDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 10, 381, 80));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        mOrinReceiveIpLineEdit = new QLineEdit(verticalLayoutWidget);
        mOrinReceiveIpLineEdit->setObjectName("mOrinReceiveIpLineEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mOrinReceiveIpLineEdit->sizePolicy().hasHeightForWidth());
        mOrinReceiveIpLineEdit->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(mOrinReceiveIpLineEdit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer);

        verticalLayoutWidget_2 = new QWidget(AppSetupDialog);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 100, 381, 80));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        mOrinReceivePortLineEdit = new QLineEdit(verticalLayoutWidget_2);
        mOrinReceivePortLineEdit->setObjectName("mOrinReceivePortLineEdit");
        sizePolicy.setHeightForWidth(mOrinReceivePortLineEdit->sizePolicy().hasHeightForWidth());
        mOrinReceivePortLineEdit->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(mOrinReceivePortLineEdit);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);

        verticalLayoutWidget_3 = new QWidget(AppSetupDialog);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 190, 381, 80));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        mOrinTransmitIpLineEdit = new QLineEdit(verticalLayoutWidget_3);
        mOrinTransmitIpLineEdit->setObjectName("mOrinTransmitIpLineEdit");
        sizePolicy.setHeightForWidth(mOrinTransmitIpLineEdit->sizePolicy().hasHeightForWidth());
        mOrinTransmitIpLineEdit->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(mOrinTransmitIpLineEdit);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);

        verticalLayoutWidget_4 = new QWidget(AppSetupDialog);
        verticalLayoutWidget_4->setObjectName("verticalLayoutWidget_4");
        verticalLayoutWidget_4->setGeometry(QRect(10, 280, 381, 80));
        verticalLayout_4 = new QVBoxLayout(verticalLayoutWidget_4);
        verticalLayout_4->setObjectName("verticalLayout_4");
        verticalLayout_4->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(verticalLayoutWidget_4);
        label_4->setObjectName("label_4");

        verticalLayout_4->addWidget(label_4);

        mOrinTransmitPortLineEdit = new QLineEdit(verticalLayoutWidget_4);
        mOrinTransmitPortLineEdit->setObjectName("mOrinTransmitPortLineEdit");
        mOrinTransmitPortLineEdit->setEnabled(true);
        sizePolicy.setHeightForWidth(mOrinTransmitPortLineEdit->sizePolicy().hasHeightForWidth());
        mOrinTransmitPortLineEdit->setSizePolicy(sizePolicy);
        mOrinTransmitPortLineEdit->setMinimumSize(QSize(140, 25));

        verticalLayout_4->addWidget(mOrinTransmitPortLineEdit);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_4->addItem(verticalSpacer_4);

        verticalLayoutWidget_5 = new QWidget(AppSetupDialog);
        verticalLayoutWidget_5->setObjectName("verticalLayoutWidget_5");
        verticalLayoutWidget_5->setGeometry(QRect(10, 370, 381, 80));
        verticalLayout_5 = new QVBoxLayout(verticalLayoutWidget_5);
        verticalLayout_5->setObjectName("verticalLayout_5");
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(verticalLayoutWidget_5);
        label_5->setObjectName("label_5");

        verticalLayout_5->addWidget(label_5);

        mVidePathLineEdit = new QLineEdit(verticalLayoutWidget_5);
        mVidePathLineEdit->setObjectName("mVidePathLineEdit");
        QSizePolicy sizePolicy1(QSizePolicy::Policy::Expanding, QSizePolicy::Policy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(mVidePathLineEdit->sizePolicy().hasHeightForWidth());
        mVidePathLineEdit->setSizePolicy(sizePolicy1);

        verticalLayout_5->addWidget(mVidePathLineEdit);

        verticalSpacer_5 = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_5->addItem(verticalSpacer_5);


        retranslateUi(AppSetupDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, AppSetupDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, AppSetupDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(AppSetupDialog);
    } // setupUi

    void retranslateUi(QDialog *AppSetupDialog)
    {
        AppSetupDialog->setWindowTitle(QCoreApplication::translate("AppSetupDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("AppSetupDialog", "Orin receive ip", nullptr));
        mOrinReceiveIpLineEdit->setText(QCoreApplication::translate("AppSetupDialog", "192.168.144.20", nullptr));
        label_2->setText(QCoreApplication::translate("AppSetupDialog", "Orin receive port", nullptr));
        mOrinReceivePortLineEdit->setText(QCoreApplication::translate("AppSetupDialog", "5000", nullptr));
        label_3->setText(QCoreApplication::translate("AppSetupDialog", "Orin transmit ip", nullptr));
        mOrinTransmitIpLineEdit->setText(QCoreApplication::translate("AppSetupDialog", "192.168.144.21", nullptr));
        label_4->setText(QCoreApplication::translate("AppSetupDialog", "Orin transit port", nullptr));
        mOrinTransmitPortLineEdit->setText(QCoreApplication::translate("AppSetupDialog", "5000", nullptr));
        label_5->setText(QCoreApplication::translate("AppSetupDialog", "Video thred ip", nullptr));
        mVidePathLineEdit->setText(QCoreApplication::translate("AppSetupDialog", "rtsp://192.168.144.25:85554/main.264", nullptr));
    } // retranslateUi

};

namespace Ui {
    class AppSetupDialog: public Ui_AppSetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_APPSETUPDIALOG_H
