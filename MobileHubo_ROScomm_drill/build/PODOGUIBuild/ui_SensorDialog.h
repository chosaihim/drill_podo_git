/********************************************************************************
** Form generated from reading UI file 'SensorDialog.ui'
**
** Created by: Qt User Interface Compiler version 5.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SENSORDIALOG_H
#define UI_SENSORDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_SensorDialog
{
public:
    QGroupBox *groupBox;
    QFrame *line_2;
    QWidget *widget;
    QVBoxLayout *verticalLayout;
    QLabel *label_63;
    QGridLayout *gridLayout_15;
    QLineEdit *LE_SENSOR_CIMU_PITCH;
    QLineEdit *LE_SENSOR_CIMU_PITCH_VEL;
    QLabel *label_53;
    QLineEdit *LE_SENSOR_CIMU_PITCH_ACC;
    QLabel *label_60;
    QLabel *label_52;
    QLabel *label_54;
    QLineEdit *LE_SENSOR_CIMU_ROLL;
    QLineEdit *LE_SENSOR_CIMU_ROLL_VEL;
    QLineEdit *LE_SENSOR_CIMU_ROLL_ACC;
    QLabel *label_49;
    QWidget *widget1;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_62;
    QGridLayout *gridLayout_12;
    QLineEdit *LE_SENSOR_LWFT_MY;
    QLabel *label_43;
    QLabel *label_32;
    QLineEdit *LE_SENSOR_LWFT_MZ;
    QLabel *label_61;
    QLineEdit *LE_SENSOR_RWFT_FY;
    QLineEdit *LE_SENSOR_RWFT_FX;
    QLineEdit *LE_SENSOR_LWFT_FY;
    QLineEdit *LE_SENSOR_LWFT_FX;
    QLineEdit *LE_SENSOR_LWFT_FZ;
    QLineEdit *LE_SENSOR_LWFT_MX;
    QLineEdit *LE_SENSOR_RWFT_MY;
    QLabel *label_42;
    QLabel *label_31;
    QLineEdit *LE_SENSOR_RWFT_MX;
    QLineEdit *LE_SENSOR_RWFT_MZ;
    QLabel *label_44;
    QLabel *label_45;
    QLabel *label_39;
    QLineEdit *LE_SENSOR_RWFT_FZ;
    QLabel *label;
    QFrame *line;
    QPushButton *BTN_SENSOR_FT_NULL;
    QPushButton *BTN_SENSOR_IMU_NULL;
    QPushButton *BTN_SENSOR_ENABLE;
    QPushButton *BTN_SENSOR_DISABLE;

    void setupUi(QDialog *SensorDialog)
    {
        if (SensorDialog->objectName().isEmpty())
            SensorDialog->setObjectName(QStringLiteral("SensorDialog"));
        SensorDialog->resize(490, 620);
        groupBox = new QGroupBox(SensorDialog);
        groupBox->setObjectName(QStringLiteral("groupBox"));
        groupBox->setGeometry(QRect(10, 50, 471, 561));
        QFont font;
        font.setPointSize(11);
        font.setBold(true);
        font.setWeight(75);
        groupBox->setFont(font);
        groupBox->setStyleSheet(QLatin1String("QGroupBox {\n"
"    border: 1px solid gray;\n"
"    border-radius: 5px;\n"
"    margin-top: 7px;\n"
"}\n"
"\n"
"QGroupBox::title {\n"
"    subcontrol-origin: margin;\n"
"    left: 8px;\n"
"    padding: 0 3px 0 3px;\n"
"}\n"
"\n"
""));
        line_2 = new QFrame(groupBox);
        line_2->setObjectName(QStringLiteral("line_2"));
        line_2->setGeometry(QRect(10, 200, 451, 16));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);
        widget = new QWidget(groupBox);
        widget->setObjectName(QStringLiteral("widget"));
        widget->setGeometry(QRect(10, 245, 451, 111));
        verticalLayout = new QVBoxLayout(widget);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        label_63 = new QLabel(widget);
        label_63->setObjectName(QStringLiteral("label_63"));
        QFont font1;
        font1.setPointSize(9);
        font1.setBold(true);
        font1.setWeight(75);
        label_63->setFont(font1);
        label_63->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout->addWidget(label_63);

        gridLayout_15 = new QGridLayout();
        gridLayout_15->setObjectName(QStringLiteral("gridLayout_15"));
        LE_SENSOR_CIMU_PITCH = new QLineEdit(widget);
        LE_SENSOR_CIMU_PITCH->setObjectName(QStringLiteral("LE_SENSOR_CIMU_PITCH"));
        LE_SENSOR_CIMU_PITCH->setEnabled(false);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(LE_SENSOR_CIMU_PITCH->sizePolicy().hasHeightForWidth());
        LE_SENSOR_CIMU_PITCH->setSizePolicy(sizePolicy);
        LE_SENSOR_CIMU_PITCH->setMinimumSize(QSize(60, 20));
        LE_SENSOR_CIMU_PITCH->setMaximumSize(QSize(60, 20));
        QFont font2;
        font2.setPointSize(9);
        LE_SENSOR_CIMU_PITCH->setFont(font2);
        LE_SENSOR_CIMU_PITCH->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_CIMU_PITCH->setReadOnly(true);

        gridLayout_15->addWidget(LE_SENSOR_CIMU_PITCH, 3, 1, 1, 1);

        LE_SENSOR_CIMU_PITCH_VEL = new QLineEdit(widget);
        LE_SENSOR_CIMU_PITCH_VEL->setObjectName(QStringLiteral("LE_SENSOR_CIMU_PITCH_VEL"));
        LE_SENSOR_CIMU_PITCH_VEL->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_CIMU_PITCH_VEL->sizePolicy().hasHeightForWidth());
        LE_SENSOR_CIMU_PITCH_VEL->setSizePolicy(sizePolicy);
        LE_SENSOR_CIMU_PITCH_VEL->setMinimumSize(QSize(60, 20));
        LE_SENSOR_CIMU_PITCH_VEL->setMaximumSize(QSize(60, 20));
        LE_SENSOR_CIMU_PITCH_VEL->setFont(font2);
        LE_SENSOR_CIMU_PITCH_VEL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_CIMU_PITCH_VEL->setReadOnly(true);

        gridLayout_15->addWidget(LE_SENSOR_CIMU_PITCH_VEL, 3, 2, 1, 1);

        label_53 = new QLabel(widget);
        label_53->setObjectName(QStringLiteral("label_53"));
        sizePolicy.setHeightForWidth(label_53->sizePolicy().hasHeightForWidth());
        label_53->setSizePolicy(sizePolicy);
        label_53->setMinimumSize(QSize(50, 20));
        label_53->setMaximumSize(QSize(50, 20));
        label_53->setFont(font2);
        label_53->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_53, 3, 0, 1, 1);

        LE_SENSOR_CIMU_PITCH_ACC = new QLineEdit(widget);
        LE_SENSOR_CIMU_PITCH_ACC->setObjectName(QStringLiteral("LE_SENSOR_CIMU_PITCH_ACC"));
        LE_SENSOR_CIMU_PITCH_ACC->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_CIMU_PITCH_ACC->sizePolicy().hasHeightForWidth());
        LE_SENSOR_CIMU_PITCH_ACC->setSizePolicy(sizePolicy);
        LE_SENSOR_CIMU_PITCH_ACC->setMinimumSize(QSize(60, 20));
        LE_SENSOR_CIMU_PITCH_ACC->setMaximumSize(QSize(60, 20));
        LE_SENSOR_CIMU_PITCH_ACC->setFont(font2);
        LE_SENSOR_CIMU_PITCH_ACC->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_CIMU_PITCH_ACC->setReadOnly(true);

        gridLayout_15->addWidget(LE_SENSOR_CIMU_PITCH_ACC, 3, 3, 1, 1);

        label_60 = new QLabel(widget);
        label_60->setObjectName(QStringLiteral("label_60"));
        sizePolicy.setHeightForWidth(label_60->sizePolicy().hasHeightForWidth());
        label_60->setSizePolicy(sizePolicy);
        label_60->setMinimumSize(QSize(60, 20));
        label_60->setMaximumSize(QSize(60, 20));
        label_60->setFont(font2);
        label_60->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_60, 0, 3, 1, 1);

        label_52 = new QLabel(widget);
        label_52->setObjectName(QStringLiteral("label_52"));
        sizePolicy.setHeightForWidth(label_52->sizePolicy().hasHeightForWidth());
        label_52->setSizePolicy(sizePolicy);
        label_52->setMinimumSize(QSize(60, 20));
        label_52->setMaximumSize(QSize(60, 20));
        label_52->setFont(font2);
        label_52->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_52, 0, 1, 1, 1);

        label_54 = new QLabel(widget);
        label_54->setObjectName(QStringLiteral("label_54"));
        sizePolicy.setHeightForWidth(label_54->sizePolicy().hasHeightForWidth());
        label_54->setSizePolicy(sizePolicy);
        label_54->setMinimumSize(QSize(50, 20));
        label_54->setMaximumSize(QSize(50, 20));
        label_54->setFont(font2);
        label_54->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_54, 1, 0, 2, 1);

        LE_SENSOR_CIMU_ROLL = new QLineEdit(widget);
        LE_SENSOR_CIMU_ROLL->setObjectName(QStringLiteral("LE_SENSOR_CIMU_ROLL"));
        LE_SENSOR_CIMU_ROLL->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_CIMU_ROLL->sizePolicy().hasHeightForWidth());
        LE_SENSOR_CIMU_ROLL->setSizePolicy(sizePolicy);
        LE_SENSOR_CIMU_ROLL->setMinimumSize(QSize(60, 20));
        LE_SENSOR_CIMU_ROLL->setMaximumSize(QSize(60, 20));
        LE_SENSOR_CIMU_ROLL->setFont(font2);
        LE_SENSOR_CIMU_ROLL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_CIMU_ROLL->setReadOnly(true);

        gridLayout_15->addWidget(LE_SENSOR_CIMU_ROLL, 1, 1, 2, 1);

        LE_SENSOR_CIMU_ROLL_VEL = new QLineEdit(widget);
        LE_SENSOR_CIMU_ROLL_VEL->setObjectName(QStringLiteral("LE_SENSOR_CIMU_ROLL_VEL"));
        LE_SENSOR_CIMU_ROLL_VEL->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_CIMU_ROLL_VEL->sizePolicy().hasHeightForWidth());
        LE_SENSOR_CIMU_ROLL_VEL->setSizePolicy(sizePolicy);
        LE_SENSOR_CIMU_ROLL_VEL->setMinimumSize(QSize(60, 20));
        LE_SENSOR_CIMU_ROLL_VEL->setMaximumSize(QSize(60, 20));
        LE_SENSOR_CIMU_ROLL_VEL->setFont(font2);
        LE_SENSOR_CIMU_ROLL_VEL->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_CIMU_ROLL_VEL->setReadOnly(true);

        gridLayout_15->addWidget(LE_SENSOR_CIMU_ROLL_VEL, 1, 2, 2, 1);

        LE_SENSOR_CIMU_ROLL_ACC = new QLineEdit(widget);
        LE_SENSOR_CIMU_ROLL_ACC->setObjectName(QStringLiteral("LE_SENSOR_CIMU_ROLL_ACC"));
        LE_SENSOR_CIMU_ROLL_ACC->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_CIMU_ROLL_ACC->sizePolicy().hasHeightForWidth());
        LE_SENSOR_CIMU_ROLL_ACC->setSizePolicy(sizePolicy);
        LE_SENSOR_CIMU_ROLL_ACC->setMinimumSize(QSize(60, 20));
        LE_SENSOR_CIMU_ROLL_ACC->setMaximumSize(QSize(60, 20));
        LE_SENSOR_CIMU_ROLL_ACC->setFont(font2);
        LE_SENSOR_CIMU_ROLL_ACC->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_CIMU_ROLL_ACC->setReadOnly(true);

        gridLayout_15->addWidget(LE_SENSOR_CIMU_ROLL_ACC, 1, 3, 2, 1);

        label_49 = new QLabel(widget);
        label_49->setObjectName(QStringLiteral("label_49"));
        sizePolicy.setHeightForWidth(label_49->sizePolicy().hasHeightForWidth());
        label_49->setSizePolicy(sizePolicy);
        label_49->setMinimumSize(QSize(60, 20));
        label_49->setMaximumSize(QSize(60, 20));
        label_49->setFont(font2);
        label_49->setAlignment(Qt::AlignCenter);

        gridLayout_15->addWidget(label_49, 0, 2, 1, 1);


        verticalLayout->addLayout(gridLayout_15);

        widget1 = new QWidget(groupBox);
        widget1->setObjectName(QStringLiteral("widget1"));
        widget1->setGeometry(QRect(10, 40, 450, 131));
        verticalLayout_2 = new QVBoxLayout(widget1);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        verticalLayout_2->setContentsMargins(0, 0, 0, 0);
        label_62 = new QLabel(widget1);
        label_62->setObjectName(QStringLiteral("label_62"));
        label_62->setFont(font1);
        label_62->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        verticalLayout_2->addWidget(label_62);

        gridLayout_12 = new QGridLayout();
        gridLayout_12->setObjectName(QStringLiteral("gridLayout_12"));
        LE_SENSOR_LWFT_MY = new QLineEdit(widget1);
        LE_SENSOR_LWFT_MY->setObjectName(QStringLiteral("LE_SENSOR_LWFT_MY"));
        LE_SENSOR_LWFT_MY->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_LWFT_MY->sizePolicy().hasHeightForWidth());
        LE_SENSOR_LWFT_MY->setSizePolicy(sizePolicy);
        LE_SENSOR_LWFT_MY->setMinimumSize(QSize(60, 20));
        LE_SENSOR_LWFT_MY->setMaximumSize(QSize(60, 20));
        LE_SENSOR_LWFT_MY->setFont(font2);
        LE_SENSOR_LWFT_MY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_LWFT_MY->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_LWFT_MY, 2, 2, 1, 1);

        label_43 = new QLabel(widget1);
        label_43->setObjectName(QStringLiteral("label_43"));
        sizePolicy.setHeightForWidth(label_43->sizePolicy().hasHeightForWidth());
        label_43->setSizePolicy(sizePolicy);
        label_43->setMinimumSize(QSize(60, 20));
        label_43->setMaximumSize(QSize(60, 20));
        label_43->setFont(font2);
        label_43->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_43, 0, 5, 1, 1);

        label_32 = new QLabel(widget1);
        label_32->setObjectName(QStringLiteral("label_32"));
        sizePolicy.setHeightForWidth(label_32->sizePolicy().hasHeightForWidth());
        label_32->setSizePolicy(sizePolicy);
        label_32->setMinimumSize(QSize(60, 20));
        label_32->setMaximumSize(QSize(60, 20));
        label_32->setFont(font2);
        label_32->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_32, 0, 3, 1, 1);

        LE_SENSOR_LWFT_MZ = new QLineEdit(widget1);
        LE_SENSOR_LWFT_MZ->setObjectName(QStringLiteral("LE_SENSOR_LWFT_MZ"));
        LE_SENSOR_LWFT_MZ->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_LWFT_MZ->sizePolicy().hasHeightForWidth());
        LE_SENSOR_LWFT_MZ->setSizePolicy(sizePolicy);
        LE_SENSOR_LWFT_MZ->setMinimumSize(QSize(60, 20));
        LE_SENSOR_LWFT_MZ->setMaximumSize(QSize(60, 20));
        LE_SENSOR_LWFT_MZ->setFont(font2);
        LE_SENSOR_LWFT_MZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_LWFT_MZ->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_LWFT_MZ, 2, 3, 1, 1);

        label_61 = new QLabel(widget1);
        label_61->setObjectName(QStringLiteral("label_61"));
        sizePolicy.setHeightForWidth(label_61->sizePolicy().hasHeightForWidth());
        label_61->setSizePolicy(sizePolicy);
        label_61->setMinimumSize(QSize(60, 20));
        label_61->setMaximumSize(QSize(60, 20));
        label_61->setFont(font2);
        label_61->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_61, 0, 4, 1, 1);

        LE_SENSOR_RWFT_FY = new QLineEdit(widget1);
        LE_SENSOR_RWFT_FY->setObjectName(QStringLiteral("LE_SENSOR_RWFT_FY"));
        LE_SENSOR_RWFT_FY->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_RWFT_FY->sizePolicy().hasHeightForWidth());
        LE_SENSOR_RWFT_FY->setSizePolicy(sizePolicy);
        LE_SENSOR_RWFT_FY->setMinimumSize(QSize(60, 20));
        LE_SENSOR_RWFT_FY->setMaximumSize(QSize(60, 20));
        LE_SENSOR_RWFT_FY->setFont(font2);
        LE_SENSOR_RWFT_FY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_RWFT_FY->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_RWFT_FY, 1, 5, 1, 1);

        LE_SENSOR_RWFT_FX = new QLineEdit(widget1);
        LE_SENSOR_RWFT_FX->setObjectName(QStringLiteral("LE_SENSOR_RWFT_FX"));
        LE_SENSOR_RWFT_FX->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_RWFT_FX->sizePolicy().hasHeightForWidth());
        LE_SENSOR_RWFT_FX->setSizePolicy(sizePolicy);
        LE_SENSOR_RWFT_FX->setMinimumSize(QSize(60, 20));
        LE_SENSOR_RWFT_FX->setMaximumSize(QSize(60, 20));
        LE_SENSOR_RWFT_FX->setFont(font2);
        LE_SENSOR_RWFT_FX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_RWFT_FX->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_RWFT_FX, 1, 4, 1, 1);

        LE_SENSOR_LWFT_FY = new QLineEdit(widget1);
        LE_SENSOR_LWFT_FY->setObjectName(QStringLiteral("LE_SENSOR_LWFT_FY"));
        LE_SENSOR_LWFT_FY->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_LWFT_FY->sizePolicy().hasHeightForWidth());
        LE_SENSOR_LWFT_FY->setSizePolicy(sizePolicy);
        LE_SENSOR_LWFT_FY->setMinimumSize(QSize(60, 20));
        LE_SENSOR_LWFT_FY->setMaximumSize(QSize(60, 20));
        LE_SENSOR_LWFT_FY->setFont(font2);
        LE_SENSOR_LWFT_FY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_LWFT_FY->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_LWFT_FY, 2, 5, 1, 1);

        LE_SENSOR_LWFT_FX = new QLineEdit(widget1);
        LE_SENSOR_LWFT_FX->setObjectName(QStringLiteral("LE_SENSOR_LWFT_FX"));
        LE_SENSOR_LWFT_FX->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_LWFT_FX->sizePolicy().hasHeightForWidth());
        LE_SENSOR_LWFT_FX->setSizePolicy(sizePolicy);
        LE_SENSOR_LWFT_FX->setMinimumSize(QSize(60, 20));
        LE_SENSOR_LWFT_FX->setMaximumSize(QSize(60, 20));
        LE_SENSOR_LWFT_FX->setFont(font2);
        LE_SENSOR_LWFT_FX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_LWFT_FX->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_LWFT_FX, 2, 4, 1, 1);

        LE_SENSOR_LWFT_FZ = new QLineEdit(widget1);
        LE_SENSOR_LWFT_FZ->setObjectName(QStringLiteral("LE_SENSOR_LWFT_FZ"));
        LE_SENSOR_LWFT_FZ->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_LWFT_FZ->sizePolicy().hasHeightForWidth());
        LE_SENSOR_LWFT_FZ->setSizePolicy(sizePolicy);
        LE_SENSOR_LWFT_FZ->setMinimumSize(QSize(60, 20));
        LE_SENSOR_LWFT_FZ->setMaximumSize(QSize(60, 20));
        LE_SENSOR_LWFT_FZ->setFont(font2);
        LE_SENSOR_LWFT_FZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_LWFT_FZ->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_LWFT_FZ, 2, 6, 1, 1);

        LE_SENSOR_LWFT_MX = new QLineEdit(widget1);
        LE_SENSOR_LWFT_MX->setObjectName(QStringLiteral("LE_SENSOR_LWFT_MX"));
        LE_SENSOR_LWFT_MX->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_LWFT_MX->sizePolicy().hasHeightForWidth());
        LE_SENSOR_LWFT_MX->setSizePolicy(sizePolicy);
        LE_SENSOR_LWFT_MX->setMinimumSize(QSize(60, 20));
        LE_SENSOR_LWFT_MX->setMaximumSize(QSize(60, 20));
        LE_SENSOR_LWFT_MX->setFont(font2);
        LE_SENSOR_LWFT_MX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_LWFT_MX->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_LWFT_MX, 2, 1, 1, 1);

        LE_SENSOR_RWFT_MY = new QLineEdit(widget1);
        LE_SENSOR_RWFT_MY->setObjectName(QStringLiteral("LE_SENSOR_RWFT_MY"));
        LE_SENSOR_RWFT_MY->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_RWFT_MY->sizePolicy().hasHeightForWidth());
        LE_SENSOR_RWFT_MY->setSizePolicy(sizePolicy);
        LE_SENSOR_RWFT_MY->setMinimumSize(QSize(60, 20));
        LE_SENSOR_RWFT_MY->setMaximumSize(QSize(60, 20));
        LE_SENSOR_RWFT_MY->setFont(font2);
        LE_SENSOR_RWFT_MY->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_RWFT_MY->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_RWFT_MY, 1, 2, 1, 1);

        label_42 = new QLabel(widget1);
        label_42->setObjectName(QStringLiteral("label_42"));
        sizePolicy.setHeightForWidth(label_42->sizePolicy().hasHeightForWidth());
        label_42->setSizePolicy(sizePolicy);
        label_42->setMinimumSize(QSize(60, 20));
        label_42->setMaximumSize(QSize(60, 20));
        label_42->setFont(font2);
        label_42->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_42, 0, 6, 1, 1);

        label_31 = new QLabel(widget1);
        label_31->setObjectName(QStringLiteral("label_31"));
        sizePolicy.setHeightForWidth(label_31->sizePolicy().hasHeightForWidth());
        label_31->setSizePolicy(sizePolicy);
        label_31->setMinimumSize(QSize(60, 20));
        label_31->setMaximumSize(QSize(60, 20));
        label_31->setFont(font2);
        label_31->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_31, 0, 2, 1, 1);

        LE_SENSOR_RWFT_MX = new QLineEdit(widget1);
        LE_SENSOR_RWFT_MX->setObjectName(QStringLiteral("LE_SENSOR_RWFT_MX"));
        LE_SENSOR_RWFT_MX->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_RWFT_MX->sizePolicy().hasHeightForWidth());
        LE_SENSOR_RWFT_MX->setSizePolicy(sizePolicy);
        LE_SENSOR_RWFT_MX->setMinimumSize(QSize(60, 20));
        LE_SENSOR_RWFT_MX->setMaximumSize(QSize(60, 20));
        LE_SENSOR_RWFT_MX->setFont(font2);
        LE_SENSOR_RWFT_MX->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_RWFT_MX->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_RWFT_MX, 1, 1, 1, 1);

        LE_SENSOR_RWFT_MZ = new QLineEdit(widget1);
        LE_SENSOR_RWFT_MZ->setObjectName(QStringLiteral("LE_SENSOR_RWFT_MZ"));
        LE_SENSOR_RWFT_MZ->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_RWFT_MZ->sizePolicy().hasHeightForWidth());
        LE_SENSOR_RWFT_MZ->setSizePolicy(sizePolicy);
        LE_SENSOR_RWFT_MZ->setMinimumSize(QSize(60, 20));
        LE_SENSOR_RWFT_MZ->setMaximumSize(QSize(60, 20));
        LE_SENSOR_RWFT_MZ->setFont(font2);
        LE_SENSOR_RWFT_MZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_RWFT_MZ->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_RWFT_MZ, 1, 3, 1, 1);

        label_44 = new QLabel(widget1);
        label_44->setObjectName(QStringLiteral("label_44"));
        sizePolicy.setHeightForWidth(label_44->sizePolicy().hasHeightForWidth());
        label_44->setSizePolicy(sizePolicy);
        label_44->setMinimumSize(QSize(60, 20));
        label_44->setMaximumSize(QSize(60, 20));
        label_44->setFont(font2);
        label_44->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_44, 0, 1, 1, 1);

        label_45 = new QLabel(widget1);
        label_45->setObjectName(QStringLiteral("label_45"));
        label_45->setMinimumSize(QSize(50, 20));
        label_45->setMaximumSize(QSize(50, 20));
        label_45->setFont(font2);
        label_45->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_45, 1, 0, 1, 1);

        label_39 = new QLabel(widget1);
        label_39->setObjectName(QStringLiteral("label_39"));
        label_39->setMinimumSize(QSize(50, 20));
        label_39->setMaximumSize(QSize(50, 20));
        label_39->setFont(font2);
        label_39->setAlignment(Qt::AlignCenter);

        gridLayout_12->addWidget(label_39, 2, 0, 1, 1);

        LE_SENSOR_RWFT_FZ = new QLineEdit(widget1);
        LE_SENSOR_RWFT_FZ->setObjectName(QStringLiteral("LE_SENSOR_RWFT_FZ"));
        LE_SENSOR_RWFT_FZ->setEnabled(false);
        sizePolicy.setHeightForWidth(LE_SENSOR_RWFT_FZ->sizePolicy().hasHeightForWidth());
        LE_SENSOR_RWFT_FZ->setSizePolicy(sizePolicy);
        LE_SENSOR_RWFT_FZ->setMinimumSize(QSize(60, 20));
        LE_SENSOR_RWFT_FZ->setMaximumSize(QSize(60, 20));
        LE_SENSOR_RWFT_FZ->setFont(font2);
        LE_SENSOR_RWFT_FZ->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        LE_SENSOR_RWFT_FZ->setReadOnly(true);

        gridLayout_12->addWidget(LE_SENSOR_RWFT_FZ, 1, 6, 1, 1);


        verticalLayout_2->addLayout(gridLayout_12);

        label = new QLabel(SensorDialog);
        label->setObjectName(QStringLiteral("label"));
        label->setGeometry(QRect(10, 2, 131, 31));
        QFont font3;
        font3.setPointSize(12);
        font3.setBold(true);
        font3.setWeight(75);
        label->setFont(font3);
        line = new QFrame(SensorDialog);
        line->setObjectName(QStringLiteral("line"));
        line->setGeometry(QRect(10, 32, 118, 3));
        line->setFont(font2);
        line->setLineWidth(2);
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        BTN_SENSOR_FT_NULL = new QPushButton(SensorDialog);
        BTN_SENSOR_FT_NULL->setObjectName(QStringLiteral("BTN_SENSOR_FT_NULL"));
        BTN_SENSOR_FT_NULL->setGeometry(QRect(330, 10, 71, 31));
        BTN_SENSOR_FT_NULL->setFont(font2);
        BTN_SENSOR_IMU_NULL = new QPushButton(SensorDialog);
        BTN_SENSOR_IMU_NULL->setObjectName(QStringLiteral("BTN_SENSOR_IMU_NULL"));
        BTN_SENSOR_IMU_NULL->setGeometry(QRect(410, 10, 71, 31));
        BTN_SENSOR_IMU_NULL->setFont(font2);
        BTN_SENSOR_ENABLE = new QPushButton(SensorDialog);
        BTN_SENSOR_ENABLE->setObjectName(QStringLiteral("BTN_SENSOR_ENABLE"));
        BTN_SENSOR_ENABLE->setGeometry(QRect(130, 10, 71, 31));
        BTN_SENSOR_ENABLE->setFont(font2);
        BTN_SENSOR_DISABLE = new QPushButton(SensorDialog);
        BTN_SENSOR_DISABLE->setObjectName(QStringLiteral("BTN_SENSOR_DISABLE"));
        BTN_SENSOR_DISABLE->setGeometry(QRect(210, 10, 71, 31));
        BTN_SENSOR_DISABLE->setFont(font2);

        retranslateUi(SensorDialog);

        QMetaObject::connectSlotsByName(SensorDialog);
    } // setupUi

    void retranslateUi(QDialog *SensorDialog)
    {
        SensorDialog->setWindowTitle(QApplication::translate("SensorDialog", "Dialog", 0));
        groupBox->setTitle(QApplication::translate("SensorDialog", "Sensor Data", 0));
        label_63->setText(QApplication::translate("SensorDialog", "IMU(Roll,Pitch,Vel)", 0));
        label_53->setText(QApplication::translate("SensorDialog", "Pitch", 0));
        label_60->setText(QApplication::translate("SensorDialog", "ACC ", 0));
        label_52->setText(QApplication::translate("SensorDialog", "Angle", 0));
        label_54->setText(QApplication::translate("SensorDialog", "Roll", 0));
        label_49->setText(QApplication::translate("SensorDialog", "Gyro", 0));
        label_62->setText(QApplication::translate("SensorDialog", "FT(Mx,My,Fz)", 0));
        label_43->setText(QApplication::translate("SensorDialog", "Fy", 0));
        label_32->setText(QApplication::translate("SensorDialog", "Mz", 0));
        label_61->setText(QApplication::translate("SensorDialog", "Fx", 0));
        label_42->setText(QApplication::translate("SensorDialog", "Fz", 0));
        label_31->setText(QApplication::translate("SensorDialog", "My", 0));
        label_44->setText(QApplication::translate("SensorDialog", "Mx", 0));
        label_45->setText(QApplication::translate("SensorDialog", "RWFT", 0));
        label_39->setText(QApplication::translate("SensorDialog", "LWFT", 0));
        label->setText(QApplication::translate("SensorDialog", "Sensor", 0));
        BTN_SENSOR_FT_NULL->setText(QApplication::translate("SensorDialog", "FT NULL", 0));
        BTN_SENSOR_IMU_NULL->setText(QApplication::translate("SensorDialog", "IMU NULL", 0));
        BTN_SENSOR_ENABLE->setText(QApplication::translate("SensorDialog", "Enable", 0));
        BTN_SENSOR_DISABLE->setText(QApplication::translate("SensorDialog", "Disable", 0));
    } // retranslateUi

};

namespace Ui {
    class SensorDialog: public Ui_SensorDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SENSORDIALOG_H
