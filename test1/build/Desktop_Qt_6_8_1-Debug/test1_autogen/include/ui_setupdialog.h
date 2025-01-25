/********************************************************************************
** Form generated from reading UI file 'setupdialog.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETUPDIALOG_H
#define UI_SETUPDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SetupDialog
{
public:
    QDialogButtonBox *buttonBox;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label;
    QComboBox *mIpAddrComboBox;
    QSpacerItem *verticalSpacer_2;
    QWidget *verticalLayoutWidget_2;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QLineEdit *mPodContorlPortLineEdit;
    QSpacerItem *verticalSpacer;
    QWidget *verticalLayoutWidget_3;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_3;
    QLineEdit *mPodContorlVideoPortLineEdit;
    QSpacerItem *verticalSpacer_3;

    void setupUi(QDialog *SetupDialog)
    {
        if (SetupDialog->objectName().isEmpty())
            SetupDialog->setObjectName("SetupDialog");
        SetupDialog->resize(400, 291);
        buttonBox = new QDialogButtonBox(SetupDialog);
        buttonBox->setObjectName("buttonBox");
        buttonBox->setGeometry(QRect(10, 250, 381, 32));
        buttonBox->setOrientation(Qt::Orientation::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);
        verticalLayoutWidget = new QWidget(SetupDialog);
        verticalLayoutWidget->setObjectName("verticalLayoutWidget");
        verticalLayoutWidget->setGeometry(QRect(9, 9, 381, 71));
        verticalLayout = new QVBoxLayout(verticalLayoutWidget);
        verticalLayout->setObjectName("verticalLayout");
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(verticalLayoutWidget);
        label->setObjectName("label");

        verticalLayout->addWidget(label);

        mIpAddrComboBox = new QComboBox(verticalLayoutWidget);
        mIpAddrComboBox->setObjectName("mIpAddrComboBox");

        verticalLayout->addWidget(mIpAddrComboBox);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        verticalLayoutWidget_2 = new QWidget(SetupDialog);
        verticalLayoutWidget_2->setObjectName("verticalLayoutWidget_2");
        verticalLayoutWidget_2->setGeometry(QRect(10, 90, 381, 71));
        verticalLayout_2 = new QVBoxLayout(verticalLayoutWidget_2);
        verticalLayout_2->setObjectName("verticalLayout_2");
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_2 = new QLabel(verticalLayoutWidget_2);
        label_2->setObjectName("label_2");

        verticalLayout_2->addWidget(label_2);

        mPodContorlPortLineEdit = new QLineEdit(verticalLayoutWidget_2);
        mPodContorlPortLineEdit->setObjectName("mPodContorlPortLineEdit");
        QSizePolicy sizePolicy(QSizePolicy::Policy::Fixed, QSizePolicy::Policy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(mPodContorlPortLineEdit->sizePolicy().hasHeightForWidth());
        mPodContorlPortLineEdit->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(mPodContorlPortLineEdit);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_2->addItem(verticalSpacer);

        verticalLayoutWidget_3 = new QWidget(SetupDialog);
        verticalLayoutWidget_3->setObjectName("verticalLayoutWidget_3");
        verticalLayoutWidget_3->setGeometry(QRect(10, 170, 381, 71));
        verticalLayout_3 = new QVBoxLayout(verticalLayoutWidget_3);
        verticalLayout_3->setObjectName("verticalLayout_3");
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(verticalLayoutWidget_3);
        label_3->setObjectName("label_3");

        verticalLayout_3->addWidget(label_3);

        mPodContorlVideoPortLineEdit = new QLineEdit(verticalLayoutWidget_3);
        mPodContorlVideoPortLineEdit->setObjectName("mPodContorlVideoPortLineEdit");
        sizePolicy.setHeightForWidth(mPodContorlVideoPortLineEdit->sizePolicy().hasHeightForWidth());
        mPodContorlVideoPortLineEdit->setSizePolicy(sizePolicy);

        verticalLayout_3->addWidget(mPodContorlVideoPortLineEdit);

        verticalSpacer_3 = new QSpacerItem(18, 40, QSizePolicy::Policy::Minimum, QSizePolicy::Policy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        retranslateUi(SetupDialog);
        QObject::connect(buttonBox, &QDialogButtonBox::accepted, SetupDialog, qOverload<>(&QDialog::accept));
        QObject::connect(buttonBox, &QDialogButtonBox::rejected, SetupDialog, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(SetupDialog);
    } // setupUi

    void retranslateUi(QDialog *SetupDialog)
    {
        SetupDialog->setWindowTitle(QCoreApplication::translate("SetupDialog", "Dialog", nullptr));
        label->setText(QCoreApplication::translate("SetupDialog", "Select Orin IP address", nullptr));
        label_2->setText(QCoreApplication::translate("SetupDialog", "POD control port", nullptr));
        label_3->setText(QCoreApplication::translate("SetupDialog", "POD video port", nullptr));
    } // retranslateUi

};

namespace Ui {
    class SetupDialog: public Ui_SetupDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETUPDIALOG_H
