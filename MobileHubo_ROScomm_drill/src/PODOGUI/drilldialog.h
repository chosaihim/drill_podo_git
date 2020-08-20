#ifndef DRILLDIALOG_H
#define DRILLDIALOG_H

#include <QDialog>
#include "BasicFiles/PODOALDialog.h"
#include "../../share/Headers/Command.h"
#include "CommonHeader.h"
#include "../../share/Headers/ROS_COMMUNICATION.h"

namespace Ui {
class DrillDialog;
}

class DrillDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DrillDialog(QWidget *parent = 0);
    ~DrillDialog();

private slots:

    //WALKREADY
    void on_PB_WalkReady_clicked();

    //GRIPPER
    void on_PB_Gripper_open_clicked();

    void on_PB_Gripper_grasp_clicked();

    //HOLD_DRILL
    void on_PB_Hold_Approach_clicked();

    void on_PB_Hold_Grasp_clicked();

    void on_PB_Hold_Bring_clicked();

    //DRILLING
    void on_PB_Drill_Ready_clicked();

    void on_PB_Drill_Approach_clicked();

    void on_PB_Drill_Down_clicked();

    void on_PB_Drill_Up_clicked();

    //PUT_DRILL
    void on_PB_Put_Lift_clicked();

    void on_PB_Put_Put_clicked();

    void on_PB_Put_WKRD_clicked();

    //EMERGENCY STOP
    void on_PB_STOP_clicked();

    //DEBUGGING TOOLS
    void on_PB_getCOM_clicked();

    void on_PB_Hold_clicked();

    void on_PB_Drilling_clicked();

    void on_PB_Put_clicked();

private:
    Ui::DrillDialog *ui;
    LANDialog       *lanData;
    QTimer          *displayTimer;

    int ALNum_ROScommand;
};

#endif // DRILLDIALOG_H
