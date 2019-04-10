#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "elt_robot.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_pushButton_clicked();

    void on_loginTestButton_clicked();

    void on_loginTestButton_2_clicked();

    void on_ServoStatusTest_clicked();

    void on_robotStatus_clicked();

    void on_wayPointMaxJointSpeed_clicked();

    void on_addWayPoint_clicked();

    void on_trackMove_clicked();

    void on_clearWayPoint_clicked();

    void on_getRobotMode_clicked();

    void on_getRobotPose_clicked();

    void on_getMotorSpeed_clicked();

    void on_getCurrentCoord_clicked();

    void on_getCycleMode_clicked();

    void on_getCurrentJobLine_clicked();

    void on_getCurrentEncode_clicked();

    void on_getToolNum_clicked();

    void on_getRobotTorques_clicked();

    void on_getRobotPos_clicked();

    void on_jointMove_clicked();

    void on_lineMove_clicked();

    void on_arcMove_clicked();

    void on_rotateMove_clicked();

    void on_wayPointMaxLineSpeed_clicked();

    void on_wayPointMaxLineSpeed_2_clicked();

    void on_stopRobot_clicked();

    void on_runRobot_clicked();

    void on_inverseKinematic_clicked();

    void on_positiveKinematic_clicked();

    void on_conventUserBase_clicked();

    void on_digitalInOutput_clicked();

    void on_virtualInput_clicked();

    void on_virtualOutput_clicked();

    void on_bVarValue_clicked();

    void on_iVarValue_clicked();

    void on_dVarValue_clicked();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
