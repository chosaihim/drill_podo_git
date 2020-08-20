/********************************************************************************
** Form generated from reading UI file 'CMDDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CMDDIALOG_H
#define UI_CMDDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_CMDDialog
{
public:
    QLabel *label_2;
    QFrame *line;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *BTN_HOMEPOS;
    QPushButton *BTN_WALKREADY;
    QWidget *layoutWidget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_3;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout;
    QRadioButton *RB_BOTH;
    QRadioButton *RB_RH;
    QRadioButton *RB_LH;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *BTN_GRIPPER_OPEN;
    QPushButton *BTN_GRIPPER_STOP;
    QPushButton *BTN_GRIPPER_CLOSE;
    QHBoxLayout *horizontalLayout_7;
    QLabel *label;
    QLineEdit *LE_GRIPPER_INPUT;
    QLabel *label_5;
    QWidget *layoutWidget2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QHBoxLayout *horizontalLayout_4;
    QTableWidget *JOY_TABLE_INFO_LEFT;
    QTableWidget *JOY_TABLE_INFO_RIGHT;
    QHBoxLayout *horizontalLayout_6;
    QPushButton *BTN_JOYSTART;
    QPushButton *BTN_JOYSTOP;
    QHBoxLayout *horizontalLayout_5;
    QPushButton *BTN_JOYMOVE;
    QPushButton *BTN_MOVESTOP;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QButtonGroup *GRB_GRIPPER;

    void setupUi(QDialog *CMDDialog)
    {
        if (CMDDialog->objectName().isEmpty())
            CMDDialog->setObjectName(QStringLiteral("CMDDialog"));
        CMDDialog->resize(829, 655);
        label_2 = new QLabel(CMDDialog);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setGeometry(QRect(20, 0, 491, 111));
        QFont font;
        font.setFamily(QStringLiteral("Courier"));
        label_2->setFont(font);
        label_2->setLineWidth(1);
        line = new QFrame(CMDDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(330, 190, 16, 441));
        line->setFrameShape(QFrame::VLine);
        line->setFrameShadow(QFrame::Sunken);
        layoutWidget = new QWidget(CMDDialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(490, 20, 261, 101));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        BTN_HOMEPOS = new QPushButton(layoutWidget);
        BTN_HOMEPOS->setObjectName(QStringLiteral("BTN_HOMEPOS"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(BTN_HOMEPOS->sizePolicy().hasHeightForWidth());
        BTN_HOMEPOS->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(BTN_HOMEPOS);

        BTN_WALKREADY = new QPushButton(layoutWidget);
        BTN_WALKREADY->setObjectName(QStringLiteral("BTN_WALKREADY"));
        sizePolicy.setHeightForWidth(BTN_WALKREADY->sizePolicy().hasHeightForWidth());
        BTN_WALKREADY->setSizePolicy(sizePolicy);

        horizontalLayout->addWidget(BTN_WALKREADY);

        layoutWidget1 = new QWidget(CMDDialog);
        layoutWidget1->setObjectName(QStringLiteral("layoutWidget1"));
        layoutWidget1->setGeometry(QRect(400, 250, 358, 282));
        verticalLayout_2 = new QVBoxLayout(layoutWidget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_3 = new QLabel(layoutWidget1);
        label_3->setObjectName(QStringLiteral("label_3"));

        verticalLayout_2->addWidget(label_3);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        RB_BOTH = new QRadioButton(layoutWidget1);
        GRB_GRIPPER = new QButtonGroup(CMDDialog);
        GRB_GRIPPER->setObjectName(QStringLiteral("GRB_GRIPPER"));
        GRB_GRIPPER->addButton(RB_BOTH);
        RB_BOTH->setObjectName(QStringLiteral("RB_BOTH"));
        RB_BOTH->setChecked(true);

        verticalLayout->addWidget(RB_BOTH);

        RB_RH = new QRadioButton(layoutWidget1);
        GRB_GRIPPER->addButton(RB_RH);
        RB_RH->setObjectName(QStringLiteral("RB_RH"));

        verticalLayout->addWidget(RB_RH);

        RB_LH = new QRadioButton(layoutWidget1);
        GRB_GRIPPER->addButton(RB_LH);
        RB_LH->setObjectName(QStringLiteral("RB_LH"));

        verticalLayout->addWidget(RB_LH);


        horizontalLayout_3->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        BTN_GRIPPER_OPEN = new QPushButton(layoutWidget1);
        BTN_GRIPPER_OPEN->setObjectName(QStringLiteral("BTN_GRIPPER_OPEN"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(BTN_GRIPPER_OPEN->sizePolicy().hasHeightForWidth());
        BTN_GRIPPER_OPEN->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(BTN_GRIPPER_OPEN);

        BTN_GRIPPER_STOP = new QPushButton(layoutWidget1);
        BTN_GRIPPER_STOP->setObjectName(QStringLiteral("BTN_GRIPPER_STOP"));
        sizePolicy1.setHeightForWidth(BTN_GRIPPER_STOP->sizePolicy().hasHeightForWidth());
        BTN_GRIPPER_STOP->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(BTN_GRIPPER_STOP);

        BTN_GRIPPER_CLOSE = new QPushButton(layoutWidget1);
        BTN_GRIPPER_CLOSE->setObjectName(QStringLiteral("BTN_GRIPPER_CLOSE"));
        sizePolicy1.setHeightForWidth(BTN_GRIPPER_CLOSE->sizePolicy().hasHeightForWidth());
        BTN_GRIPPER_CLOSE->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(BTN_GRIPPER_CLOSE);


        horizontalLayout_3->addLayout(horizontalLayout_2);


        verticalLayout_2->addLayout(horizontalLayout_3);

        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QStringLiteral("horizontalLayout_7"));
        label = new QLabel(layoutWidget1);
        label->setObjectName(QStringLiteral("label"));

        horizontalLayout_7->addWidget(label);

        LE_GRIPPER_INPUT = new QLineEdit(layoutWidget1);
        LE_GRIPPER_INPUT->setObjectName(QStringLiteral("LE_GRIPPER_INPUT"));
        LE_GRIPPER_INPUT->setMaxLength(3);

        horizontalLayout_7->addWidget(LE_GRIPPER_INPUT);


        verticalLayout_2->addLayout(horizontalLayout_7);

        label_5 = new QLabel(layoutWidget1);
        label_5->setObjectName(QStringLiteral("label_5"));

        verticalLayout_2->addWidget(label_5);

        layoutWidget2 = new QWidget(CMDDialog);
        layoutWidget2->setObjectName(QStringLiteral("layoutWidget2"));
        layoutWidget2->setGeometry(QRect(50, 210, 241, 411));
        verticalLayout_3 = new QVBoxLayout(layoutWidget2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setContentsMargins(0, 0, 0, 0);
        label_4 = new QLabel(layoutWidget2);
        label_4->setObjectName(QStringLiteral("label_4"));

        verticalLayout_3->addWidget(label_4);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(0);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        JOY_TABLE_INFO_LEFT = new QTableWidget(layoutWidget2);
        if (JOY_TABLE_INFO_LEFT->columnCount() < 1)
            JOY_TABLE_INFO_LEFT->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setHorizontalHeaderItem(0, __qtablewidgetitem);
        if (JOY_TABLE_INFO_LEFT->rowCount() < 9)
            JOY_TABLE_INFO_LEFT->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(0, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(1, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(2, __qtablewidgetitem3);
        QTableWidgetItem *__qtablewidgetitem4 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(3, __qtablewidgetitem4);
        QTableWidgetItem *__qtablewidgetitem5 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(4, __qtablewidgetitem5);
        QTableWidgetItem *__qtablewidgetitem6 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(5, __qtablewidgetitem6);
        QTableWidgetItem *__qtablewidgetitem7 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(6, __qtablewidgetitem7);
        QTableWidgetItem *__qtablewidgetitem8 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(7, __qtablewidgetitem8);
        QTableWidgetItem *__qtablewidgetitem9 = new QTableWidgetItem();
        JOY_TABLE_INFO_LEFT->setVerticalHeaderItem(8, __qtablewidgetitem9);
        JOY_TABLE_INFO_LEFT->setObjectName(QStringLiteral("JOY_TABLE_INFO_LEFT"));
        QFont font1;
        font1.setPointSize(7);
        JOY_TABLE_INFO_LEFT->setFont(font1);
        JOY_TABLE_INFO_LEFT->horizontalHeader()->setMinimumSectionSize(8);
        JOY_TABLE_INFO_LEFT->verticalHeader()->setDefaultSectionSize(27);
        JOY_TABLE_INFO_LEFT->verticalHeader()->setMinimumSectionSize(10);

        horizontalLayout_4->addWidget(JOY_TABLE_INFO_LEFT);

        JOY_TABLE_INFO_RIGHT = new QTableWidget(layoutWidget2);
        if (JOY_TABLE_INFO_RIGHT->columnCount() < 1)
            JOY_TABLE_INFO_RIGHT->setColumnCount(1);
        QTableWidgetItem *__qtablewidgetitem10 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setHorizontalHeaderItem(0, __qtablewidgetitem10);
        if (JOY_TABLE_INFO_RIGHT->rowCount() < 9)
            JOY_TABLE_INFO_RIGHT->setRowCount(9);
        QTableWidgetItem *__qtablewidgetitem11 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(0, __qtablewidgetitem11);
        QTableWidgetItem *__qtablewidgetitem12 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(1, __qtablewidgetitem12);
        QTableWidgetItem *__qtablewidgetitem13 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(2, __qtablewidgetitem13);
        QTableWidgetItem *__qtablewidgetitem14 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(3, __qtablewidgetitem14);
        QTableWidgetItem *__qtablewidgetitem15 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(4, __qtablewidgetitem15);
        QTableWidgetItem *__qtablewidgetitem16 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(5, __qtablewidgetitem16);
        QTableWidgetItem *__qtablewidgetitem17 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(6, __qtablewidgetitem17);
        QTableWidgetItem *__qtablewidgetitem18 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(7, __qtablewidgetitem18);
        QTableWidgetItem *__qtablewidgetitem19 = new QTableWidgetItem();
        JOY_TABLE_INFO_RIGHT->setVerticalHeaderItem(8, __qtablewidgetitem19);
        JOY_TABLE_INFO_RIGHT->setObjectName(QStringLiteral("JOY_TABLE_INFO_RIGHT"));
        JOY_TABLE_INFO_RIGHT->setFont(font1);
        JOY_TABLE_INFO_RIGHT->horizontalHeader()->setMinimumSectionSize(8);
        JOY_TABLE_INFO_RIGHT->verticalHeader()->setDefaultSectionSize(27);
        JOY_TABLE_INFO_RIGHT->verticalHeader()->setMinimumSectionSize(10);

        horizontalLayout_4->addWidget(JOY_TABLE_INFO_RIGHT);


        verticalLayout_3->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QStringLiteral("horizontalLayout_6"));
        BTN_JOYSTART = new QPushButton(layoutWidget2);
        BTN_JOYSTART->setObjectName(QStringLiteral("BTN_JOYSTART"));
        BTN_JOYSTART->setMinimumSize(QSize(0, 50));

        horizontalLayout_6->addWidget(BTN_JOYSTART);

        BTN_JOYSTOP = new QPushButton(layoutWidget2);
        BTN_JOYSTOP->setObjectName(QStringLiteral("BTN_JOYSTOP"));
        BTN_JOYSTOP->setEnabled(true);
        BTN_JOYSTOP->setMinimumSize(QSize(0, 50));
        BTN_JOYSTOP->setCheckable(false);
        BTN_JOYSTOP->setAutoDefault(true);

        horizontalLayout_6->addWidget(BTN_JOYSTOP);


        verticalLayout_3->addLayout(horizontalLayout_6);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        BTN_JOYMOVE = new QPushButton(layoutWidget2);
        BTN_JOYMOVE->setObjectName(QStringLiteral("BTN_JOYMOVE"));
        BTN_JOYMOVE->setMinimumSize(QSize(0, 50));

        horizontalLayout_5->addWidget(BTN_JOYMOVE);

        BTN_MOVESTOP = new QPushButton(layoutWidget2);
        BTN_MOVESTOP->setObjectName(QStringLiteral("BTN_MOVESTOP"));
        BTN_MOVESTOP->setEnabled(true);
        BTN_MOVESTOP->setMinimumSize(QSize(0, 50));

        horizontalLayout_5->addWidget(BTN_MOVESTOP);


        verticalLayout_3->addLayout(horizontalLayout_5);

        pushButton = new QPushButton(CMDDialog);
        pushButton->setObjectName(QStringLiteral("pushButton"));
        pushButton->setGeometry(QRect(490, 580, 80, 22));
        pushButton_2 = new QPushButton(CMDDialog);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));
        pushButton_2->setGeometry(QRect(580, 580, 80, 22));
        pushButton_3 = new QPushButton(CMDDialog);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));
        pushButton_3->setGeometry(QRect(670, 580, 80, 22));
        pushButton_4 = new QPushButton(CMDDialog);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));
        pushButton_4->setGeometry(QRect(490, 180, 80, 22));
        pushButton_5 = new QPushButton(CMDDialog);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));
        pushButton_5->setGeometry(QRect(600, 180, 80, 22));
        layoutWidget->raise();
        layoutWidget->raise();
        layoutWidget->raise();
        label_2->raise();
        line->raise();
        pushButton->raise();
        pushButton_2->raise();
        pushButton_3->raise();
        pushButton_4->raise();
        pushButton_5->raise();

        retranslateUi(CMDDialog);

        QMetaObject::connectSlotsByName(CMDDialog);
    } // setupUi

    void retranslateUi(QDialog *CMDDialog)
    {
        CMDDialog->setWindowTitle(QApplication::translate("CMDDialog", "Dialog", 0));
        label_2->setText(QApplication::translate("CMDDialog", "<html><head/><body><p><span style=\" color:#ff0004;\">Remember!!</span></p><p><span style=\" color:#ff0004;\">Make sure the green light is on the top of the &quot;Ref Enable&quot;.</span></p><p><br/>HomePos, WalkReady : Hubo takes the basic posture. </p><p>Be careful because this motion does not consider selfcollision.</p></body></html>", 0));
        BTN_HOMEPOS->setText(QApplication::translate("CMDDialog", "HomePos", 0));
        BTN_WALKREADY->setText(QApplication::translate("CMDDialog", "WalkReady", 0));
        label_3->setText(QApplication::translate("CMDDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:11pt; font-weight:600;\">Gripper Command</span></p></body></html>", 0));
        RB_BOTH->setText(QApplication::translate("CMDDialog", "Both Hand", 0));
        RB_RH->setText(QApplication::translate("CMDDialog", "Right Hand", 0));
        RB_LH->setText(QApplication::translate("CMDDialog", "Left Hand", 0));
        BTN_GRIPPER_OPEN->setText(QApplication::translate("CMDDialog", "OPEN", 0));
        BTN_GRIPPER_STOP->setText(QApplication::translate("CMDDialog", "STOP", 0));
        BTN_GRIPPER_CLOSE->setText(QApplication::translate("CMDDialog", "CLOSE", 0));
        label->setText(QApplication::translate("CMDDialog", "GripperLimit", 0));
        LE_GRIPPER_INPUT->setInputMask(QApplication::translate("CMDDialog", "000", 0));
        LE_GRIPPER_INPUT->setText(QApplication::translate("CMDDialog", "0", 0));
        label_5->setText(QApplication::translate("CMDDialog", "<html><head/><body><p align=\"center\">*Help (GripperLimit)*</p><p align=\"center\">[3-finger]</p><p align=\"center\">0 : default(max open or close)</p><p align=\"center\">[2-finger]</p><p align=\"center\">0 : default(max open or close)</p><p align=\"center\">(mm) : desired value between finger tip</p></body></html>", 0));
        label_4->setText(QApplication::translate("CMDDialog", "<html><head/><body><p align=\"center\"><span style=\" font-size:11pt; font-weight:600;\">JoyStick</span></p></body></html>", 0));
        QTableWidgetItem *___qtablewidgetitem = JOY_TABLE_INFO_LEFT->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("CMDDialog", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem1 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(0);
        ___qtablewidgetitem1->setText(QApplication::translate("CMDDialog", "L-LT", 0));
        QTableWidgetItem *___qtablewidgetitem2 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(1);
        ___qtablewidgetitem2->setText(QApplication::translate("CMDDialog", "L-LB", 0));
        QTableWidgetItem *___qtablewidgetitem3 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(2);
        ___qtablewidgetitem3->setText(QApplication::translate("CMDDialog", "L-JOG-RL", 0));
        QTableWidgetItem *___qtablewidgetitem4 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(3);
        ___qtablewidgetitem4->setText(QApplication::translate("CMDDialog", "L-JOG-UD", 0));
        QTableWidgetItem *___qtablewidgetitem5 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(4);
        ___qtablewidgetitem5->setText(QApplication::translate("CMDDialog", "L-ARW_RL", 0));
        QTableWidgetItem *___qtablewidgetitem6 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(5);
        ___qtablewidgetitem6->setText(QApplication::translate("CMDDialog", "L-ARW_UD", 0));
        QTableWidgetItem *___qtablewidgetitem7 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(6);
        ___qtablewidgetitem7->setText(QApplication::translate("CMDDialog", "R-JOG-BTN", 0));
        QTableWidgetItem *___qtablewidgetitem8 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(7);
        ___qtablewidgetitem8->setText(QApplication::translate("CMDDialog", "L-JOG-BTN", 0));
        QTableWidgetItem *___qtablewidgetitem9 = JOY_TABLE_INFO_LEFT->verticalHeaderItem(8);
        ___qtablewidgetitem9->setText(QApplication::translate("CMDDialog", "BTN-BACK", 0));
        QTableWidgetItem *___qtablewidgetitem10 = JOY_TABLE_INFO_RIGHT->horizontalHeaderItem(0);
        ___qtablewidgetitem10->setText(QApplication::translate("CMDDialog", "Value", 0));
        QTableWidgetItem *___qtablewidgetitem11 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(0);
        ___qtablewidgetitem11->setText(QApplication::translate("CMDDialog", "R-RT", 0));
        QTableWidgetItem *___qtablewidgetitem12 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(1);
        ___qtablewidgetitem12->setText(QApplication::translate("CMDDialog", "R-RB", 0));
        QTableWidgetItem *___qtablewidgetitem13 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(2);
        ___qtablewidgetitem13->setText(QApplication::translate("CMDDialog", "R-JOG-RL", 0));
        QTableWidgetItem *___qtablewidgetitem14 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(3);
        ___qtablewidgetitem14->setText(QApplication::translate("CMDDialog", "R-JOG-UD", 0));
        QTableWidgetItem *___qtablewidgetitem15 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(4);
        ___qtablewidgetitem15->setText(QApplication::translate("CMDDialog", "BTN-Y", 0));
        QTableWidgetItem *___qtablewidgetitem16 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(5);
        ___qtablewidgetitem16->setText(QApplication::translate("CMDDialog", "BTN-X", 0));
        QTableWidgetItem *___qtablewidgetitem17 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(6);
        ___qtablewidgetitem17->setText(QApplication::translate("CMDDialog", "BTN-B", 0));
        QTableWidgetItem *___qtablewidgetitem18 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(7);
        ___qtablewidgetitem18->setText(QApplication::translate("CMDDialog", "BTN-A", 0));
        QTableWidgetItem *___qtablewidgetitem19 = JOY_TABLE_INFO_RIGHT->verticalHeaderItem(8);
        ___qtablewidgetitem19->setText(QApplication::translate("CMDDialog", "BTN-START", 0));
        BTN_JOYSTART->setText(QApplication::translate("CMDDialog", "Joy Start", 0));
        BTN_JOYSTOP->setText(QApplication::translate("CMDDialog", "Joy Stop", 0));
        BTN_JOYMOVE->setText(QApplication::translate("CMDDialog", "JoyMove Start", 0));
        BTN_MOVESTOP->setText(QApplication::translate("CMDDialog", "JoyMove Stop", 0));
        pushButton->setText(QApplication::translate("CMDDialog", "send 1", 0));
        pushButton_2->setText(QApplication::translate("CMDDialog", "send 2", 0));
        pushButton_3->setText(QApplication::translate("CMDDialog", "send 3", 0));
        pushButton_4->setText(QApplication::translate("CMDDialog", "Save Start", 0));
        pushButton_5->setText(QApplication::translate("CMDDialog", "Save", 0));
    } // retranslateUi

};

namespace Ui {
    class CMDDialog: public Ui_CMDDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CMDDIALOG_H
