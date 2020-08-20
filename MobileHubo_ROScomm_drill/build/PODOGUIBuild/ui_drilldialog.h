/********************************************************************************
** Form generated from reading UI file 'drilldialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DRILLDIALOG_H
#define UI_DRILLDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_DrillDialog
{
public:
    QFrame *frame_gripper;
    QPushButton *PB_Gripper_grasp;
    QLabel *label_Gripper_right;
    QPushButton *PB_Gripper_open;
    QPushButton *PB_WalkReady;
    QPushButton *PB_STOP;
    QPushButton *PB_getCOM;
    QFrame *frame_DRILL;
    QFrame *frame_HoldDrill;
    QPushButton *PB_Hold_Approach;
    QLabel *label_HoldDrill;
    QPushButton *PB_Hold_Bring;
    QPushButton *PB_Hold_Grasp;
    QFrame *frame_Drilling;
    QLabel *label_Drilling;
    QPushButton *PB_Drill_Ready;
    QPushButton *PB_Drill_Approach;
    QPushButton *PB_Drill_Down;
    QPushButton *PB_Drill_Up;
    QFrame *frame_PutDril;
    QLabel *label_PutDrill;
    QPushButton *PB_Put_Lift;
    QPushButton *PB_Put_Put;
    QPushButton *PB_Put_WKRD;
    QLabel *label_DRILL;
    QPushButton *PB_Hold;
    QPushButton *PB_Drilling;
    QPushButton *PB_Put;

    void setupUi(QDialog *DrillDialog)
    {
        if (DrillDialog->objectName().isEmpty())
            DrillDialog->setObjectName(QStringLiteral("DrillDialog"));
        DrillDialog->resize(600, 549);
        frame_gripper = new QFrame(DrillDialog);
        frame_gripper->setObjectName(QStringLiteral("frame_gripper"));
        frame_gripper->setGeometry(QRect(120, 10, 191, 71));
        frame_gripper->setFrameShape(QFrame::StyledPanel);
        frame_gripper->setFrameShadow(QFrame::Raised);
        PB_Gripper_grasp = new QPushButton(frame_gripper);
        PB_Gripper_grasp->setObjectName(QStringLiteral("PB_Gripper_grasp"));
        PB_Gripper_grasp->setGeometry(QRect(100, 40, 80, 22));
        label_Gripper_right = new QLabel(frame_gripper);
        label_Gripper_right->setObjectName(QStringLiteral("label_Gripper_right"));
        label_Gripper_right->setGeometry(QRect(10, 10, 171, 21));
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        label_Gripper_right->setFont(font);
        PB_Gripper_open = new QPushButton(frame_gripper);
        PB_Gripper_open->setObjectName(QStringLiteral("PB_Gripper_open"));
        PB_Gripper_open->setGeometry(QRect(10, 40, 80, 22));
        PB_WalkReady = new QPushButton(DrillDialog);
        PB_WalkReady->setObjectName(QStringLiteral("PB_WalkReady"));
        PB_WalkReady->setGeometry(QRect(10, 10, 101, 71));
        QFont font1;
        font1.setPointSize(10);
        font1.setBold(false);
        font1.setWeight(50);
        PB_WalkReady->setFont(font1);
        PB_STOP = new QPushButton(DrillDialog);
        PB_STOP->setObjectName(QStringLiteral("PB_STOP"));
        PB_STOP->setGeometry(QRect(390, 170, 91, 151));
        PB_STOP->setFont(font);
        PB_getCOM = new QPushButton(DrillDialog);
        PB_getCOM->setObjectName(QStringLiteral("PB_getCOM"));
        PB_getCOM->setGeometry(QRect(390, 130, 91, 31));
        frame_DRILL = new QFrame(DrillDialog);
        frame_DRILL->setObjectName(QStringLiteral("frame_DRILL"));
        frame_DRILL->setGeometry(QRect(10, 90, 371, 241));
        frame_DRILL->setFrameShape(QFrame::StyledPanel);
        frame_DRILL->setFrameShadow(QFrame::Raised);
        frame_HoldDrill = new QFrame(frame_DRILL);
        frame_HoldDrill->setObjectName(QStringLiteral("frame_HoldDrill"));
        frame_HoldDrill->setGeometry(QRect(10, 80, 111, 121));
        frame_HoldDrill->setFrameShape(QFrame::StyledPanel);
        frame_HoldDrill->setFrameShadow(QFrame::Raised);
        PB_Hold_Approach = new QPushButton(frame_HoldDrill);
        PB_Hold_Approach->setObjectName(QStringLiteral("PB_Hold_Approach"));
        PB_Hold_Approach->setGeometry(QRect(10, 30, 91, 21));
        label_HoldDrill = new QLabel(frame_HoldDrill);
        label_HoldDrill->setObjectName(QStringLiteral("label_HoldDrill"));
        label_HoldDrill->setGeometry(QRect(10, 10, 91, 16));
        QFont font2;
        font2.setBold(true);
        font2.setWeight(75);
        label_HoldDrill->setFont(font2);
        PB_Hold_Bring = new QPushButton(frame_HoldDrill);
        PB_Hold_Bring->setObjectName(QStringLiteral("PB_Hold_Bring"));
        PB_Hold_Bring->setGeometry(QRect(10, 90, 91, 21));
        PB_Hold_Grasp = new QPushButton(frame_HoldDrill);
        PB_Hold_Grasp->setObjectName(QStringLiteral("PB_Hold_Grasp"));
        PB_Hold_Grasp->setGeometry(QRect(10, 60, 91, 22));
        frame_Drilling = new QFrame(frame_DRILL);
        frame_Drilling->setObjectName(QStringLiteral("frame_Drilling"));
        frame_Drilling->setGeometry(QRect(130, 80, 111, 151));
        frame_Drilling->setFrameShape(QFrame::StyledPanel);
        frame_Drilling->setFrameShadow(QFrame::Raised);
        label_Drilling = new QLabel(frame_Drilling);
        label_Drilling->setObjectName(QStringLiteral("label_Drilling"));
        label_Drilling->setGeometry(QRect(10, 10, 91, 16));
        label_Drilling->setFont(font2);
        PB_Drill_Ready = new QPushButton(frame_Drilling);
        PB_Drill_Ready->setObjectName(QStringLiteral("PB_Drill_Ready"));
        PB_Drill_Ready->setGeometry(QRect(10, 30, 91, 22));
        PB_Drill_Approach = new QPushButton(frame_Drilling);
        PB_Drill_Approach->setObjectName(QStringLiteral("PB_Drill_Approach"));
        PB_Drill_Approach->setGeometry(QRect(10, 60, 91, 22));
        PB_Drill_Down = new QPushButton(frame_Drilling);
        PB_Drill_Down->setObjectName(QStringLiteral("PB_Drill_Down"));
        PB_Drill_Down->setGeometry(QRect(10, 90, 91, 22));
        PB_Drill_Up = new QPushButton(frame_Drilling);
        PB_Drill_Up->setObjectName(QStringLiteral("PB_Drill_Up"));
        PB_Drill_Up->setGeometry(QRect(10, 120, 91, 22));
        frame_PutDril = new QFrame(frame_DRILL);
        frame_PutDril->setObjectName(QStringLiteral("frame_PutDril"));
        frame_PutDril->setGeometry(QRect(250, 80, 111, 121));
        frame_PutDril->setFrameShape(QFrame::StyledPanel);
        frame_PutDril->setFrameShadow(QFrame::Raised);
        label_PutDrill = new QLabel(frame_PutDril);
        label_PutDrill->setObjectName(QStringLiteral("label_PutDrill"));
        label_PutDrill->setGeometry(QRect(10, 10, 91, 16));
        label_PutDrill->setFont(font2);
        PB_Put_Lift = new QPushButton(frame_PutDril);
        PB_Put_Lift->setObjectName(QStringLiteral("PB_Put_Lift"));
        PB_Put_Lift->setGeometry(QRect(10, 30, 91, 22));
        PB_Put_Put = new QPushButton(frame_PutDril);
        PB_Put_Put->setObjectName(QStringLiteral("PB_Put_Put"));
        PB_Put_Put->setGeometry(QRect(10, 60, 91, 22));
        PB_Put_WKRD = new QPushButton(frame_PutDril);
        PB_Put_WKRD->setObjectName(QStringLiteral("PB_Put_WKRD"));
        PB_Put_WKRD->setGeometry(QRect(10, 90, 91, 22));
        label_DRILL = new QLabel(frame_DRILL);
        label_DRILL->setObjectName(QStringLiteral("label_DRILL"));
        label_DRILL->setGeometry(QRect(10, 10, 71, 21));
        QFont font3;
        font3.setPointSize(15);
        font3.setBold(true);
        font3.setWeight(75);
        label_DRILL->setFont(font3);
        PB_Hold = new QPushButton(frame_DRILL);
        PB_Hold->setObjectName(QStringLiteral("PB_Hold"));
        PB_Hold->setGeometry(QRect(10, 40, 111, 31));
        PB_Drilling = new QPushButton(frame_DRILL);
        PB_Drilling->setObjectName(QStringLiteral("PB_Drilling"));
        PB_Drilling->setGeometry(QRect(130, 40, 111, 31));
        PB_Put = new QPushButton(frame_DRILL);
        PB_Put->setObjectName(QStringLiteral("PB_Put"));
        PB_Put->setGeometry(QRect(250, 40, 111, 31));

        retranslateUi(DrillDialog);

        QMetaObject::connectSlotsByName(DrillDialog);
    } // setupUi

    void retranslateUi(QDialog *DrillDialog)
    {
        DrillDialog->setWindowTitle(QApplication::translate("DrillDialog", "Dialog", 0));
        PB_Gripper_grasp->setText(QApplication::translate("DrillDialog", "Close", 0));
        label_Gripper_right->setText(QApplication::translate("DrillDialog", "Gripper - Right", 0));
        PB_Gripper_open->setText(QApplication::translate("DrillDialog", "Open", 0));
        PB_WalkReady->setText(QApplication::translate("DrillDialog", "Walk\n"
"Ready", 0));
        PB_STOP->setText(QApplication::translate("DrillDialog", "STOP", 0));
        PB_getCOM->setText(QApplication::translate("DrillDialog", "get COM", 0));
        PB_Hold_Approach->setText(QApplication::translate("DrillDialog", "Approach", 0));
        label_HoldDrill->setText(QApplication::translate("DrillDialog", "Hold Drill", 0));
        PB_Hold_Bring->setText(QApplication::translate("DrillDialog", "Bring", 0));
        PB_Hold_Grasp->setText(QApplication::translate("DrillDialog", "Grasp", 0));
        label_Drilling->setText(QApplication::translate("DrillDialog", "Drilling", 0));
        PB_Drill_Ready->setText(QApplication::translate("DrillDialog", "Ready", 0));
        PB_Drill_Approach->setText(QApplication::translate("DrillDialog", "Approach", 0));
        PB_Drill_Down->setText(QApplication::translate("DrillDialog", "Down", 0));
        PB_Drill_Up->setText(QApplication::translate("DrillDialog", "Up", 0));
        label_PutDrill->setText(QApplication::translate("DrillDialog", "Put Drill", 0));
        PB_Put_Lift->setText(QApplication::translate("DrillDialog", "Lift", 0));
        PB_Put_Put->setText(QApplication::translate("DrillDialog", "Put", 0));
        PB_Put_WKRD->setText(QApplication::translate("DrillDialog", "Walkready", 0));
        label_DRILL->setText(QApplication::translate("DrillDialog", "DRILL", 0));
        PB_Hold->setText(QApplication::translate("DrillDialog", "HOLD", 0));
        PB_Drilling->setText(QApplication::translate("DrillDialog", "DRILLING", 0));
        PB_Put->setText(QApplication::translate("DrillDialog", "PUT", 0));
    } // retranslateUi

};

namespace Ui {
    class DrillDialog: public Ui_DrillDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DRILLDIALOG_H
