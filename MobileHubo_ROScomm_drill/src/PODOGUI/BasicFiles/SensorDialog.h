#ifndef SENSORDIALOG_H
#define SENSORDIALOG_H

#include <QDialog>
#include "CommonHeader.h"


namespace Ui {
class SensorDialog;
}

class SensorDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SensorDialog(QWidget *parent = 0);
    ~SensorDialog();

private slots:
    void on_BTN_SENSOR_ENABLE_clicked();
    void on_BTN_SENSOR_DISABLE_clicked();
    void on_BTN_SENSOR_FT_NULL_clicked();
    void on_BTN_SENSOR_IMU_NULL_clicked();

    void UpdateSensors();

private:
    Ui::SensorDialog *ui;
};

#endif // SENSORDIALOG_H
