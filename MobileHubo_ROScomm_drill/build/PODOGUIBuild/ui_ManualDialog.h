/********************************************************************************
** Form generated from reading UI file 'ManualDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MANUALDIALOG_H
#define UI_MANUALDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHeaderView>

QT_BEGIN_NAMESPACE

class Ui_ManualDialog
{
public:

    void setupUi(QDialog *ManualDialog)
    {
        if (ManualDialog->objectName().isEmpty())
            ManualDialog->setObjectName(QStringLiteral("ManualDialog"));
        ManualDialog->resize(840, 668);

        retranslateUi(ManualDialog);

        QMetaObject::connectSlotsByName(ManualDialog);
    } // setupUi

    void retranslateUi(QDialog *ManualDialog)
    {
        ManualDialog->setWindowTitle(QApplication::translate("ManualDialog", "Dialog", 0));
    } // retranslateUi

};

namespace Ui {
    class ManualDialog: public Ui_ManualDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MANUALDIALOG_H
