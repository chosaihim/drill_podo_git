#ifndef OMNIMOVE_H
#define OMNIMOVE_H
#include <stdio.h>
#include "BasicFiles/BasicMatrix.h"
#include "BasicFiles/ManualCAN.h"
#include "BasicFiles/joint.h"
#include <cmath>
#ifndef PI
#define PI			3.141592653589793
#endif
#ifndef D2R
#define D2R			1.745329251994330e-2
#endif
#ifndef R2D
#define R2D			5.729577951308232e1
#endif

extern pRBCORE_SHM_COMMAND     sharedCMD;
extern pRBCORE_SHM_REFERENCE   sharedREF;
extern pRBCORE_SHM_SENSOR      sharedSEN;
extern pROS_SHM                sharedROS;
enum{
    INIT = 0, SHORT, MIDDLE, FAR, TURN_LITTLE, MOVE_LITTLE, TURN_NORMAL, MOVE_NORMAL, TURN_FAR, MOVE_FAR
};
enum{
    TimeFix = 0, XFix
};
typedef struct _USER_INPUT_PARAMETER{
    double Distance_OmniTrajectoryX_m = 1.0;
    double Distance_OmniTrajectoryY_m = 1.0;
    double Distance_OmniTrajectoryR_Rad = 30.0*D2R;
    double Time_OmniTrajectory_sec = 1.5;

    /* OmniWheel profile */
    double Vmax_ms = 0.55;//0.55;//0.57;//1.85;
    double Vmax_rads = 65.0*D2R;

    double Distance_TrajM_m = 0.98;
    double Distance_TrajRad = 30.0*D2R;
} USER_INPUT_PARA;


typedef struct _INFO_ROBOTMOVE{
    double X;
    double Y;
    double M;
    double Theta;
}Robot_move;

typedef struct _WHEEL_PARAMETER{
    double alpha1 = 60*D2R;
    double alpha2 = 180*D2R;
    double alpha3 = -60*D2R;

    double WheelRm = 0.127/2;
    double RobotRm = 0.656/2;
}WHEEL_PARAMETER;

typedef struct _OMNI_PARAMETER{
    Robot_move Pin;
    Robot_move Probot;
    Robot_move Vrobot;
    double CurSec;
    double GoalSec;
    double GoalSecR;
    double TrajSec;
    double TrajSecR;
    double SatSecR;
    double SatSec;
    double TickSec = 0.005;
    double RatioTraj = 0.2;
    double move_theta = 0.;

    /* Profile by HD */
    Robot_move Pc;  //move distance during acc&dec
    double Vms;
    double Vrads;
    double Trajm;
    double Trajrad;
    double TrajT;
}OMNI_PARAMETER;

typedef struct _WHEEL_INFO{
    double InitRef_Deg;
    double WheelVel_ms;
    double MoveDistance_m;
    double Reference;
}WheelInfos;

typedef struct _ROBOT_STATE
{
    Robot_move SLAMPos;
    Robot_move GoalPos;
    Robot_move DiffPos;
    Robot_move CurrPos;
}ROBOT_STATE;

class OMNIMOVE
{
public:
    OMNIMOVE();

    WheelInfos RWHinfo;
    WheelInfos LWHinfo;
    WheelInfos BWHinfo;
    OMNI_PARAMETER OMNIinfo;
private:
    int FLAG_OMNImove;
    int FLAG_JOYmove;
    USER_INPUT_PARA in;
    WHEEL_PARAMETER Pw;
    ROBOT_STATE    ROBOTinfo;
    double Xa3,Xa4,Xa5,Ya3,Ya4,Ya5,Ra3,Ra4,Ra5;
    int fix = XFix;
public:
    void Omni_CalVel_Robot5th();
    void Omni_CalRef_Motor();
    void Omni_CalVel_Wheel();

    void OMNIThread();
    void StartOMNImove(double _x, double _y, double _r);
    void JoyStickmove(int _onoff);
    void InitWheelInfo();
    void SetOMNIpara(int _mode);
    bool IsMovingWheel();
};

#endif // OMNIMOVE_H
