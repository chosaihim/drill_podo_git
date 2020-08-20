#ifndef DIALOG_H
#define DIALOG_H

#include <QDialog>
#include "BasicFiles/PODOALDialog.h"
#include "../../share/Headers/Command.h"
#include "CommonHeader.h"
#include "../../share/Headers/ROS_COMMUNICATION.h"
namespace Ui {
class CMDDialog;
}

class CMDDialog : public QDialog
{
    Q_OBJECT

public:
    explicit CMDDialog(QWidget *parent = 0);
    ~CMDDialog();

private slots:
    void DisplayUpdate();

    void on_BTN_WALKREADY_clicked();

    void on_BTN_HOMEPOS_clicked();

    void on_BTN_GRIPPER_OPEN_clicked();

    void on_BTN_GRIPPER_STOP_clicked();

    void on_BTN_GRIPPER_CLOSE_clicked();

    void on_BTN_JOYSTART_clicked();

    void on_BTN_JOYSTOP_clicked();

    void on_BTN_JOYMOVE_clicked();

    void on_BTN_MOVESTOP_clicked();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

private:
    Ui::CMDDialog *ui;
    QTimer		*displayTimer;

    int ALNum_ROScommand;
};

#endif // DIALOG_H
